#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_ARGS_N 2

void parse_args(int n_args, char *args[]) {
	return;
}


int check_av_status(void) {
	/* check somehow if the services are running ok */
	return 1;
}

void help_usage(char *argv_0) {
	printf("Usage: %s -- whatever to explain here --\n\n");
	puts("option1 - Does nothing");
	puts("option2 - Does nothing");
	puts("");
	puts("");
	return;
}

int main(int argc, char *argv[]) {

	/* argv[0] does not count*/
	
	if(check_av_status()) {
		printf("[!] The Antivirus is not running!\n");
	}
	
	if(argc < MIN_ARGS_N+1) { 
		help_usage(argv[0]);
		exit(0);
	}
	
	parse_args(argc, argv);
	
	return 0;

}
