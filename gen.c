#include "gen.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void
gen (ast *t) {
	switch (t -> type) {
	case LIT:
		printf("%c", (t->data).lit);
		break;
	case CLASS:
		;
		int r = rand();
		int n = (t -> data).charclass.number;
		char c = (t -> data).charclass.letters[r%n];	
		printf("%c", c);
		break;
	case DOT:
		;
		c = (char) (rand()%( '~' + 1 - ' ') + 32);
		printf("%c", c);
		break;
	case REP:
		;
		int min = (t->data).rep[0];
		int max = (t->data).rep[1];
		r = rand() % (max-min);
		for (int i = 0; i < min + r; ++i) {
			gen((t -> kids)[0]);
		}
		break;	
	case ALT:
		;
		r = rand() % (t->size);
		gen((t -> kids)[r]);
		break;
	case CAT:
		for (int i = 0; i < t->size; ++i) {
			gen((t->kids)[i]);
		}	
		break;
	default:
		break;
	}
}

void
run (ast *t) {
	gen(t);
	printf("\n");
}

void
show_aux (int tabs, ast *t) {
	for (int i = 0; i < tabs; ++i) 
		printf("\t");
	switch (t->type) {
	case LIT:
		printf("LIT\n");
		return;
	case CLASS:
		printf("CLASS\n");
		return;
	case DOT:
		printf("DOT\n");
		return;
	case REP:
		printf("REP\n");
		break;
	case ALT:
		printf("ALT\n");
		break;
	case CAT:
		printf("CAT\n");
		break;
	default:
		return;
	}
	for (int i = 0; i < t->size; ++i) 
		show_aux(tabs+1, (t->kids)[i]);
}

void
show (ast *t) {
	show_aux(0, t);
}
