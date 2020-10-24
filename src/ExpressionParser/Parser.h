#pragma once
#include "pch.h"
#include "Lexer.h"
#include "KeyChained.h"

namespace ExpressionParser
{
public
    ref class CalcExpressionParser sealed
    {
    public:
        Windows::Foundation::Collections::IVector<int> ^ Parse(Platform::String ^ text, ParserMode mode, int base, Platform::String ^ decimalSeparator, Platform::String ^ thousandSeparator);
    private:
        LexemeReader m_reader;
    };
}
