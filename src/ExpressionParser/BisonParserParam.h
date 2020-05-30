#pragma once
#include "pch.h"
#include "Parser.h"
#include "BisonGeneratedFiles/BisonParser.tab.hpp"

class BisonParserParam
{
public:
    std::shared_ptr<std::function<void(KeyChained*)>> callback;
    std::vector<Lexeme *>::const_iterator iterator;
    std::vector<Lexeme *>::const_iterator endIterator;
};

int yylex(yy::Parser::semantic_type * val, BisonParserParam * param);  /* Called by yyparse on error */
