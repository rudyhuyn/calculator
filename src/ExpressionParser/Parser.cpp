#include "pch.h"
#include "Parser.h"
#include "BisonGeneratedFiles/BisonParser.tab.hpp"
#include "BisonParserParam.h"
using namespace std;
using namespace yy;
using namespace Platform::Collections;
using namespace CalculationManager;
using namespace ExpressionParser;
using namespace Windows::Foundation::Collections;

IVector<int> ^ CalcExpressionParser::Parse(Platform::String ^ text, ParserMode mode, int base, Platform::String ^ decimalSeparator, Platform::String ^ thousandSeparator)
{
    vector<Lexeme*>* lexemes;
    if (!m_reader.GetLexemes(text->Data(), mode, base, decimalSeparator->Data(), thousandSeparator->Data(), &lexemes))
    {
        return nullptr;
    }
    KeyChained* results = nullptr;
    auto pCallback = std::make_shared<std::function<void(KeyChained* keys)>>();
    *pCallback = [&results](KeyChained* keys) { results = keys; };

    Parser parser(new BisonParserParam({ pCallback, lexemes->begin(), lexemes->end() }));
    if (parser.parse() == 0)
    {
        auto result = ref new Vector<int>();
        KeyChained* currentKey = results;
        while (currentKey != nullptr)
        {
            result->Append(static_cast<int>(currentKey->key));
            currentKey  = currentKey->next;
        }

        return result;
    }
    return nullptr;
}

void yy::Parser::error(const std::string& msg)
{
    printf("error %s\n", msg.c_str());
}
