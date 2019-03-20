#pragma once
#include "Lexer.h"
#include "KeyChained.h"

class CalcExpressionParser
{
public:
    ~CalcExpressionParser();
    bool Parse(std::wstring text);
    void GetResult(KeyChained *keys);
private:
    LexemeReader m_reader;
};

