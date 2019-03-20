#pragma once
#include "Parser.h"
#include "BisonGeneratedFiles/BisonParser.hpp"

class BisonParserParam
{
public:
    CalcExpressionParser * parser;
    std::vector<Lexeme *>::const_iterator iterator;
    std::vector<Lexeme *>::const_iterator endIterator;
};


int yylex(yy::Parser::semantic_type * val, BisonParserParam * param);  /* Called by yyparse on error */
