%{
#include <stdio.h>
#include "cavitcakir-hw3.h"


void yyerror (const char *s)
{
	printf ("%s\n", s);
}

int yylex();

int error_code = 0;
int error_line = 0;

my_node add_op(my_node, my_node);
my_node sub_op(my_node, my_node);
my_node div_op(my_node, my_node);
my_node mult_op(my_node, my_node);
my_node dot_op(my_node, my_node);

%}


%union {
	int value;
  struct my_node Node_union;
}

%token tINTTYPE tINTVECTORTYPE tINTMATRIXTYPE tREALTYPE tREALVECTORTYPE tREALMATRIXTYPE tTRANSPOSE tIDENT tDOTPROD tIF tENDIF tREALNUM tINTNUM tAND tOR tGT tLT tGTE tLTE tNE tEQ

%left '='
%left tOR
%left tAND
%left tEQ tNE
%left tLTE tGTE tLT tGT
%left '+' '-'
%left '*' '/'
%left tDOTPROD
%left '(' ')'
%left tTRANSPOSE

%type <Node_union> expr
%type <Node_union> row
%type <Node_union> rows
%type <Node_union> matrixLit
%type <Node_union> vectorLit
%type <Node_union> transpose


%start prog

%%


prog:				stmtlst
;
stmtlst:		stmtlst stmt
						| stmt
;
stmt:       decl
            | asgn
            | if
;
decl:				type vars '=' expr ';'
;
asgn:				tIDENT '=' expr ';'
;
if:					tIF '(' bool ')' stmtlst tENDIF
;
type:				tINTTYPE
						| tINTVECTORTYPE
            | tINTMATRIXTYPE
            | tREALTYPE
            | tREALVECTORTYPE
            | tREALMATRIXTYPE
;
vars:				vars ',' tIDENT
						| tIDENT
;
expr:				value {$$.Row = 1; $$.Col = 1; $$.Type = SCA;}
						| vectorLit {$$ = $1;}
  					| matrixLit {$$ = $1;}
            | expr	'*' expr { $$ = mult_op($1,$3); if(error_code){error_line = line_count; return 0;} }
            | expr	'/' expr { $$ = div_op($1,$3); if(error_code){error_line = line_count; return 0;} }
            | expr	'+' expr { $$ = add_op($1,$3); if(error_code){error_line = line_count; return 0;} }
            | expr	'-' expr { $$ = add_op($1,$3); if(error_code){error_line = line_count; return 0;} }
            | expr tDOTPROD expr { $$ = dot_op($1,$3); if(error_code){error_line = line_count; return 0;} }
						| transpose {$$ = $1;}
;
transpose: 	tTRANSPOSE '(' expr ')' { $$ = $3; if($3.Type != SCA){$$.Row = $3.Col; $$.Col = $3.Row;}}
;
vectorLit:	'[' row ']' {$$ = $2; $$.Type = VEC;}
;
row:				row ',' value			{$$ = $1; $$.Col += 1;}
						| value 					{$$.Col = 1; $$.Row = 1; $$.Type = ROW;}
;
matrixLit: 	'[' rows ']' {$$ = $2; $$.Type = MAT;}
;
rows:				row ';' row 			{	if($1.Col != $3.Col){
																error_code = 1;
																error_line = line_count;
																return 0;
															}
															$$.Row = 2; $$.Col = $1.Col; $$.Type = ROWS;
														}
						| rows ';' row 		{$$ = $1; $$.Row += 1;
															if($1.Col != $3.Col){
																error_code = 1;
																error_line = line_count;
																return 0;
															}}
;
value:			tINTNUM
						| tREALNUM
;
bool: 			comp
						| bool tAND bool
						| bool tOR bool
;
comp:				tIDENT relation tIDENT
;
relation:		tGT
						| tLT
						| tGTE
            | tLTE
						| tEQ
						| tNE
;

%%


my_node add_op(my_node lhs, my_node rhs){
	my_node dummy;
	int is_okay = 1;

	if(lhs.Type == SCA && rhs.Type == SCA){
		dummy = lhs;
	}
	else if(lhs.Type != SCA && rhs.Type != SCA){
		if(lhs.Row == rhs.Row && lhs.Col == rhs.Col){
			dummy = lhs;
		}
		else{
			is_okay = 0;
		}
	}
	else if(lhs.Type == SCA && rhs.Type != SCA){
		is_okay = 0;
	}
	else{
		is_okay = 0;
	}
	if(!is_okay){
		error_code = 2;
		dummy.Row = -1;
		dummy.Col = -1;
	}
	return dummy;
}

my_node mult_op(my_node lhs, my_node rhs){
	my_node dummy;
	int is_okay = 1;

	if(lhs.Type == SCA && rhs.Type == SCA){
		dummy = lhs;
	}
	else if(lhs.Type != SCA && rhs.Type != SCA){
		if (lhs.Col == rhs.Row) {
			dummy.Row = lhs.Row;
			dummy.Col = rhs.Col;
		}
		else{
			is_okay = 0;
		}
	}
	else if(lhs.Type == SCA && rhs.Type != SCA){
		dummy = rhs;
	}
	else{
		dummy = lhs;
	}
	if(!is_okay){
		error_code = 2;
		dummy.Row = -1;
		dummy.Col = -1;
	}
	return dummy;
}

my_node div_op(my_node lhs, my_node rhs){
	my_node dummy;
	int is_okay = 1;

	if(lhs.Type == SCA && rhs.Type == SCA){
		dummy = lhs;
	}
	else if(lhs.Type != SCA && rhs.Type != SCA){
		if(lhs.Col == rhs.Row && lhs.Col == rhs.Col){
			dummy = rhs;
		}else{
			is_okay = 0;
		}
	}
	else if(lhs.Type == SCA && rhs.Type != SCA){
		dummy = rhs;
	}
	else{
		if(rhs.Col == rhs.Row){
			dummy = rhs;
		}
		else{
			is_okay = 0;
		}
	}
	if(!is_okay){
		error_code = 2;
		dummy.Row = -1;
		dummy.Col = -1;
	}
	return dummy;
}

my_node dot_op(my_node lhs, my_node rhs){
	my_node dummy;
	int is_okay = 1;

	if(lhs.Type == SCA && rhs.Type == SCA){
		is_okay = 0;
	}
	else if(lhs.Type != SCA && rhs.Type != SCA){
		if(lhs.Row == 1 && rhs.Row == 1){
			dummy.Row = 1;
			dummy.Col = 1;
			dummy.Type = SCA;
		}else{
			is_okay = 0;
		}
	}
	else if(lhs.Type == SCA && rhs.Type != SCA){
		is_okay = 0;
	}
	else{
		is_okay = 0;
	}
	if(!is_okay){
		error_code = 2;
		dummy.Row = -1;
		dummy.Col = -1;
	}
	return dummy;
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
			printf("ERROR 1: %i inconsistent matrix size \n",error_line);
		}
		else{
			printf("ERROR 2: %i dimension mismatch \n",error_line);
		}
      return 0;
   }
}
