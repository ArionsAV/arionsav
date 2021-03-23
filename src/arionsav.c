/*

	This code is part of the ArionsAV project.
	
	NOTES:


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manager.h"

void parse_args(int n_args, char *args[]) {

	if(strcmp(args[1], CMD_HELP)
		help_usage(argv[0]);
	else if(strcmp(args[1], CMD_DB_UPDATE))
		search_updates(UPDATE_TYPE_DB);
	else if(strcmp(args[1], CMD_AV_UPDATE))
		search_updates(UPDATE_TYPE_AV);
	else {
		puts("[-] Unknown command specified");
		return;
	}	
	return;
}


int check_av_status(void) {
	/* check if AV enabled or not */
	return 1;
}

int check_aslr_status(void) {
	FILE *f_aslr = NULL;
	char va_randomize_content[4];
	int status = 0;
	
	memset(va_randomize_content, '\0', sizeof(va_randomize_content));
	
	f_aslr = fopen(ASLR_CONF_PATH, "r")
	fread(va_randomize_content, sizeof(va_randomize_content)-1, sizeof(char), f_aslr);
	fclose(f_aslr);
	
	status = atoi(va_randomize_content);
	
	if(status == 2)
		return 1;
	else
		return 0;
}

void check_status(void) {
	if(!check_av_status())
		fprintf(stderr, "[!] Antivirus is NOT enabled!\n");

	if(!check_aslr_status())
		fprintf(stderr, "[!] ASLR is NOT enabled!\n");
		
	return;
}

void help_usage(char *argv_0) {
	printf("Usage: %s -- whatever to explain here --\n\n", argv_0);
	puts("option1 - Does nothing");
	puts("option2 - Does nothing");
	puts("");
	puts("");
	return;
}

int main(int argc, char *argv[]) {
	
	check_status();

	/* argv[0] does not count */
	
	if(argc < MIN_ARGS_N+1) { 
		help_usage(argv[0]);
		exit(0);
	}
	
	parse_args(argc, argv);
	
	return 0;

}


