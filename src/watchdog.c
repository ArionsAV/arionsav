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


void init_watchdog(void) {
	return;
}

int is_wd_up(void) {
	/* check somehow if the watchdog is up */
	return 1;
}

int main(int argc, char *argv[]) {

	if(is_wd_up())
		exit(0);
	
	init_watchdog();
	
	return 0;

}
