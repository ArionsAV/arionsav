/*

*/

#ifndef DANGEROUS_FUNCTIONS_FLG
#define DANGEROUS_FUNCTIONS_FLG 0
#endif

#if DANGEROUS_FUNCTIONS_FLG

#endif

/* copy bytes and return the number of copied bytes */
int xmemcpy(void *ptr_a, void *ptr_b, off_t sz_a, off_t sz_b) {
	int i = 0, x = 0;
	while(i < sz_a && x < sz_b) {
		ptr_a[i] = ptr_b[x];
		i++;
		x++;
	}
	return i;
}

/* if exactly equal return 0, else return 1 */
int xmemcmp(void *ptr_a, void *ptr_b, off_t sz_a, off_t sz_b) {
	int i = 0, x = 0, ret = 0;
	while(i < sz_a && x < sz_b) {
		if(ptr_a[i] != ptr_b[x]) {
			ret = 1;
			break;
		}
		i++;
		x++;
	}
	return ret;
}

/* memset a buffer return nothing */
void xmemset(void *ptr, char chr, off_t sz) {
	int i = 0;
	while(i < sz) {
		ptr[i] = chr;
		i++;
	}
	return;
}
