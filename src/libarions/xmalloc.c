/*


    _         _                    ___     __
   / \   _ __(_) ___  _ __  ___   / \ \   / /
  / _ \ | '__| |/ _ \| '_ \/ __| / _ \ \ / / 
 / ___ \| |  | | (_) | | | \__ \/ ___ \ V /  
/_/   \_\_|  |_|\___/|_| |_|___/_/   \_\_/   
                                            
                                            
     -- This code is part of the ArionsAV project --
     
           << Code under GNU General Public License >>
          
      [ Src: https://github.com/ArionsAV/arionsav ]
	

Name: xmalloc
Description: Malloc-like functions using mmap and munmap

NOTES:
	
*/

#ifndef SIZE_SZ
#define SIZE_SZ SYS_BITS/8
#endif

#define chunk2intern(p) p-SIZE_SZ

#define intern2chunk(p) p+SIZE_SZ


char *x_int_mallocx(unsigned long int size) {
	char *ptr = NULL;
	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(SYS_BITS == 32)
		(long *)ptr = size;
	else if(SYS_BITS == 64)
		(int *)ptr = (int)size;
	return intern2chunk(p);
}

void x_int_freex(char *ptr) {
	munmap(chunk2intern(p), sizeof(char));
	return;
}

char *xmallocx(unsigned int size) {
	char *ptr = NULL;
	ptr = x_int_mallocx(size);
	if(!ptr)
		return NULL;
	return ptr;
}

char *xcallocx(unsigned int size) {
	char *ptr = NULL;
	ptr = xmallocx(size);
	if(!ptr)
		return NULL;
	xmemset(ptr, '\0', size);
	return ptr;
}

void xfreex(char *ptr) {
	if(!ptr)
		return; /* if I forgot to check for NULLs this will save my life */
	x_int_freex(ptr);
	ptr = NULL; /* avoid Use-After-Free (UAF) or Double free */
	return;
}
