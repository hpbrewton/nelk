#ifndef _GEN_H_
#define _GEN_H_

typedef enum _ntype {
	LIT,
	CLASS,
	NCLASS,
	DOT,
	REP,
	ALT,
	CAT
} ntype;

typedef union _ndata {
	char lit;
	struct {
		char* letters;
		int number;
	} charclass;
	int rep [2];
} ndata;

typedef struct _ast {
	int size;
	struct _ast **kids;
	ndata data;
	ntype type;
} ast;

void show(ast *t);
void gen(ast *t);

#endif // _GEN_H_
