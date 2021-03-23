/*


    _         _                    ___     __
   / \   _ __(_) ___  _ __  ___   / \ \   / /
  / _ \ | '__| |/ _ \| '_ \/ __| / _ \ \ / / 
 / ___ \| |  | | (_) | | | \__ \/ ___ \ V /  
/_/   \_\_|  |_|\___/|_| |_|___/_/   \_\_/   
                                            
                                            
     -- This code is part of the ArionsAV project --
     
           << Code under GNU General Public License >>
          
      [ Src: https://github.com/ArionsAV/arionsav ]
	

Name: io
Description: Input / Output related-functions

NOTES:
	
*/


#ifndef DANGEROUS_FUNCTIONS_FLG
#define DANGEROUS_FUNCTIONS_FLG 0
#endif

#if DANGEROUS_FUNCTIONS_FLG

void xgets(char *buf) {

}

#endif

int xopen(const char *fpath, int mode) {

}

int xread(int fd, void *ptr, off_t sz) {

}

int xwrite(int fd, void *ptr, off_t sz) {

}

int xclose(int fd) {

}

int xfopen(const char *fpath, const char *mode) {

}

int xfread(void *ptr, off_t sz, off_t sz_x, FILE *f) {

}

int xfwrite(void *ptr, off_t sz, off_t sz_x, FILE *f) {

}

int xfclose(FILE *f) {

}

int xfgets(char *out, off_t sz, FILE *file) {

}

void xputs(const char *str) {
	xwrite(1, str, strlen(str));
	xwrite(1, "\n", 1);
	return;
}

void xprintf() {

}

void xfprintf() {

}

