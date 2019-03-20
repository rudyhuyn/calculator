#include "pch.h"
#include "Lexer.h"
#include "BisonGeneratedFiles/BisonParser.hpp" 

using namespace std;

#define yytokentype yy::Parser::token

wchar_t decimalSeparatorChar = ',';
wchar_t digitGroupingChar = ' ';
std::wregex regexNumber = std::wregex((
    L"("
    "(\\d{0,3}(?:\\" + digitGroupingChar + L"\\d{3})+(\\" + decimalSeparatorChar + L"\\d+)?)|"
    "(\\d*\\" + decimalSeparatorChar + L"\\d+)|"
    "(\\d+\\" + decimalSeparatorChar + L"?)"
    ")"
    "(e[+-]?\\d+)?")->Data());
LexInfoRegex * numberDecimal = new LexInfoRegex(yytokentype::NUMBER, L"(?:\\d+|(?:\\d*(?:\\.\\d+)))");
LexInfoRegex * numberDec = new LexInfoRegex(yytokentype::NUMBER, L"\\d");
LexInfoRegex * numberOcto = new LexInfoRegex(yytokentype::NUMBER, L"[0-7]");
LexInfoRegex * numberHexa = new LexInfoRegex(yytokentype::NUMBER, L"[0-9A-F]");
LexInfoRegex * numberBin = new LexInfoRegex(yytokentype::NUMBER, L"[01]+");



vector<LexInfo *> const lexemeRulesBase(
    {
        new LexInfoChar(yytokentype::PLUS, L'+'),
        new LexInfoChar(yytokentype::MINUS, L'-'),
        new LexInfoChar(yytokentype::DIVIDE, L'/'),
        new LexInfoChar(yytokentype::MULTIPLY, L'*'),
        new LexInfoRegex(yytokentype::SPACE, L"\\s+"),
        new LexInfoChar(yytokentype::EQU, L'='),
    });

vector<LexInfo *> const lexemeRulesNormal(
    {
        new LexInfoChar(yytokentype::POWER2, L'²'),
        new LexInfoChar(yytokentype::POWER2, 253),
        new LexInfoChar(yytokentype::POWER3, L'³'),
        new LexInfoChar(yytokentype::POWER2, 254),
    });

vector<LexInfo *> const lexemeRulesProg(
    {
       new LexInfoChar(yytokentype::LEFTPARENTHESIS, L'('),
       new LexInfoChar(yytokentype::RIGHTPARENTHESIS, L')'),
       new LexInfoChar(yytokentype::PROG_AND, L'&'),
       new LexInfoChar(yytokentype::PROG_NOT, L'~'),
    });

vector<LexInfo *> const lexemeRulesScientific(
    {
        new LexInfoChar(yytokentype::LEFTPARENTHESIS, L'('),
        new LexInfoChar(yytokentype::RIGHTPARENTHESIS, L')'),
        new LexInfoChar(yytokentype::CARET, L'^'),
        new LexInfoString(yytokentype::SIN, L"sin"),
        new LexInfoString(yytokentype::COS, L"cos"),
        new LexInfoString(yytokentype::TAN, L"tan"),
    });

int LexInfoChar::CheckLex(const wstring::const_iterator &begin, const wstring::const_iterator & /*end*/)
{
    if (*begin == m_character)
    {
        return 1;
    }
    return -1;
}


int LexInfoString::CheckLex(const wstring::const_iterator &begin, const wstring::const_iterator &end)
{
    if (m_refTextCachedSize <= end - begin && equal(m_refText.begin(), m_refText.end(), begin))
    {
        return m_refTextCachedSize;
    }
    return -1;
}

int LexInfoRegex::CheckLex(const wstring::const_iterator &begin, const wstring::const_iterator &end)
{
    wsmatch match;
    if (regex_search(begin, end, match, m_regex, regex_constants::match_continuous))
        return match.length();
    return -1;
}

int LexemeReader::ParseNumber(const wstring::const_iterator &begin, const wstring::const_iterator &end, std::vector<std::wstring>** keys)
{
    *keys = nullptr;
    wsmatch match;
    if (regex_search(begin, end, match, regexNumber, regex_constants::match_continuous))
    {
        *keys = new std::vector<std::wstring>();
        std::wstring numberFound = match.str();
        for (auto&c : numberFound)
        {
            if (c == digitGroupingChar)
                continue;
            if (c == decimalSeparatorChar)
            {
                (*keys)->push_back(std::wstring(L"<Separator>"));
                continue;
            }
            switch (c)
            {
            case '0':
                (*keys)->push_back(std::wstring(L"0"));
                break;
            case '1':
                (*keys)->push_back(std::wstring(L"1"));
                break;
            case '2':
                (*keys)->push_back(std::wstring(L"2"));
                break;
            case '3':
                (*keys)->push_back(std::wstring(L"3"));
                break;
            case '4':
                (*keys)->push_back(std::wstring(L"4"));
                break;
            case '5':
                (*keys)->push_back(std::wstring(L"5"));
                break;
            case '6':
                (*keys)->push_back(std::wstring(L"6"));
                break;
            case '7':
                (*keys)->push_back(std::wstring(L"7"));
                break;
            case '8':
                (*keys)->push_back(std::wstring(L"8"));
                break;
            case '9':
                (*keys)->push_back(std::wstring(L"9"));
                break;
            case 'e':
                (*keys)->push_back(std::wstring(L"EXP"));
                break;
            case '-':
                (*keys)->push_back(std::wstring(L"NEG"));
                break;
            }

        }

        return numberFound.length();
    }
    return -1;
}

bool LexemeReader::GetLexemes(wstring item, vector<Lexeme *>** lexemes)
{
    *lexemes = nullptr;
    vector<Lexeme *>* result = new vector<Lexeme *>();
    wstring::const_iterator currentPos = item.begin();
    wstring::const_iterator end = item.end();

    vector<vector<LexInfo *>> lexemesCollections{
        lexemeRulesBase
    };
    if (true)
    {
        lexemesCollections.push_back(lexemeRulesNormal);
        lexemesCollections.push_back(lexemeRulesScientific);
    }

    while (currentPos != end)
    {
        bool found = false;

        //First check if it's a number
        std::vector<std::wstring> *keys;
        auto nbrCharacters = ParseNumber(currentPos, end, &keys);
        if (nbrCharacters > 0)
        {
            result->push_back(new Lexeme(yytokentype::NUMBER, wstring(currentPos, currentPos + nbrCharacters), keys));
            currentPos += nbrCharacters;
            continue;
        }

        for (auto & lexemesCollection : lexemesCollections)
        {
            for (auto & lexemeInfo : lexemesCollection)
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
