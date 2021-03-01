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
