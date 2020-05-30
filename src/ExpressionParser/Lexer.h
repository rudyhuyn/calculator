#pragma once
#include "pch.h"
#include "CalcManager/Command.h"
#include "ParserMode.h"

#define LexemeId int

class LexInfo
{
public:
    LexInfo(LexemeId id) :m_id(id) {}
    virtual int CheckLex(const std::wstring::const_iterator &begin, const std::wstring::const_iterator &end) = 0;
public:
    LexemeId m_id;
};


class LexInfoChar : public LexInfo
{
public:
    LexInfoChar(LexemeId id, wchar_t character) :LexInfo(id), m_character(character) {}
    int CheckLex(const std::wstring::const_iterator &begin, const std::wstring::const_iterator &end);

public:
    wchar_t m_character;
};

class LexInfoString : public LexInfo
{
public:
    LexInfoString(LexemeId id, std::wstring text) :LexInfo(static_cast<int>(id)), m_refText(text), m_refTextCachedSize(static_cast<int>(text.length())) {}
    int CheckLex(const std::wstring::const_iterator &begin, const std::wstring::const_iterator &end);
private:
    static bool CaseInsensitiveCompare(wchar_t a, wchar_t b);
public:
    std::wstring m_refText;
    int m_refTextCachedSize;
};

class LexInfoRegex : public LexInfo
{
public:
    LexInfoRegex(LexemeId id, std::wstring regex) :LexInfo(id), m_regex(regex) {}
    int CheckLex(const std::wstring::const_iterator &begin, const std::wstring::const_iterator &end);
public:
    std::wregex m_regex;
};


class Lexeme
{
public:
    Lexeme(LexemeId id, std::wstring str, std::vector<CalculationManager::Command> * keys) : Lexeme(id, str)
    {
        m_keys = keys;
    }
    Lexeme(LexemeId id, std::wstring str) :m_id(id), m_str(str) {}
public:
    std::wstring m_str;
    LexemeId m_id;
    std::vector<CalculationManager::Command> * m_keys;
};

class LexemeReader
{
public:
    bool GetLexemes(
        std::wstring item,
        ExpressionParser::ParserMode mode,
        int base,
        const std::wstring& decimalSeparator,
        const std::wstring& thousandSeparator,
        std::vector<Lexeme*>** lexemes);

protected:
    int ParseNumber(
        const std::wstring::const_iterator& begin,
        const std::wstring::const_iterator& end,
        ExpressionParser::ParserMode mode,
        int base,
        const std::wstring& decimalSeparator,
        const std::wstring& thousandSeparator,
        std::vector<CalculationManager::Command>** keys);

private:
    std::vector<Lexeme *>::const_iterator iterator;
};
