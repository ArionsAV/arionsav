/*

*/

char *_int_malloc(unsigned int size) {
	char *ptr = NULL;
	return ptr;
}

void _int_free(char *ptr) {
	return;
}

char *xmalloc(unsigned int size) {
	char *ptr = NULL;
	ptr = _int_malloc(size);
	if(!ptr)
		return NULL;
	return ptr;
}

char *xcalloc(unsigned int size) {
	char *ptr = NULL;
	ptr = xmalloc(size);
	if(!ptr)
		return NULL;
	xmemset(ptr, '\0', size);
	return ptr;
}

void xfree(char *ptr) {
	if(!ptr)
		return; /* if I forgot to check for NULLs this will save my life */
	_int_free(ptr);
	ptr = NULL; /* avoid Use-After-Free (UAF) or Double free */
	return;
}
