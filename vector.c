#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void *
mk (vector *v, int width) {
	v->width = width;
	v->next = 0;
	v->alloc = 8;
	v->data = malloc(8 * (v->alloc) * width);
	return (v->data);
}

void
unmk (vector *v) {
	free(v->data);
}

void * 
truncate (vector *v) {
	return realloc(v -> data, (v->width * v->next));
}

int 
push (vector *v, void *item) {
	if (v -> next == v -> alloc) 
		v->data = realloc(v -> data, 2 * (v->width * v->alloc));
	if (! v->data)
		return 0;
	memcpy( &(v->data)[v->width * (v->next++)], item, v->width);
	return 1;		
}

