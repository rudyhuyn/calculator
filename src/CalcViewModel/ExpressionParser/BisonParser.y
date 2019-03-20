%language "c++"
%no-lines
%defines
%lex-param {params}
%parse-param { BisonParserParam * params}
%define "parser_class_name" "Parser"

%token SPACE
%token NUMBER 
%left PROG_XOR 
%token EQU
%left SIN 
%left  COS 
%left  TAN
%left LEFTPARENTHESIS
%token RIGHTPARENTHESIS
%left PLUS
%left MINUS
%left MULTIPLY
%left DIVIDE
%left PROG_NOT
%left PROG_OR
%left PROG_AND
%left CARET
%right POWER2
%right POWER3

%code requires
{
#include "../KeyChained.h"
class BisonParserParam;
}

%union {
    KeyChainedIterator * keys;
	KeyChained * key;
}

%type <keys> command
%type <keys> binary_expr
%type <keys> unary_pre_expr
%type <keys> unary_post_expr
%type <key> binary_operator
%type <key> pre_unary_operator
%type <key> post_unary_operator
%type <key> trigo_function
%type <keys> funcall_expr
%type <keys> prim_expr
%type <keys> Program
%type <keys> NUMBER

%{
#include "pch.h"
#include "../BisonParserParam.h"
#include "Common/CalculatorButtonUser.h"

using namespace std;
using namespace CalculatorApp;

#pragma warning (disable: 4702)
#pragma warning (disable: 4127)
#pragma warning (disable: 4065)
%}
	
%start Program
%%
Program: command
			{
				params->parser->GetResult($1->begin);
			}
    ;

command
	: binary_expr
			{
					$$ = $1;
			}
	| binary_expr EQU
			{
					auto equ = new KeyChained(NumbersAndOperatorsEnum::Equals, nullptr);
					$$ = $1;
					$$->last->next = equ;
					$$->last = equ;
			}
	;

trigo_function
	: SIN
		{
			$$ = new KeyChained(NumbersAndOperatorsEnum::Sin, nullptr);
		}
	| COS
		{
			$$ = new KeyChained(NumbersAndOperatorsEnum::Cos, nullptr);
		}
	| TAN
		{
			$$ = new KeyChained(NumbersAndOperatorsEnum::Tan, nullptr);
		}
	;

binary_operator
    : PLUS
	{
		$$ = new KeyChained(NumbersAndOperatorsEnum::Add, nullptr);
	}
	| MINUS
	{
		$$ = new KeyChained(NumbersAndOperatorsEnum::Subtract, nullptr);
	}
	| MULTIPLY
	{
		$$ = new KeyChained(NumbersAndOperatorsEnum::Multiply, nullptr);
	}
	| DIVIDE
	{
		$$ = new KeyChained(NumbersAndOperatorsEnum::Divide, nullptr);
	}
	| CARET
	{
		$$ = new KeyChained(NumbersAndOperatorsEnum::XPowerY, nullptr);		
	}
	| PROG_AND
	{
		$$ = new KeyChained(NumbersAndOperatorsEnum::And, nullptr);		
	}
	| PROG_OR
	{
		$$ = new KeyChained(NumbersAndOperatorsEnum::Or, nullptr);		
	}
	| PROG_XOR
	{
		$$ = new KeyChained(NumbersAndOperatorsEnum::Xor, nullptr);		
	}
	;

pre_unary_operator
    : MINUS
	{
		$$ = new KeyChained(NumbersAndOperatorsEnum::Negate, nullptr);
	}
	| PROG_NOT
	{
		$$ = new KeyChained(NumbersAndOperatorsEnum::Not, nullptr);
	}
	;

post_unary_operator
    : POWER2
	{
		$$ = new KeyChained(NumbersAndOperatorsEnum::XPower2, nullptr);
	}
	| POWER3
	{
		$$ = new KeyChained(NumbersAndOperatorsEnum::Cube, nullptr);
	}
	;

binary_expr
    : unary_pre_expr
				{ 
					$$ = $1;
				}
    | unary_pre_expr binary_operator binary_expr  
                { 
					$$->begin = $1->begin;
					$1->last->next = $2;
					$2->next = $3->begin;
					$$->last = $3->last;
				}
    ;

unary_pre_expr
	: unary_post_expr
			{
			    $$ = $1;
			}
	| pre_unary_operator unary_post_expr
				{
					$$ = $2;
					$$->last->next = $1;
					$$->last = $1;
				}
unary_post_expr
	: funcall_expr
			{
			    $$ = $1;

			}
	| funcall_expr post_unary_operator
				{
					$$ = $1;
					$$->last->next = $2;
					$$->last = $2;
				}

funcall_expr
    : prim_expr
				{
					$$ = $1;
				}
    | trigo_function LEFTPARENTHESIS binary_expr RIGHTPARENTHESIS
				{
					$3->begin = new KeyChained(NumbersAndOperatorsEnum::OpenParenthesis, $3->begin);
					$$ = $3;
				    $3->last->next = new KeyChained(NumbersAndOperatorsEnum::CloseParenthesis, $1);
					$$->last = $1;
				}
    ;

prim_expr
    : NUMBER  
	{
			$$ = $1;
	}
    | LEFTPARENTHESIS binary_expr RIGHTPARENTHESIS
				{
					auto close_parenthesis = new KeyChained(NumbersAndOperatorsEnum::CloseParenthesis, nullptr);

					$2->begin = new KeyChained(NumbersAndOperatorsEnum::OpenParenthesis, $2->begin);
					$$ = $2;
				    $2->last->next = close_parenthesis;
					$$->last = close_parenthesis;
				}
    ;
	
%%
