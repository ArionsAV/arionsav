/*

	This code is part of the ArionsAV project.
	
	NOTES:


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void init_agent(void) {
	return;
}

int is_agnt_up(void) {
	/* check somehow if the agent is up */
	return 1;
}

int main(int argc, char *argv[]) {

	if(is_agnt_up())
		exit(0);
	
	init_agent();
	
	return 0;

}
