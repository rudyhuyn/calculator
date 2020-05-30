#include "pch.h"
#include "Lexer.h"
#include "BisonGeneratedFiles/BisonParser.tab.hpp"

using namespace std;
using namespace ExpressionParser;

#define yytokentype yy::Parser::token

static const wstring c_uIntSuffixes = L"[uU]?[lL]{0,2}";

vector<LexInfo*> const lexemeRulesBase({
    new LexInfoChar(yytokentype::PLUS, L'+'),
    new LexInfoChar(yytokentype::MINUS, L'-'),
    new LexInfoChar(yytokentype::DIVIDE, L'/'),
    new LexInfoChar(yytokentype::DIVIDE, 247 /* ÷ */),
    new LexInfoChar(yytokentype::MULTIPLY, L'*'),
    new LexInfoChar(yytokentype::MULTIPLY, 215 /*'×'*/),
    new LexInfoRegex(yytokentype::SPACE, L"\\s+"),
    new LexInfoChar(yytokentype::EQU, L'='),
});

vector<LexInfo*> const lexemeRulesNormal({
    new LexInfoChar(yytokentype::POWER2, 253),
    new LexInfoChar(yytokentype::POWER3, 254),
    new LexInfoChar(yytokentype::POWER2, 178),
    new LexInfoChar(yytokentype::POWER3, 179),
});

vector<LexInfo*> const lexemeRulesProg({
    new LexInfoChar(yytokentype::LEFTPARENTHESIS, L'('),
    new LexInfoChar(yytokentype::RIGHTPARENTHESIS, L')'),
    new LexInfoChar(yytokentype::PROG_AND, L'&'),
    new LexInfoChar(yytokentype::PROG_OR, L'|'),
    new LexInfoChar(yytokentype::PROG_XOR, L'^'),
    new LexInfoChar(yytokentype::PROG_NOT, L'~'),
    new LexInfoString(yytokentype::PROG_AND, L"and"),
    new LexInfoString(yytokentype::PROG_NAND, L"nand"),
    new LexInfoString(yytokentype::PROG_OR, L"or"),
    new LexInfoString(yytokentype::PROG_OR, L"nor"),
    new LexInfoString(yytokentype::PROG_XOR, L"xor"),
    new LexInfoString(yytokentype::PROG_NOT, L"not"),
    new LexInfoString(yytokentype::BITSHIFTLEFT, L"<<"),
    new LexInfoString(yytokentype::BITSHIFTRIGHT, L">>"),
});

vector<LexInfo*> const lexemeRulesScientific({
    new LexInfoChar(yytokentype::LEFTPARENTHESIS, L'('),
    new LexInfoChar(yytokentype::RIGHTPARENTHESIS, L')'),
    new LexInfoChar(yytokentype::CARET, L'^'),
    new LexInfoString(yytokentype::SIN, L"sin"),
    new LexInfoString(yytokentype::COS, L"cos"),
    new LexInfoString(yytokentype::TAN, L"tan"),
    new LexInfoString(yytokentype::LOG, L"log"),
    new LexInfoString(yytokentype::LN, L"ln"),
    new LexInfoString(yytokentype::MOD, L"mod"),
    new LexInfoString(yytokentype::PI, L"pi"),
    new LexInfoString(yytokentype::PI, L"π"),
    new LexInfoString(yytokentype::EULER, L"e"),

});

int LexInfoChar::CheckLex(const wstring::const_iterator& begin, const wstring::const_iterator& /*end*/)
{
    if (*begin == m_character)
    {
        return 1;
    }
    return -1;
}
bool LexInfoString::CaseInsensitiveCompare(wchar_t a, wchar_t b)
{
    return tolower(a) == tolower(b);
}

int LexInfoString::CheckLex(const wstring::const_iterator& begin, const wstring::const_iterator& end)
{
    if (m_refTextCachedSize <= end - begin && equal(m_refText.begin(), m_refText.end(), begin, &CaseInsensitiveCompare))
    {
        return m_refTextCachedSize;
    }
    return -1;
}

int LexInfoRegex::CheckLex(const wstring::const_iterator& begin, const wstring::const_iterator& end)
{
    wsmatch match;
    if (regex_search(begin, end, match, m_regex, regex_constants::match_continuous))
        return static_cast<int>(match.length());
    return -1;
}

int LexemeReader::ParseNumber(
    const wstring::const_iterator& begin,
    const wstring::const_iterator& end,
    ParserMode mode,
    int base,
    const std::wstring& decimalSeparator,
    const std::wstring& thousandSeparator,
    std::vector<CalculationManager::Command>** keys)
{
    *keys = nullptr;
    wsmatch match;

    wchar_t decimalSeparatorChar = decimalSeparator[0];
    wchar_t digitGroupingChar = thousandSeparator[0];
    wstring prefixToIgnore = L"";
    vector<wregex> regNumberToUse;
    switch (mode)
    {
    case ParserMode::Standard:
    {
        // Use [0-9] instead of \d because \d matches also square and cube signs
        std::wregex regexNumberDecimal((L"(?:[0-9]+|(?:[0-9]*(?:\\" + decimalSeparatorChar + L"[0-9]+)))")->Data());
        regNumberToUse.push_back(regexNumberDecimal);
        break;
    }
    case ParserMode::Scientific:
    {
        std::wregex regexNumberDecimalExtended((L"("
                                                "([0-9]{0,3}(?:\\"
                                                + digitGroupingChar + L"[0-9]{2,3})+(\\" + decimalSeparatorChar
                                                + L"[0-9]+)?)|"
                                                  "([0-9]*\\"
                                                + decimalSeparatorChar
                                                + L"[0-9]+)|"
                                                  "([0-9]+\\"
                                                + decimalSeparatorChar
                                                + L"?)"
                                                  ")"
                                                  "(e[+-]?[0-9]+)?")
                                                   ->Data());
        regNumberToUse.push_back(regexNumberDecimalExtended);
    }
    case ParserMode::Programmer:
    {
        switch (base)
        {
        case 10:
        {
            // Decimal numbers like 145, 0n145, 123ull etc
            wstring decProgrammerChars = L"[0-9]+((_|'|`)[0-9]+)*";
            regNumberToUse.push_back(wregex(decProgrammerChars + c_uIntSuffixes));
            regNumberToUse.push_back(wregex(L"(0[nN])?" + decProgrammerChars));
            break;
        }
        case 16:
        {
            // Hex numbers like 5F, 4A0C, 0xa9, 0xFFull, 47CDh
            wstring hexaProgrammersChars = L"[0-9a-fA-F]+((_|'|`)[0-9a-fA-F]+)*";
            regNumberToUse.push_back(wregex(hexaProgrammersChars + L"[hH]?"));
            regNumberToUse.push_back(wregex(L"(0[xX])?" + hexaProgrammersChars + c_uIntSuffixes));
            break;
        }
        case 8:
        {
            // Octal numbers like 06, 010, 0t77, 0o77, 077ull etc
            wstring octoProgrammersChars = L"[0-7]+((_|'|`)[0-7]+)*";
            regNumberToUse.push_back(wregex(L"(0[otOT])?" + octoProgrammersChars + c_uIntSuffixes));
            break;
        }
        case 2:
        {
            // Binary numbers like 011010110, 0010110, 10101001, 1001b, 0b1001, 0y1001, 0b1001ull
            wstring binProgrammersChars = L"[0-1]+((_|'|`)[0-1]+)*";
            regNumberToUse.push_back(wregex(L"(0[byBY])?" + binProgrammersChars + c_uIntSuffixes));
            regNumberToUse.push_back(wregex(binProgrammersChars + L"[bB]?"));
            break;
        }
        }
        break;
    }
    default:
    {
        regNumberToUse.push_back(wregex(L"[0-9]+"));
        break;
    }
    }

    for (auto& regNumber : regNumberToUse)
    {
        if (regex_search(begin, end, match, regNumber, regex_constants::match_continuous))
        {
            *keys = new std::vector<CalculationManager::Command>();
            std::wstring numberFound = match.str();
            for (auto& c : numberFound)
            {
                if (c == digitGroupingChar)
                    continue;
                if (c == decimalSeparatorChar)
                {
                    (*keys)->push_back(CalculationManager::Command::CommandPNT);
                    continue;
                }
                switch (tolower(c))
                {
                case '0':
                    (*keys)->push_back(CalculationManager::Command::Command0);
                    break;
                case '1':
                    (*keys)->push_back(CalculationManager::Command::Command1);
                    break;
                case '2':
                    (*keys)->push_back(CalculationManager::Command::Command2);
                    break;
                case '3':
                    (*keys)->push_back(CalculationManager::Command::Command3);
                    break;
                case '4':
                    (*keys)->push_back(CalculationManager::Command::Command4);
                    break;
                case '5':
                    (*keys)->push_back(CalculationManager::Command::Command5);
                    break;
                case '6':
                    (*keys)->push_back(CalculationManager::Command::Command6);
                    break;
                case '7':
                    (*keys)->push_back(CalculationManager::Command::Command7);
                    break;
                case '8':
                    (*keys)->push_back(CalculationManager::Command::Command8);
                    break;
                case '9':
                    (*keys)->push_back(CalculationManager::Command::Command9);
                    break;
                case 'a':
                    (*keys)->push_back(CalculationManager::Command::CommandA);
                    break;
                case 'b':
                    (*keys)->push_back(CalculationManager::Command::CommandB);
                    break;
                case 'c':
                    (*keys)->push_back(CalculationManager::Command::CommandC);
                    break;
                case 'd':
                    (*keys)->push_back(CalculationManager::Command::CommandD);
                    break;
                case 'f':
                    (*keys)->push_back(CalculationManager::Command::CommandF);
                    break;
                case 'e':
                    if (mode == ParserMode::Programmer)
                    {
                        (*keys)->push_back(CalculationManager::Command::CommandE);
                    }
                    else
                    {
                        (*keys)->push_back(CalculationManager::Command::CommandEXP);
                    }
                    break;
                case '-':
                    (*keys)->push_back(CalculationManager::Command::CommandSIGN);
                    break;
                }
            }

            return static_cast<int>(numberFound.length());
        }
    }
    return -1;
}

bool LexemeReader::GetLexemes(
    wstring item,
    ParserMode mode,
    int base,
    const std::wstring& decimalSeparator,
    const std::wstring& thousandSeparator,
    vector<Lexeme*>** lexemes)
{
    *lexemes = nullptr;
    vector<Lexeme*>* result = new vector<Lexeme*>();
    wstring::const_iterator currentPos = item.begin();
    wstring::const_iterator end = item.end();

    vector<vector<LexInfo*>> lexemesCollections{};
    switch (mode)
    {
    case ParserMode::Scientific:
    {
        lexemesCollections.push_back(lexemeRulesBase);
        lexemesCollections.push_back(lexemeRulesNormal);
        lexemesCollections.push_back(lexemeRulesScientific);
    }
    break;
    case ParserMode::Programmer:
    {
        lexemesCollections.push_back(lexemeRulesBase);
        lexemesCollections.push_back(lexemeRulesNormal);
        lexemesCollections.push_back(lexemeRulesProg);
    }
    break;
    case ParserMode::Standard:
    {
        lexemesCollections.push_back(lexemeRulesBase);
        lexemesCollections.push_back(lexemeRulesNormal);
    }
    break;
    }

    while (currentPos != end)
    {
        bool found = false;

        // First check if it's a number
        std::vector<CalculationManager::Command>* keys;
        auto nbrCharacters = ParseNumber(currentPos, end, mode, base, decimalSeparator, thousandSeparator, &keys);
        if (nbrCharacters > 0)
        {
            result->push_back(new Lexeme(yytokentype::NUMBER, wstring(currentPos, currentPos + nbrCharacters), keys));
            currentPos += nbrCharacters;
            continue;
        }

        for (auto& lexemesCollection : lexemesCollections)
        {
            for (auto& lexemeInfo : lexemesCollection)
            {
                nbrCharacters = lexemeInfo->CheckLex(currentPos, end);
                if (nbrCharacters > 0)
                {
                    if (lexemeInfo->m_id != yytokentype::SPACE)
                        result->push_back(new Lexeme(lexemeInfo->m_id, wstring(currentPos, currentPos + nbrCharacters)));

                    currentPos += nbrCharacters;
                    found = true;
                    break;
                }
            }
            if (found)
            {
                break;
            }
        }
        if (!found)
        {
            return false;
        }
    }
    *lexemes = result;
    return true;
}

/*

int LexemeReader::GetNextLexeme(std::vector<std::wstring> ** keys)
{
    *keys = nullptr;
    if (iterator == lexemes->end())
        return 0;
    auto val = *iterator;
    *keys = val->m_keys;
    ++iterator;
    return val->m_id;
}

*/
