#include "gen.h"
#include <stdlib.h>
#include "vector.h"
#include <time.h>
#include <stdio.h>

int LIMIT = 10;
char *curc;

char
match (char l) {
	if (*curc == l)  {
		++curc;
		return l;
	}
	return '\0';
}

char
any () {
	if (*curc == '|') {return '\0';}
	if (*curc == '*') {return '\0';}
	if (*curc == '+') {return '\0';}
	if (*curc == '?') {return '\0';}
	if (*curc == ')') {return '\0';}
	if (*curc >= ' ' && *curc <= '~') {
		return *curc++;
	}
	return '\0';
}

char
eof () {
	if (*curc == '\0') {
		++curc;
		return 1;
	}
	return 0;
}

extern ast* e0();

//e3:  literal | charclass | '.' | '^' | '$' | '(' e0 ')'
ast *
e3 () {
	ast *t = malloc(sizeof(ast));	
	char c;

	if (match('.')) {
		t->type = DOT;
		t->kids = 0;
	} else if (match('(')) {
		char *revert = curc-1;
		ast *t;
		if ((t = e0())) {
			if (match(')')) {
				return t;
			} 
		} 
		curc = revert;
	}else if ((c = any())) {
		t->data = (ndata) {.lit = c};
		t->type = LIT;
		t->kids = 0;
	} else {
		free(t);
		t =  NULL;
	}
	return t;
}

//REP: '*' | '+' | '?'
//e2:  e3
//|  e2 REP
ast *
e2 () {
	ast *curr = e3();
	for (;;) {
		int min;
		int max;
		
		if (match('*')) {
			min = 0;
			max = LIMIT;
		} else if (match('?')) {
			min = 0;
			max = 2;
		} else if (match('+')) {
			min = 1;
			max = LIMIT;
		} else {
			break;
		}

		ast *next = malloc(sizeof(ast));
		ast **kids = malloc(sizeof(ast*));
		next->size = 1;
		kids[0] = curr;
		next->kids = kids;
		next->data = (ndata) {.rep = {min, max}};
		next->type = REP;
		curr = next;
	}

	return curr;
}


//e1:  e2
//|  e1 e2
ast *
e1 () { 
	vector v;
	mk(&v, sizeof(ast *));

	ast *curr;
	while ((curr = e2())) {
		push(&v, &curr);
	}

	ast *cat = malloc(sizeof(ast));
	cat->size = v.next;
	cat->kids = (ast **) truncate(&v);
	cat->type = CAT;

	return cat;
}

//e0:  e1
//|  e0 '|' e1
ast *
e0 () {
	vector v;
	mk(&v, sizeof(ast *));

	do {
		ast *ptr = e1();
		push(&v, (void *) &ptr);
	} while (match ('|'));
		
	ast *alt = malloc(sizeof(ast)); 
	alt->size = v.next;
	alt->kids = (ast **) truncate(&v);
	alt->type = ALT;

	return alt;
}

int 
main (int argc, char *argv[]) {
	srand(time(0));
	curc = argv[1];
	ast *tree = e0();
	for (;;) {
		gen(tree);
		printf("\n");
	}
}
