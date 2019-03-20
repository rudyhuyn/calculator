#pragma once
#include "Lexer.h"
#include "KeyChained.h"
#include "Common/NavCategory.h"

class CalcExpressionParser
{
public:
    ~CalcExpressionParser();
    std::vector<CalculatorApp::NumbersAndOperatorsEnum> * Parse(std::wstring text, CalculatorApp::Common::ViewMode mode, int base, const std::wstring &decimalSeparator, const std::wstring &thousandSeparator);
    void GetResult(KeyChained *keys);
private:
    LexemeReader m_reader;
    KeyChained * m_resultReceived;

};

