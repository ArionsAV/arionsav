/*


Using libnotify-dev to pop notifications.

NOTES:
	- It would be nice to first check if the system is desktop or Server. If server return without even try to pop it

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
