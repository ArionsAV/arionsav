/*

NOTES:
	- load_kmod_driver() can be highly vulnerable, if an attacker is able to modify the origin file, an arbitrary module can be loaded on kernel space

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "c_config/c_config.h"

#ifndef KMOD_FILE
#define KMOD_FILE "/var/backups/aav_kbk.dat" /* .ko backup file for restore purposes */
#endif

#ifndef DEPMOD_P
#define DEPMOD_P "/usr/sbin/depmod"
#ifndef

int file_exists(const char *filename) {
	FILE *file = NULL;
	if (file = fopen(filename, "r")) {
		fclose(file);
		return 1;
	}
	return 0;
}

int copy_file(const char *o_f, const char *d_f) {
	FILE *f_o = NULL;
	FILE *f_d = NULL;
	int o_f_sz = 0;
	struct stat st;
	char *ptr = NULL;
	stat(filename, &st);
	o_f_sz = st.st_size;
	if(!(f_o = fopen(o_f, "r")))
		return 0;
	if(!(f_d = fopen(d_f, "r"))) {
		fclose(f_o);
		return 0;
	}
	ptr = malloc(o_f_sz + 1);
	if(!ptr) {
		fclose(f_o);
		fclose(f_d);
		return 0;
	}
	fread(ptr, o_f_sz, sizeof(char), f_o);
	fwrite(ptr, o_f_sz, sizeof(char), f_d);
	fclose(f_o);
	fclose(f_d);
	if(ptr)
		free(ptr);
	return 1;
}

pid_t check_process(const char *name) {
	DIR *dir = NULL;
	FILE *f = NULL;
	char *endptr = NULL;
	char buf[512];
	long lpid = 0;
	char *first = NULL;
	struct dirent *ent;
	if(!(dir = opendir("/proc")))
		exit(1); /* what happened here?? */
	while((ent = readdir(dir)) != NULL) {
		lpid = strtol(ent->d_name, &endptr, 10);
		if (*endptr != 0x0)
			continue;
		snprintf(buf, sizeof(buf) - 1, "/proc/%ld/cmdline", lpid);
		f = fopen(buf, "r");
		if(f) {
			if(fgets(buf, sizeof(buf) - 1, f) != NULL) {
				first = strtok(buf, " ");
				if(!strcmp(first, name)) {
					fclose(f);
					closedir(dir);
					return (pid_t)lpid;
				}
			}
			fclose(f);
		}
	}
	closedir(dir);
	return 0;
}

int is_kmod_loaded(void) {
	FILE *fd = NULL;
	char *comp = NULL;
	char out[1024];
	int ret = 0;
	memset(out, '\0', sizeof(out));
	if(!(fd = popen("uname -r", O_RDONLY)))
		return -1;
	fread(1024, 1, fd);
	fclose(fd);
	comp = malloc(2048);
	if(!comp)
		return 0;
	memset(comp, '\0', 2048); 
	snprintf(comp, 2047, "/lib/modules/%s/kernel/drivers/platform/arionsavx.ko", out);
	if(file_exists(comp))
		ret = 1; /* module loaded */
	else
		ret = 0; /* module is not loaded */
	if(comp)
		free(comp);
	return ret;
}

void load_kmod_driver(void) {
	FILE *fd = NULL;
	char *comp = NULL;
	char out[1024];
	const char *n_ptr = {NULL};
	memset(out, '\0', sizeof(out));
	if(!(fd = popen("uname -r", O_RDONLY)))
		return; /* could not load driver */
	fread(1024, 1, fd);
	fclose(fd);
	comp = malloc(2048);
	if(!comp)
		return;
	memset(comp, '\0', 2048); 
	snprintf(comp, 2047, "/lib/modules/%s/kernel/drivers/platform/arionsavx.ko", out);
	
	if(file_exists(comp)) {
		if(comp)
			free(comp);
		return; /* module already loaded.. is it worth check the file hash? */
	}
	copy_file(KMOD_FILE, comp); /* if not copy it again from /var/backups/aav_kbk.dat */
	
	execve(DEPMOD_P, n_ptr, n_ptr);
	
	if(comp)
		free(comp);
	return;
}

/* initialize a process in background (do not make it depend on us) */
void init_background_process(const char *proc_name) {
	/* we need strncmp's to ensure we use proper arguments, not just filepath */
	char *n_ptr = {NULL};
	if(strcmp(proc_name, SERVICE_PROC) == 0) {
		char *args = {SERVICE_PROC, NULL};
	} else if(strcmp(proc_name, AGENT_PROC) == 0) {
		char *args = {AGENT_PROC, NULL};
	} else if(strcmp(proc_name, WATCHDOG_PROC) == 0) {
		char *args = {WATCHDOG_PROC, NULL};
	} else {
		return; /* unknown service ?!! */
	}
	execve(proc_name, args, n_ptr);
	return;
}

int is_srv_up(void) {
	if(check_process(SERVICE_PROC))
		return 1;
	return 0;
}

void set_up_srv(void) {
	init_background_process(SERVICE_PROC);
	return;
}

int is_agnt_up(void) {
	if(check_process(AGENT_PROC))
		return 1;
	return 0;
}

void set_up_agnt(void) {
	init_background_process(AGENT_PROC);
	return;
}

int is_wdg_up(void) {
	if(check_process(WATCHDOG_PROC))
		return 1;
	return 0;
}

void set_up_wdg(void) {
	init_background_process(WATCHDOG_PROC);
	return;
}

