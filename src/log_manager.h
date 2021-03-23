/*


    _         _                    ___     __
   / \   _ __(_) ___  _ __  ___   / \ \   / /
  / _ \ | '__| |/ _ \| '_ \/ __| / _ \ \ / / 
 / ___ \| |  | | (_) | | | \__ \/ ___ \ V /  
/_/   \_\_|  |_|\___/|_| |_|___/_/   \_\_/   
                                            
                                            
     -- This code is part of the ArionsAV project --
     
           << Code under GNU General Public License >>
          
      [ Src: https://github.com/ArionsAV/arionsav ]
	

Name: log_manager
Description: Logging-purpose functions

NOTES:
	- Mar_23-21: log file paths (for the moment both info and error dumped on same file)

*/


#ifndef AGENT_LOG_FILE
#define AGENT_LOG_FILE "/var/log/arionsav/agent/agent.log"
#endif

#ifndef AGENT_ERROR_LOG_FILE
#define AGENT_ERROR_LOG_FILE "/var/log/arionsav/agent/agent.log"
#endif
 
#ifndef SERVICE_LOG_FILE
#define SERVICE_LOG_FILE "/var/log/arionsav/service/service.log"
#endif

#ifndef SERVICE_ERROR_LOG_FILE
#define SERVICE_ERROR_LOG_FILE "/var/log/arionsav/service/service.log"
#endif

#ifndef WATCHDOG_LOG_FILE
#define WATCHDOG_LOG_FILE "/var/log/arionsav/watchdog/watchdog.log"
#endif

#ifndef WATCHDOG_ERROR_LOG_FILE
#define WATCHDOG_ERROR_LOG_FILE "/var/log/arionsav/watchdog/watchdog.log"
#endif


/* size-related */

#ifndef MAX_APPEND_DATA
#define MAX_APPEND_DATA 8096
#endif

#ifndef MAX_TIME_SZ
#define MAX_TIME_SZ 18
#endif

/* time-related */

#ifndef DATETIME_FORMAT
#define DATETIME_FORMAT "%H:%M:%S %d-%m-%Y" /* format used for date in logs */
#endif







