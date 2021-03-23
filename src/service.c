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
#include "c_config/c_config.h"

void init_service(void) {
	return;
}

int main(int argc, char *argv[]) {
	
	log_srv_info("Initializing service @ init_service()...");
	
	if(is_srv_up()) {
		log_srv_error("Service already up. Exiting...");
		exit(0);
	}
	
	init_service();
	
	return 0;

}
