#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef struct _vector {
        int width;
        int next;
        int alloc;
        void *data;
} vector;

void *
mk (vector *v, int width);

void
unmk (vector *v);

void *
truncate (vector *v);

int
push (vector *v, void *item);

#endif // _VECTOR_H_
