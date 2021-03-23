/*


    _         _                    ___     __
   / \   _ __(_) ___  _ __  ___   / \ \   / /
  / _ \ | '__| |/ _ \| '_ \/ __| / _ \ \ / / 
 / ___ \| |  | | (_) | | | \__ \/ ___ \ V /  
/_/   \_\_|  |_|\___/|_| |_|___/_/   \_\_/   
                                            
                                            
     -- This code is part of the ArionsAV project --
     
           << Code under GNU General Public License >>
          
      [ Src: https://github.com/ArionsAV/arionsav ]
	

Name: notification
Description: Using libnotify-dev to pop notifications.

NOTES:
	- Mar_23-21: It would be nice to first check if the system is desktop or Server. If server return without even try to pop it
	
*/


#include <libnotify/notify.h>

int pop_notification(char *name, char *description) {
	NotifyNotification *n = NULL;
	notify_init("ArionsAV");
	if(!name)
		return 1;
	if(!description)
		n = notify_notification_new(name, "No description provided.", 0);
	else
		n = notify_notification_new(name, description, 0);
	notify_notification_set_timeout(n, 10000); // 10s
	if(!notify_notification_show(n, 0))
		return 0;
	return 1;
}
