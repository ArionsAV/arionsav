/*


    _         _                    ___     __
   / \   _ __(_) ___  _ __  ___   / \ \   / /
  / _ \ | '__| |/ _ \| '_ \/ __| / _ \ \ / / 
 / ___ \| |  | | (_) | | | \__ \/ ___ \ V /  
/_/   \_\_|  |_|\___/|_| |_|___/_/   \_\_/   
                                            
                                            
     -- This code is part of the ArionsAV project --
     
           << Code under GNU General Public License >>
          
      [ Src: https://github.com/ArionsAV/arionsav ]
	

Name: service
Description: Main detection service

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
