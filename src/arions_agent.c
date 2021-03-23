/*

	This code is part of the ArionsAV project.
	
	NOTES:


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log_manager.h"
#include "service_status.h"
#include "interprocess_com.h"
#include "mod/db_update.h"
#include "mod/av_update.h"
#include "c_config/c_config.h"

/*
CMD_NONE = 0
CMD_DISABLE_SRV = 1
CMD_ENABLE_SRV = 2


FIFO_F_MNGR
FIFO_F_MNGR_RSP

CMD_DISABLE_SRV
COM_ENABLE_AV


MSG_CMD_NOT_FOUND

*/

int global_com_srv = CMD_NONE;

void set_pending_cmd_srv(int global_new) {
	global_com_srv = global_new;
	return;
}

void init_pipes(void) {
	log_agnt_info("Initializing pipes for inter-process communication...");
	mkfifo(FIFO_F_MNGR_AGNT, O_RDWR);
	mkfifo(FIFO_F_MNGR_AGNT_RESP, O_RDWR);
	mkfifo(FIFO_F_SRV_AGNT, O_RDWR);
	mkfifo(FIFO_F_SRV_AGNT_RESP, O_RDWR);
	return;
}

void close_pipes(void) {
	log_agnt_info("Closing pipes...");
	unlink(FIFO_F_MNGR_AGNT);
	unlink(FIFO_F_MNGR_AGNT_RESP);
	unlink(FIFO_F_SRV_AGNT);
	unlink(FIFO_F_SRV_AGNT_RESP);
	return;
}

void mngr_com(void) {
	FILE *f = NULL;
	char com_msg[MAX_COM_SZ];
	memset(com_msg, '\0', sizeof(com_msg));
	while(1) {
		if(!(f = fopen(FIFO_F_MNGR_AGNT, "r")))
			return;
		if(!(f2 = fopen(FIFO_F_MNGR_AGNT_RSP, "r"))) {
			fclose(f);
			return;
		}
		fgets(com_msg, sizeof(com_msg) - 1, f);
		if(strcmp(com_msg, COM_DISABLE_AV) == 0) {
			set_pending_cmd_srv(CMD_DISABLE_SRV);
		} else if(strcmp(com_msg, COM_ENABLE_AV) == 0) {
			set_pending_cmd_srv(CMD_ENABLE_SRV);
		} else {
			log_agnt_info("Unknown command received from manager.");
			fwrite(MSG_CMD_NOT_FOUND, sizeof(MSG_CMD_NOT_FOUND), sizeof(char), f2);
		}
		fclose(f);
		fclose(f2);
	}
	return;
}

void srv_com(void) {
	FILE *f = NULL;
	char com_msg[MAX_COM_SZ];
	memset(com_msg, '\0', sizeof(com_msg));
	while(1) {
		if(!(f = fopen(FIFO_F_SRV_AGNT, "r")))
			return;
		if(!(f2 = fopen(FIFO_F_SRV_AGNT_RSP, "r"))) {
			fclose(f2);
			return;
		}
		fwrite(, sizeof(), sizeof(char), f2);
		fgets(com_msg, sizeof(com_msg) - 1, f);
		fclose(f);
		fclose(f2);
	}
	return;
}


void check_watchdog(void) {

	while(1) {
		if(!is_wdg_up()) {
			log_agnt_info("Watchdog service found down. Restarting it...");
			set_up_wdg();
		}
		sleep(WD_INT_CHECK_DELAY);
	}
	return;
}

/* be aware of collisions in parallelism woth av update manually on arions.c */

void check_av_updates(void) {

	while(1) {
		if(check_av_update()) {
			log_agnt_info("AV update found. Applying it...");
			perform_av_update();
		}
		sleep(SRV_AV_DELAY);
	}
	return;

}

/* be aware of collisions in parallelism woth db update manually on arions.c */

void check_db_updates(void) {

	while(1) {
		if(check_db_update()) {
			log_agnt_info("DB update found. Downloading it...");
			perform_db_update();
		}
		sleep(SRV_DB_DELAY);
	}
	return;

}

int srv_check_esc(void) {
	/* check somehow if this service is needed to be down to exit */
	return 0;
}


void srv_main(void) {
	while(1) {
		sleep(C_MAIN_WAIT);
		if(srv_check_esc()) {
			log_srv_info("srv_check_esc() returned 1. Shutting down watchdog...");
			break;
		}
	}
	return;
}


void init_agent(void) {
	
	pthread_t c_wdg = 0;
	pthread_t c_av = 0;
	pthread_t c_db = 0;
	
	init_pipes();
	
	if(pthread_create(&c_wdg, NULL, check_watchdog, NULL)) {
		log_srv_error("Error creating a new thread for check_watchdog(). Exiting...");
		exit(1);
	}

	if(pthread_create(&c_av, NULL, check_av_updates, NULL)) {
		log_srv_error("Error creating a new thread for check_av_updates(). Exiting...");
		exit(1);
	}
	
	if(pthread_create(&c_db, NULL, check_db_updates, NULL)) {
		log_srv_error("Error creating a new thread for check_db_updates(). Exiting...");
		exit(1);
	}
	
	srv_main();
	
	close_pipes();
	
	return;
}


int main(int argc, char *argv[]) {

	log_agnt_info("Initializing agent @ init_agent()...");

	if(is_agnt_up()) {
		log_agnt_error("Agent service already up. Exiting...");
		exit(0);
	}
	
	init_agent();
	
	log_agnt_info("Agent service is closing...");
	
	return 0;

}
