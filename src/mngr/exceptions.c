/*


    _         _                    ___     __
   / \   _ __(_) ___  _ __  ___   / \ \   / /
  / _ \ | '__| |/ _ \| '_ \/ __| / _ \ \ / / 
 / ___ \| |  | | (_) | | | \__ \/ ___ \ V /  
/_/   \_\_|  |_|\___/|_| |_|___/_/   \_\_/   
                                            
                                            
     -- This code is part of the ArionsAV project --
     
           << Code under GNU General Public License >>
          
      [ Src: https://github.com/ArionsAV/arionsav ]
	

Name: exceptions
Description: Code related with exception rules

NOTES:

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exceptions.h"

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
