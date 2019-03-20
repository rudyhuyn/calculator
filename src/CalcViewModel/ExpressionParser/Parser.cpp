#include "pch.h"
#include "Parser.h"
#include "BisonGeneratedFiles/BisonParser.hpp"
#include "BisonParserParam.h"
using namespace std;

CalcExpressionParser::~CalcExpressionParser()
{
}

bool CalcExpressionParser::Parse(wstring text)
{
    vector<Lexeme*>* lexemes;
    if (!m_reader.GetLexemes(text, &lexemes))
    {
        return false;
    }
    auto parser = yy::Parser(new BisonParserParam({this, lexemes->begin(), lexemes->end()}));
    parser.parse();
    return true;
}

void CalcExpressionParser::GetResult(KeyChained *keys)
{
    KeyChained *current = keys;
    while (current != nullptr)
    {
        std::wcout << current->key.data() << std::endl;
        current = current->next;
    }
}


void yy::Parser::error(const location_type& /*loc*/, const std::string& msg)
{
    printf("error %s\n", msg.c_str());
}