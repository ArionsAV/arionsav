/*


    _         _                    ___     __
   / \   _ __(_) ___  _ __  ___   / \ \   / /
  / _ \ | '__| |/ _ \| '_ \/ __| / _ \ \ / / 
 / ___ \| |  | | (_) | | | \__ \/ ___ \ V /  
/_/   \_\_|  |_|\___/|_| |_|___/_/   \_\_/   
                                            
                                            
     -- This code is part of the ArionsAV project --
     
           << Code under GNU General Public License >>
          
      [ Src: https://github.com/ArionsAV/arionsav ]
	

Name: service_status
Description: Detect status of different processes

NOTES:

*/


#ifndef KMOD_FILE
#define KMOD_FILE "/var/backups/aav_kbk.dat" /* .ko backup file for restore purposes */
#endif

#ifndef DEPMOD_P
#define DEPMOD_P "/usr/sbin/depmod"
#endif

#ifndef SERVICE_PROC
#define SERVICE_PROC ""
#endif

#ifndef AGENT_PROC
#define AGENT_PROC ""
#endif

#ifndef WATCHDOG_PROC
#define WATCHDOG_PROC ""
#endif
