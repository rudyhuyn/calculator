#pragma once
#include "pch.h"
#include "CalcManager/Command.h"

class KeyChained
{
public:
    KeyChained(CalculationManager::Command key, KeyChained * next) :key(key), next(next) {}
    CalculationManager::Command key; 
    KeyChained * next;
};

struct KeyChainedIterator
{
    KeyChained * begin;
    KeyChained * last;
};
