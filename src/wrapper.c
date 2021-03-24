/*


    _         _                    ___     __
   / \   _ __(_) ___  _ __  ___   / \ \   / /
  / _ \ | '__| |/ _ \| '_ \/ __| / _ \ \ / / 
 / ___ \| |  | | (_) | | | \__ \/ ___ \ V /  
/_/   \_\_|  |_|\___/|_| |_|___/_/   \_\_/   
                                            
                                            
     -- This code is part of the ArionsAV project --
     
           << Code under GNU General Public License >>
          
      [ Src: https://github.com/ArionsAV/arionsav ]
	

Name: wrapper
Description: Mainly wrapper functions for security improvements on dynamic memory usage

NOTES:
	- Mar_23-21: If cookie space is out, program will fail. Implement a way to increase space for cookies... Maybe with linked lists and dynamic memory?
	- Mar_23-21: Heap cookies will decrease performance, but will improve security and make heap overflow exploitation a bit harder. But... does it worth it? MitiGator visited us maybe!
	- Mar_24-21: Use mmap for linked lists? what if an attacker has a cookie_struct right after his chunk? he will be able to corrupt cookie with custom value and even make his attacks easier (using xmallocx?)
*/


#ifndef HEAP_COOKIE_SZ
#define HEAP_COOKIE_SZ SYS_BITS/8 /* if system is 32 bits SYS_BITS will be 4, else 64 if 64 bit system */
#endif

#define chunk2intern(p) p-HEAP_COOKIE_SZ

#define intern2chunk(p) p+HEAP_COOKIE_SZ

#ifndef MIN_COOKIE
#define MIN_COOKIE 0x1111111111111111
#endif

#ifndef MAX_COOKIE
#define MAX_COOKIE 0xffffffffffffffff
#endif

/* deprecated */
#ifndef MAX_CHUNK_N
#define MAX_CHUNK_N 2048*2048
#endif

#ifndef CHUNK_POOL_N
#define CHUNK_POOL_N 2048*2048
#endif

typedef struct  {
	char *ptr;
	long cookie;
	cookie_struct *next;
} cookie_struct[CHUNK_POOL_N];


char *chunks[MAX_CHUNK_N];
long *cookies[MAX_CHUNK_N];

int cookie_initialized = 0;

cookie_struct *base_ptr = NULL;

void initialize_cookie(void) {
	for(int i = 0 ; i < sizeof(chunks) ; i++)
		chunks[i] = NULL;
	for(int x = 0 ; x < sizeof(cookies) ; x++)
		cookies[x] = 0;
	return;
}

/* initialize first chunk */
void __initialize_cookie(void) {
	base_ptr = (cookie_struct *)xmallocx(CHUNK_POOL_N * sizeof(*cookie_struct));
	memset(base_ptr, '\0', CHUNK_POOL_N * sizeof(*cookie_struct));
	return;
}

void append_cookie(char *ptr, long cookie) {
	/* try to use holes to optimize space */
	int i = 0;
	int first_free = -1;
	while(i < sizeof(chunks)) {
		if(chunks[i] == ptr)
			return; /* pointer already exists */
		i++;
	}
	i = 0;
	while(i < sizeof(chunks)) {
		if(chunks[i] == NULL) {
			first_free = i;
			break;
		}
		i++;
	}
	if(first_free < 0)
		return; /* out of space: this can be FATAL, implement a way to increase space to store them */
	chunks[first_free] = ptr;
	cookies[first_free] = cookie;
	return;
}

/* search a hole on existent pools. if not, create new pool */
void __append_cookie(char *ptr, long cookie) {
	int i = 0;
	int x = 0;
	int idx = -1;
	int no_flg = 0;
	cookie_struct *ptrx = NULL;
	ptrx = base_ptr;
	while(ptrx != NULL) {
		x = 0;
		while(x < CHUNK_POOL_N) {
			if(ptrx[x].ptr == NULL) {
				idx = x;
				break;
			}
			x++;
		}
		if(idx > 0)
			break;
		if(ptrx->next == NULL) {
			no_flg = 1;
			break;
		}
		ptrx = ptrx->next;
	}

	if(no_flg) {
		ptrx->next = (cookie_struct *)xmallocx(CHUNK_POOL_N * sizeof(*cookie_struct));
		memset(base_ptr, '\0', CHUNK_POOL_N * sizeof(*cookie_struct));
		idx = 0;
		ptrx = ptrx->next;
	}
	ptrx[idx].ptr = ptr;
	ptrx[idx].cookie = cookie;
	if(no_flg)
		ptrx[idx].next = NULL;
	return;
}

void delete_cookie(char *ptr) {
	int i = 0;
	int idx = -1;
	while(i < sizeof(chunks)) {
		if(chunks[i] == ptr) {
			idx = i;
			break;
		}
		i++;
	}
	if(idx < 0)
		return; /* pointer not found */
	chunks[idx] = NULL;
	cookies[idx] = 0;
	return;
}

/* traverse linked list to delete a cookie */
void __delete_cookie(char *ptr) {
	int i = 0;
	int x = 0;
	int idx = -1;
	int no_flg = 0;
	cookie_struct *ptrx = NULL;
	ptrx = base_ptr;
	while(ptrx != NULL) {
		x = 0;
		while(x < CHUNK_POOL_N) {
			if(ptrx[x].ptr == ptr) {
				idx = x;
				break;
			}
			x++;
		}
		if(idx > 0)
			break;
		if(ptrx->next == NULL)
			break;
		ptrx = ptrx->next;
	}
	
	if(idx < 0)
		return; /* chunk not found */

	ptrx[idx].ptr = NULL;
	ptrx[idx].cookie = 0;
	return;
}

int check_cookie(char *ptr, long cookie) {
	int i = 0;
	int idx = -1;
	while(i < sizeof(chunks)) {
		if(chunks[i] == ptr) {
			idx = i;
			break;
		}
		i++;
	}
	if(idx < 0)
		return 0; /* pointer not found */
	if(cookies[idx] == cookie)
		return 1;
	return 0;
}

/* traverse linked list to check if cookie is right or corrupted */
int __check_cookie(char *ptr, long cookie) {
	int i = 0;
	int x = 0;
	int idx = -1;
	int no_flg = 0;
	cookie_struct *ptrx = NULL;
	ptrx = base_ptr;
	while(ptrx != NULL) {
		x = 0;
		while(x < CHUNK_POOL_N) {
			if(ptrx[x].ptr == ptr) {
				idx = x;
				break;
			}
			x++;
		}
		if(idx > 0)
			break;
		if(ptrx->next == NULL)
			break;
		ptrx = ptrx->next;
	}
	
	if(idx < 0)
		return 0; /* chunk not found */

	if(ptrx[idx].cookie == cookie)
		return 1;
	return 0;
}

long generate_heap_cookie(void) {
	long cookie = 0;
	srand(rand() ^ time(NULL));
	srand(rand() + time(NULL));
	cookie = (MIN_COOKIE + rand()) % MAX_COOKIE;
	cookie =  cookie & 0xffffffffffffff00; /* we want first byte to be NULL to avoid cookie being leaked */
	return cookie;
}

char *xmalloc(unsigned int size) {
	if(!cookie_initialized)
		initialize_cookie();
	long heap_cookie_n = 0;
	char *ptr = NULL;
	heap_cookie_n = generate_heap_cookie();
	ptr = malloc(size);
	if(!ptr)
		return NULL;
	memset(ptr, '\0', size); /* this should be done just on a calloc variant, but let's make it default */
	(long *)ptr = heap_cookie_n; /* we enter the SYS_BITS/8-byte heap cookie */
	append_cookie(intern2chunk(ptr), heap_cookie_n);
	return intern2chunk(ptr);
}

char *xfree(char *ptr) {
	char *ptrx = NULL;
	if(!cookie_initialized)
		initialize_cookie();
	if(!ptr)
		return; /* avoid NULL ptr deref */
	if(!check_cookie(ptr, (long *)ptr)) {
		/* do nothing until implemented right */
		int dummy_var = 1
		//exit(1); /* access violation occured */
	}
	delete_cookie(ptr);
	ptrx = chunk2intern(ptr);
	free(ptrx);
	ptrx = NULL;
	ptr = NULL; /* avoid Use-After-Free (UAF) or double free */
	return;
}




