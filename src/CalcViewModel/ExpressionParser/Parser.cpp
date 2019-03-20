#include "pch.h"
#include "Parser.h"
#include "BisonGeneratedFiles/BisonParser.hpp"
#include "BisonParserParam.h"
using namespace std;
using namespace CalculatorApp::Common;

CalcExpressionParser::~CalcExpressionParser()
{
}

vector<CalculatorApp::NumbersAndOperatorsEnum> * CalcExpressionParser::Parse(wstring text, ViewMode mode, int base, const std::wstring &decimalSeparator, const std::wstring &thousandSeparator)
{
    m_resultReceived = nullptr;
    vector<Lexeme*>* lexemes;
    if (!m_reader.GetLexemes(text, mode, base, decimalSeparator, thousandSeparator, &lexemes))
    {
        return nullptr;
    }
    auto parser = yy::Parser(new BisonParserParam({this, lexemes->begin(), lexemes->end()}));
    if (parser.parse() == 0)
    {
        //Convert to a std::vector

        vector<CalculatorApp::NumbersAndOperatorsEnum> * result = new vector<CalculatorApp::NumbersAndOperatorsEnum>();
        KeyChained * currentKey = m_resultReceived;
        while (currentKey != nullptr)
        {
            result->push_back(currentKey->key);
            currentKey  = currentKey->next;
        }

        return result;
    }
    return nullptr;
}

void CalcExpressionParser::GetResult(KeyChained *keys)
{
    //TODO: change how we get the result and send it to Parse(wstring)
    m_resultReceived = keys;
}


void yy::Parser::error(const location_type& /*loc*/, const std::string& msg)
{
    printf("error %s\n", msg.c_str());
}
