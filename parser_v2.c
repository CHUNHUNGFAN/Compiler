/*
* Copyright 2010 Yihjia Tsai */
#include <stdio.h> 
#include <string.h> 
#define BUFSIZE 1024

void S();
void E();
void Etail();
void T();
void Ttail();
void F();
char ibuf[BUFSIZE]={0}; 
int cpos=0;

char getToken() {
	char tok;
	tok=ibuf[cpos];
	while( tok == ' ' || tok == '\t') {
		cpos++; tok=ibuf[cpos]; 
	}
	return tok; 
}

int match(char c) {
	char tok = getToken(); cpos++;
	if(tok == c) { 
		return 1; 
	} 
	else { 
		return 0; 
	}
}

void error(const char msg[]) { 
	printf(msg); 
}

/*
* S -> E$
* E -> T Etail
* Etail -> '+' T Etail * Etail -> ε
* T -> F Ttail
* Ttail -> '*' F Ttail * Ttail -> ε
* F -> id
* F -> '(' E ')'
*/

/* New Rules
*expr -> rel = expr
*expr -> rel
*rel -> add rel-R
*rel-R -> '<' add rel-R
*rel-R -> "<=" add rel-R
*rel-R -> ε
*/


/*S->E$ */ 
void S() {
	char tok;
	printf("S -> E\n");
	E();
	tok = getToken();
	if (tok == '$') { 
		match('$'); 
		printf("END$\n"); 
	}
}

/*E->TEtail */ 
void E() {
	printf("E -> T and Etail\n"); 
	T();
	Etail();
}

/* Etail -> '+' T Etail * Etail -> ε*/
void Etail() {
	char tok = getToken();
	switch(tok) {
		case '+': match('+') ;
				  printf("Etail -> '+' and T and Etail\n"); 
				  T(); 
				  Etail(); 
				  break; 
		default: printf("Etail -> ε\n");
	} 
}

/*T->FTtail */ 
void T() {
	printf("T -> F and Ttail\n"); 
	F();
	Ttail();
}

/* Ttail -> '*' F Ttail * Ttail -> ε
*/
void Ttail() {
	char tok = getToken(); 
	switch(tok) {
		case '*': match('*') ;
				  printf("Ttail -> '*' and F and Ttail\n"); 
				  F(); 
				  Ttail(); 
				  break;
		default: printf("Ttail -> ε\n"); }
}

/* F -> '(' E ')' * F -> id
*/
void F() {
	char tok = getToken(); 
	switch(tok) {
		case '(': match('(') ;
				  printf("( "); 
				  E(); 
				  printf(" )\n");
				  tok = getToken(); 
				  match(')'); 
				  break; 
		case 'a': match('a') ; 
				  printf("F -> a\n"); 
				  break;
		case 'b': match('b');
				  printf("F -> b\n");
				  break;
	} 
}

int main() {
	int len;
	fgets(ibuf,BUFSIZE,stdin);
	len = strlen(ibuf); 
	if (ibuf[len-1]	== '\n'){ 
		ibuf[len-1] = 0; 
		len--; 
	} 
	printf("[%s]\n", ibuf);
	S();
}
