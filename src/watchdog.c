/*

	This code is part of the ArionsAV project.
	
	NOTES:
		- Mar_01-21: Check config, binaries etc permissions aswell to make sure all is okay
		- Mar_01-21: Check file existence (to avoid problems)
		- Mar-01-21: Report errors to file to notify users, perform actions on other processes etc


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "log_manager.h"
#include "service_status.h"
#include "c_config/c_config.h"

/*
typedef struct pt_action {
        pthread_t t;
        void (*pt_detect_p)();
        void (*pt_fix_p)();
} pt_action;
pt_action *pt_ptr = NULL;
*/


int check_files_integrity(void) {
	return 1;
}

int check_esc(void) {
	/* know when to stop PT_MAIN that will close watchdog */
	/* maybe when service is needed to shut down? */
	/* we need to communicate between agent and watchdog so they do not check each other when
	the service is needed to be closed
	*/
	/* for the moment, this returned value will be static */
	return 0;
}

void watchdog(int pt_t) {
	
	int (*target)(void) = NULL;
	int (*check)(void) = NULL;
	
	if(pt_t == PT_MAIN) {
		target = NULL;
		check = NULL;
	} else if(pt_t == PT_SERVICE) {
		target = set_up_srv;
		check = is_srv_up;
	} else if(pt_t == PT_AGENT) {
		target = set_up_agnt;
		check = is_agnt_up;
	} else if(pt_t == PT_KMOD) {
		target = load_kmod_driver;
		check = is_kmod_loaded;
	} else if(pt_t == PT_INTEGRITY) {
		target = NULL;
		check = check_files_integrity;
	} else {
		log_wdg_error("Unknown pt_t value received watchdog(). Exiting...");
		exit(1);
	}
	
	if(check = 0x1337) {
		while(1) {
			sleep(PT_MAIN_WAIT);
			if(check_esc()) {
				log_wdg_info("check_esc() returned 1. Shutting down watchdog...");
				break;
			}
		}
		return;
	}
	
	
	if(check == NULL || target == NULL) {
		log_wdg_error("Either check() or target() found to be NULL. Returning...");
		return;
	}
	
	while(1) {
		if(!check()) {
			log_wdg_info("Service found down. Restarting it..."); /* add service name here */
			target();
		}
		sleep(WD_CHECK_DELAY);
	}
	
	return;	
}

void init_watchdog(void) {
	
	pthread_t p_srv = 0;
	pthread_t p_agent = 0;
	pthread_t p_kmod = 0;
	pthread_t p_integrity = 0;
	
	if(pthread_create(&p_srv, NULL, watchdog, PT_SERVICE)) {
		log_wdg_error("Error creating a new thread for PT_SERVICE. Exiting...");
		exit(1);
	}

	if(pthread_create(&p_agent, NULL, watchdog, PT_AGENT)) {
		log_wdg_error("Error creating a new thread for PT_AGENT. Exiting...");
		exit(1);
	}
	
	if(pthread_create(&p_kmod, NULL, watchdog, PT_KMOD)) {
		log_wdg_error("Error creating a new thread for PT_KMOD. Exiting...");
		exit(1);
	}
	
	if(pthread_create(&p_integrity, NULL, watchdog, PT_INTEGRITY)) {
		log_wdg_error("Error creating a new thread for PT_INTEGRITY. Exiting...");
		exit(1);
	}
	
	watchdog(PT_MAIN);
	
	return;
}


int main(int argc, char *argv[]) {

	log_wdg_info("Initializing watchdog @ init_watchdog()...");

	if(is_wdg_up()) {
		log_wdg_error("Watchdog service already up. Exiting...");
		exit(0);
	}
	
	init_watchdog();
	
	log_wdg_info("Watchdog is closing...");
	
	return 0;

}


