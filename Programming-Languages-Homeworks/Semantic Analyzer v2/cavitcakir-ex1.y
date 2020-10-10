%{
#include <stdio.h>
#include <stdlib.h>
#include "cavitcakir-ex1.h"

extern int yylineno;

void yyerror (const char *s)
{
	//printf ("%s\n", s);
}

int yylex();

int error_code = 0;
int error_line = 0;

my_node globalVariables[50000];
int globalLength = 0;
my_node localVariables[50000];
int localLength = 0;

int checkGlobal(char * );
int checkLocal(char * );

%}

%locations

%union {
  struct my_node node_union;
}


%token tINT tSTRING tRETURN tPRINT tLPAR tCOMMA tASSIGNM tPLUS tSTAR tLBRAC tRPAR tMOD tMINUS tDIV tSEMI tRBRAC tSTRINGVAL tINTVAL

%token <node_union> tIDENT
%type <node_union> decl localdecl

%left tPLUS tMINUS
%left tSTAR tDIV tMOD




%start prog

%%
prog:				stmtlst
;
stmtlst:		stmtlst stmt
						| stmt
;
stmt:       funcdef
            | decl
						| asgn
						| print
;
decl:				type tIDENT tASSIGNM expr tSEMI {
																						if(checkGlobal($2.ident)){
																							error_code = 1; // redecleration
																							error_line = yylineno;
																							return 0;
																						}
																						else{
																							globalVariables[globalLength] = $2;
																							globalLength++;
																						}
																					}
;

type:				tINT
						| tSTRING
;

expr:				tSTRINGVAL
						| tINTVAL
						| tMINUS tINTVAL
            | expr tSTAR expr
            | expr tDIV expr
            | expr tPLUS expr
            | expr tMINUS expr
            | expr tMOD expr
						| funccall
						| tIDENT{
							if(!checkGlobal($1.ident) && !checkLocal($1.ident)) {
								error_line = yylineno;
								error_code = 2;
								return 0;
							}
						}
;


exprparam:	tSTRINGVAL
						| tINTVAL
						| tMINUS tINTVAL
            | expr tSTAR expr
            | expr tDIV expr
            | expr tPLUS expr
            | expr tMOD expr
            | expr tMINUS expr
						| funccall
						| tIDENT
;

funccall: tIDENT tLPAR param tRPAR
					| tIDENT tLPAR tRPAR

;

param:  exprparam
			 | exprparam tCOMMA param
;

asgn:	tIDENT tASSIGNM expr tSEMI{
															if(!checkGlobal($1.ident) && !checkLocal($1.ident)) {
																error_line = yylineno;
																error_code = 2;
																return 0;
															}
														}
;

funcdef: type tIDENT tLPAR formalparam tRPAR tLBRAC funcbodylst tRETURN expr tSEMI tRBRAC {localLength =0 ;}
				 | type tIDENT tLPAR tRPAR tLBRAC funcbodylst tRETURN expr tSEMI tRBRAC {localLength = 0; }
				 | type tIDENT tLPAR formalparam tRPAR tLBRAC  tRETURN expr tSEMI tRBRAC {localLength =0 ;}
				 | type tIDENT tLPAR tRPAR tLBRAC  tRETURN expr tSEMI tRBRAC {localLength = 0; }

;

funcbodylst: funcbodylst funcbody
						| funcbody
;
funcbody:     localdecl
						| asgn
						| print
;
localdecl: type tIDENT tASSIGNM expr tSEMI{
																						if(checkLocal($2.ident)){
																							error_code = 1; // redecleration
																							error_line = yylineno;
																							return 0;
																						}
																						else{
																							localVariables[localLength] = $2;
																							localLength++;
																						}
																					}
;


formalparam: type tIDENT{
																 if(checkGlobal($2.ident) || checkLocal($2.ident)){
																	 error_code = 1; // redecleration
																	 error_line = yylineno;
																	 return 0;
																 }
																 else{
																	 localVariables[localLength] = $2;
																	 localLength++;
																 }
															 }
			 | type tIDENT tCOMMA formalparam {
																				if(checkGlobal($2.ident)|| checkLocal($2.ident)){
																					error_code = 1; // redecleration
																					error_line = yylineno;
																					return 0;
																				}
																				else{
																					localVariables[localLength] = $2;
																					localLength++;
																				}
																			}
;

print: tPRINT tLPAR expr tRPAR tSEMI
;

%%

int checkLocal(char * temp){
	int i ;
	size_t lenTemp = strlen(temp);
	for ( i = 0; i < localLength; i++) {
		size_t lenLocalVar = strlen(localVariables[i].ident);
		if(lenTemp == lenLocalVar){
			int j;
			for (j = 0; j < lenTemp; j++) {
				if((temp[j] != localVariables[i].ident[j])) break;
				else if((temp[j] == localVariables[i].ident[j]) && (j == lenTemp-1)) return 1;
			}
		}
	}
	return 0;
}

int checkGlobal(char * temp){
	int i ;
	size_t lenTemp = strlen(temp);
	for ( i = 0; i < globalLength; i++) {
		size_t lenGlobalVar = strlen(globalVariables[i].ident);
		if(lenTemp == lenGlobalVar){
			int j;
			for (j = 0; j < lenTemp; j++) {
				if((temp[j] != globalVariables[i].ident[j])) break;
				else if((temp[j] == globalVariables[i].ident[j]) && (j == lenTemp-1)) return 1;
			}
		}
	}
	return 0;
}



int main ()
{
   if (yyparse()) {
   // parse error
       printf("ERROR\n");
       return 1;
   }
   else {
   // successful parsing
	 	if(error_code == 0){
      printf("OK\n");
		}
		else if(error_code == 1){
			printf("%i Redefinition of variable \n",error_line);
		}
		else{
			printf("%i Undefined variable \n",error_line);
		}
      return 0;
   }
}
