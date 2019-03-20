#include "pch.h"
#include "BisonParserParam.h"
using namespace std;

int yylex(yy::Parser::semantic_type * val, BisonParserParam * param)  /* Called by yyparse on error */
{
    if (param->iterator == param->endIterator)
    {
        return 0;
    }
    vector<std::wstring> * vectorKeys = (*param->iterator)->m_keys;
    if (vectorKeys != nullptr && !vectorKeys->empty())
    {
        auto chained = new KeyChainedIterator();
        KeyChained * current = nullptr;
        for (auto& key : *vectorKeys)
        {
            auto keyChained = new KeyChained(key, nullptr);
            if (chained->begin == nullptr)
            {
                chained->begin = keyChained;
            }

            if (current != nullptr)
            {
                current->next = keyChained;
            }

            current = keyChained;
            chained->last = current;
        }
        val->keys = chained;
    }
    auto res = (*param->iterator)->m_id;
    ++param->iterator;
    return res;
}

