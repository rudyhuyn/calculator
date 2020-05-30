#pragma once
#include "pch.h"

namespace ExpressionParser
{
public
    enum class ParserMode : int
    {
        Numbers = 0,
        Standard,
        Scientific,
        Programmer,
    };
}
