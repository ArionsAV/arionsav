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


*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log_manager.h"
#include "c_config/c_config.h"


/* pending: convert timestamp to format "h:m d:M:Y" */
void return_time_str(char *out, size_t max_sz) {
	time_t now = 0;
	struct tm ts;
	memset(out, '\0', max_sz);
	time(&now);
	ts = *localtime(&now);
	strftime(out, max_sz - 1, DATETIME_FORMAT, &ts); /* format can be changed */
        return;
}

void append_entry(const char *file_path, const char *append_content, const char *prefix, int time_prefix) {
	FILE *f = NULL;
	int pos = 0;
	char comp_append_data[MAX_APPEND_DATA];
	char time_str[MAX_TIME_SZ];
	memset(comp_append_data, '\0', sizeof(comp_append_data));
	memset(time_str, '\0', sizeof(time_str));
	if(!(f = fopen(file_path, "a")))
		return;
	return_time_str(time_str, MAX_TIME_SZ-1);
	snprintf(comp_append_data, sizeof(comp_append_data)-1, "[%s] %s %s", time_str, prefix, append_content);
	pos = strlen(comp_append_data);
	comp_append_data[pos] = 0x0a; // "\n" 
	comp_append_data[pos+1] = 0x0; // close string again
	fwrite(comp_append_data, pos+1, sizeof(char), f); // copy all except NULL byte
	fclose(f);
	return;
}

void log_agnt_info(const char *out_str) {
	append_entry(AGENT_LOG_FILE, out_str, "[AGENT]", 1);
	return;
}

void log_agnt_error(const char *out_str) {
	append_entry(AGENT_ERROR_LOG_FILE, out_str, "[AGENT]", 1);
	return;
}

void log_srv_info(const char *out_str) {
	append_entry(SERVICE_LOG_FILE, out_str, "[SERVICE]", 1);
	return;
}

void log_srv_error(const char *out_str) {
	append_entry(SERVICE_ERROR_LOG_FILE, out_str, "[SERVICE]", 1);
	return;
}

void log_wdg_info(const char *out_str) {
	append_entry(WATCHDOG_LOG_FILE, out_str, "[WATCHDOG]", 1);
	return;
}

void log_wdg_error(const char *out_str) {
	append_entry(WATCHDOG_ERROR_LOG_FILE, out_str, "[WATCHDOG]", 1);
	return;
}




