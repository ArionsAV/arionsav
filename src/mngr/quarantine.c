/*


    _         _                    ___     __
   / \   _ __(_) ___  _ __  ___   / \ \   / /
  / _ \ | '__| |/ _ \| '_ \/ __| / _ \ \ / / 
 / ___ \| |  | | (_) | | | \__ \/ ___ \ V /  
/_/   \_\_|  |_|\___/|_| |_|___/_/   \_\_/   
                                            
                                            
     -- This code is part of the ArionsAV project --
     
           << Code under GNU General Public License >>
          
      [ Src: https://github.com/ArionsAV/arionsav ]
	

Name: quarantine
Description: Functions related with quarantine (malware related)

NOTES:
	- Mar_23-21: What should we do if the path to restore already has a file? Maybe copy this file to path + "." + q_id + ".restored" ??
	
*/

int add_entity_to_quarantine(char *path) {
	return 1;
}

int restore_entity_from_quarantine(long int q_id) {
	return 1;
}
