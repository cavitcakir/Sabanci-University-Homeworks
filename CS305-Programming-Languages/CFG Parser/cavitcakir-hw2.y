%{
#include <stdio.h>
int yylex();
void yyerror (const char *s)
{
  //printf ("%s\n", s);
}
%}

%token tINTVECTORTYPE tINTMATRIXTYPE tINTTYPE tREALVECTORTYPE tREALMATRIXTYPE tREALTYPE tTRANSPOSE tIDENT tDOTPROD tIF tENDIF tREALNUM tINTNUM tAND tOR tGT tLT tGTE tLTE tNE tEQ

%left tOR
%left tAND
%left '+' '-'
%left '/' '*'
%left tDOTPROD
%left tTRANSPOSE

%%

prog: stmtlst
;
stmtlst:  stmt
        | stmt stmtlst
;

stmt:     decl
        | asgn
        | if
;

decl: type vars '=' expr ';'
;

type:     tINTTYPE
        | tINTVECTORTYPE
        | tINTMATRIXTYPE
        | tREALTYPE
        | tREALVECTORTYPE
        | tREALMATRIXTYPE
;

vars:     tIDENT ',' vars
        | tIDENT
;

asgn: tIDENT '=' expr ';'
;

if: tIF '(' bool ')' stmtlst tENDIF
;

expr:     value
        | vectorLit
        | matrixLit
        | expr '+' expr
        | expr '*' expr
        | expr '-' expr
        | expr '/' expr
        | expr tDOTPROD expr
        | transpose
;

transpose: tTRANSPOSE '(' expr ')'
;

vectorLit: '[' row ']'
;

matrixLit: '[' rows ']'
;

row:   value ',' row
     | value
;

rows:   row ';' rows
      | row ';' row
;

value:    tIDENT
        | tINTNUM
        | tREALNUM
;

bool:     comp
        | comp tAND comp
        | comp tOR comp
;

comp:   tIDENT relation tIDENT
;

relation:   tGT
          | tLT
          | tGTE
          | tLTE
          | tNE
          | tEQ
;



%%

int main ()
{
  if (yyparse()) {
    printf("ERROR\n");
    return 1;
  }
  else {
    printf("OK\n");
    return 0;
  }
}
