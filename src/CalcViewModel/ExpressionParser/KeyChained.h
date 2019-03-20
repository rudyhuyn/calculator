#pragma once
#include "Common/CalculatorButtonUser.h"

class KeyChained
{
public:
    KeyChained(CalculatorApp::NumbersAndOperatorsEnum key, KeyChained * next) :key(key), next(next) {}
    CalculatorApp::NumbersAndOperatorsEnum key; 
    KeyChained * next;
};


struct KeyChainedIterator
{
    KeyChained * begin;
    KeyChained * last;
};
