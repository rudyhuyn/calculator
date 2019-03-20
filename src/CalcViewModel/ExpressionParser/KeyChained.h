#pragma once
#include<string>

class KeyChained
{
public:
    KeyChained(std::wstring key, KeyChained * next) :key(key), next(next) {}
    std::wstring key;
    KeyChained * next;
};

struct KeyChainedIterator
{
    KeyChained * begin;
    KeyChained * last;
};