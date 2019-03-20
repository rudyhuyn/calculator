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
using namespace std;
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
					auto equ = new KeyChained(std::wstring(L"EQU"), nullptr);
					$$ = $1;
					$$->last->next = equ;
					$$->last = equ;
			}
	;

trigo_function
	: SIN
		{
			$$ = new KeyChained(std::wstring(L"SIN"), nullptr);
		}
	| COS
		{
			$$ = new KeyChained(std::wstring(L"COS"), nullptr);
		}
	| TAN
		{
			$$ = new KeyChained(std::wstring(L"TAN"), nullptr);
		}
	;

binary_operator
    : PLUS
	{
		$$ = new KeyChained(std::wstring(L"PLUS"), nullptr);
	}
	| MINUS
	{
		$$ = new KeyChained(std::wstring(L"MINUS"), nullptr);
	}
	| MULTIPLY
	{
		$$ = new KeyChained(std::wstring(L"MULTIPLY"), nullptr);
	}
	| DIVIDE
	{
		$$ = new KeyChained(std::wstring(L"DIVIDE"), nullptr);
	}
	| CARET
	{
		$$ = new KeyChained(std::wstring(L"POWER"), nullptr);		
	}
	| PROG_AND
	{
		$$ = new KeyChained(std::wstring(L"BIN_AND"), nullptr);		
	}
	| PROG_OR
	{
		$$ = new KeyChained(std::wstring(L"BIN_OR"), nullptr);		
	}
	| PROG_XOR
	{
		$$ = new KeyChained(std::wstring(L"BIN_XOR"), nullptr);		
	}
	;

pre_unary_operator
    : MINUS
	{
		$$ = new KeyChained(std::wstring(L"MINUSNEG"), nullptr);
	}
	| PROG_NOT
	{
		$$ = new KeyChained(std::wstring(L"BINARYNOT"), nullptr);
	}
	;

post_unary_operator
    : POWER2
	{
		$$ = new KeyChained(std::wstring(L"POWER2"), nullptr);
	}
	| POWER3
	{
		$$ = new KeyChained(std::wstring(L"POWER3"), nullptr);
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
					$3->begin = new KeyChained(std::wstring(L"OPEN_PARENTHESE"), $3->begin);
					$$ = $3;
				    $3->last->next = new KeyChained(std::wstring(L"CLOSE_PARENTHESE"), $1);
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
					auto close_parenthesis = new KeyChained(std::wstring(L"CLOSE_PARENTHESE"), nullptr);

					$2->begin = new KeyChained(std::wstring(L"OPEN_PARENTHESE"), $2->begin);
					$$ = $2;
				    $2->last->next = close_parenthesis;
					$$->last = close_parenthesis;
				}
    ;
	
%%