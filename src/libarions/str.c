/*


    _         _                    ___     __
   / \   _ __(_) ___  _ __  ___   / \ \   / /
  / _ \ | '__| |/ _ \| '_ \/ __| / _ \ \ / / 
 / ___ \| |  | | (_) | | | \__ \/ ___ \ V /  
/_/   \_\_|  |_|\___/|_| |_|___/_/   \_\_/   
                                            
                                            
     -- This code is part of the ArionsAV project --
     
           << Code under GNU General Public License >>
          
      [ Src: https://github.com/ArionsAV/arionsav ]
	

Name: str
Description: String-managing functions

NOTES:
	
*/


#ifndef IGNORE_DST_MISMATCH
#define IGNORE_DST_MISMATCH 0 /* ignore if destination buffer is less than strlen of origin (and just copy until limit is reached ) */
#endif

#ifndef DANGEROUS_FUNCTIONS_FLG
#define DANGEROUS_FUNCTIONS_FLG 0
#endif

#if DANGEROUS_FUNCTIONS_FLG

/* copy string into buffer. Dangerous! No size restrictions */
int xstrcpy(char *str_a, char *str_b) {
	int x = 0;
	int i = 0;
	while(x < xstrlen(str_b)) {
		str_a[i] = str_b[x];
		i++;
		x++;
	}
	return i;
}

/* compare two strings. return 0 if equal or 1 if not */
/* dangerous! No restrictions. OOB read possible */
int xstrcmp(char *str_a, char *str_b) {
	int i = 0;
	int x = 0;
	int ret = 0;
	while(i < xstrlen(str_a) && x < xstrlen(str_b)) {
		if(str_a[i] != str_b[x]) {
			ret = 1;
			break;
		}
		i++;
		x++;
	}
	return ret;
}

int xsprintf() {

}

#endif

/* byte-count until next NULL byte */
int xstrlen(char *str) {
	int i = 0,
	int len = 0;
	while(1) {
		if(str[i] == '\0') {
			len = i; /* arrays start at 0, but last index was a NULL byte, it does not count */
			break;
		}
		i++;
	}
	return len;
}


/* compare two strings with size restrictions */
int xstrncmp(char *str_a, off_t len_a, char *str_b, off_t len_b) {
	int i = 0;
	int x = 0;
	int max = 0;
	int ret = 0;
	/* I select the minor count to use as maximum to avoid OOB read */
	if(len_a > len_b)
		max = len_b;
	else if(len_a < len_b)
		max = len_a;
	else
		max = len_a; /* len_a == len_b */
	while(i < max && x < max) {
		if(str_a[i] != str_b[x]) {
			ret = 1;
			break;
		}
		i++;
		x++;
	}
	return ret;
}

/* copy string into buffer with size restrictions */
int xstrncpy(char *str_a, off_t len_a, char *str_b, off_t len_b) {
	int i = 0;
	int x = 0;
	if(xstrlen(str_b) >= len_b)
		return -1; /* size mismatch. NULL byte found to be out-of-bounts */
	#if IGNORE_DST_MISMATCH
	if(xstrlen(str_b) >= len_a)
		return -1; /* size mismatch. Destination cannot hold complete string */
	#endif
	while(i < len_a && x < len_b
		&& x < xstrlen(str_b)) {
		str_a[i] = str_b[x];
		i++;
		x++;
	}
	return i;
}

int xsnprintf() {

}
