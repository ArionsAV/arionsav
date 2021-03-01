#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void init_service(void) {
	return;
}

int is_srv_up(void) {
	/* check somehow if the service is up */
	return 1;
}

int main(int argc, char *argv[]) {

	if(is_srv_up())
		exit(0);
	
	init_service();
	
	return 0;

}
