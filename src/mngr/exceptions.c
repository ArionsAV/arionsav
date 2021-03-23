/*

*/

/* except or blacklist all found on a file path */

int add_path_rule(int action_t, char *path) {


} 

int del_path_rule(int action_t, char *path) {


} 

/* instead of file path, use sha256 hash instead */

int add_file_rule(int action_t, char *path) {


}

int del_file_rule(int action_t, char *path) {


} 


/* use above functions to add rules (but from a list) */

int load_whitelist(char *ptr, size_t b_sz) {

}

int load_blacklist(char *ptr, size_t b_sz) {

}
