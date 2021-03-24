/*


    _         _                    ___     __
   / \   _ __(_) ___  _ __  ___   / \ \   / /
  / _ \ | '__| |/ _ \| '_ \/ __| / _ \ \ / / 
 / ___ \| |  | | (_) | | | \__ \/ ___ \ V /  
/_/   \_\_|  |_|\___/|_| |_|___/_/   \_\_/   
                                            
                                            
     -- This code is part of the ArionsAV project --
     
           << Code under GNU General Public License >>
          
      [ Src: https://github.com/ArionsAV/arionsav ]
	

Name: manager
Description: Managing-purpose functions

NOTES:
	- Mar_01-21: A random password will be generated on a global variable, if a memory corruption exploit is trying to use functions as gadgets like disable_antivirus() a password will be needed, that will not allow an attacker to use it directly? Bypass could be jumping to a code that calls it. Randomize which variable use in each moment? NULL password variable after using it?

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manager.h"
#include "mod/db_update.h"
#include "mod/av_update.h"
#include "service_status.h"
#include "interprocess_com.h"
#include "c_config/c_config.h"

#ifndef AV_INFO_PATH
#define AV_INFO_PATH ""
#endif

typedef struct {
	int status; /* 1 av enabled, else if 0 disabled */
	float version; /* antivirus current version */
} av_info;

av_info *current_info = NULL;

void enable_antivirus(void) {
	FILE *f = NULL;
	if(!current_info) {
		current_info = (av_info *)xmallocx(sizeof(av_info));
		f = fopen(AV_INFO_PATH, "r");
		fread(current_info, sizeof(av_info), sizeof(char), f);
		fclose(f);
	}
	if(current_info.status == 1)
		return; /* antivirus already disabled */
	current_info.status = 1;
	if(version == 0)
		current_info.version = 1.0;
	/* now we have to make changes on filesystem */
	f = fopen(AV_INFO_PATH, "w");
	fwrite(current_info, sizeof(av_info), sizeof(char), f);
	fclose(f);
	return;
}

void disable_antivirus(void) {
	FILE *f = NULL;
	if(!current_info) {
		current_info = (av_info *)xmallocx(sizeof(av_info));
		f = fopen(AV_INFO_PATH, "r");
		fread(current_info, sizeof(av_info), sizeof(char), f);
		fclose(f);
	}
	if(current_info.status == 0)
		return; /* antivirus already disabled */
	current_info.status = 0;
	if(version == 0)
		current_info.version = 1.0;
	/* now we have to make changes on filesystem */
	f = fopen(AV_INFO_PATH, "w");
	fwrite(current_info, sizeof(av_info), sizeof(char), f);
	fclose(f);
	return;
}

void add_exception(int except_t) {
	return;
}

int search_updates(int u_t) {
	int status = 0;
	
	puts("[*] Searching for updates...");
	
	status = db_update(u_t);

	if(status == 0) {
		puts("[i] No new updates found.");
	} else if(status == 1) {
		puts("[+] New updates installed successfully.");
	} else if(status == 2) {
		puts("[-] An unknown error ocurred.");
		return 0;
	}
	
	return 1;
}

