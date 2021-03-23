/*


    _         _                    ___     __
   / \   _ __(_) ___  _ __  ___   / \ \   / /
  / _ \ | '__| |/ _ \| '_ \/ __| / _ \ \ / / 
 / ___ \| |  | | (_) | | | \__ \/ ___ \ V /  
/_/   \_\_|  |_|\___/|_| |_|___/_/   \_\_/   
                                            
                                            
     -- This code is part of the ArionsAV project --
     
           << Code under GNU General Public License >>
          
      [ Src: https://github.com/ArionsAV/arionsav ]
	

Name: watchdog
Description: Detect down services and start them again

NOTES:

	
*/


/* pt_t valiues */

#ifndef PT_MAIN
#define PT_MAIN 0
#endif

#ifndef PT_SERVICE
#define PT_SERVICE 1
#endif

#ifndef PT_AGENT
#define PT_AGENT 2
#endif

#ifndef PT_KMOD
#define PT_KMOD 3
#endif

#ifndef PT_INTEGRITY
#define PT_INTEGRITY 4
#endif

/* static values */

#ifndef MAX_PT_STRUCTS
#define MAX_PT_STRUCTS 4
#endif

#ifndef PT_MAIN_WAIT
#define PT_MAIN_WAIT 30 // 60
#endif

#ifndef WD_CHECK_DELAY
#define WD_CHECK_DELAY 60
#endif

