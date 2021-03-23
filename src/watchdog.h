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

#ifndef
#define PT_MAIN 0
#endif

#ifndef
#define PT_SERVICE 1
#endif

#ifndef
#define PT_AGENT 2
#endif

#ifndef
#define PT_KMOD 3
#endif

#ifndef
#define PT_INTEGRITY 4
#endif

/* static values */

#ifndef
#define MAX_PT_STRUCTS 4
#endif

#ifndef
#define PT_MAIN_WAIT 30 // 60
#endif

#ifndef
#define WD_CHECK_DELAY 60
#endif
