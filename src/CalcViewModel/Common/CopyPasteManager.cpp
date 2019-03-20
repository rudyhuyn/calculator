// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "CopyPasteManager.h"
#include "Common/TraceLogger.h"
#include "Common/LocalizationSettings.h"

using namespace std;
using namespace concurrency;
using namespace CalculatorApp;
using namespace CalculatorApp::Common;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::System;
using namespace Windows::ApplicationModel::DataTransfer;
using namespace Windows::Foundation::Collections;

StringReference PasteErrorString(L"NoOp");
unsigned long long maxOperandNumber;
const wregex regexTrimSpacesStart = wregex(L"^\\s+");
const wregex regexTrimSpacesEnd = wregex(L"\\s+$");

static const wstring c_validBasicCharacterSet = L"0123456789+-.e";
static const wstring c_validStandardCharacterSet = c_validBasicCharacterSet + L"*/";
static const wstring c_validScientificCharacterSet = c_validStandardCharacterSet + L"()^%";
static const wstring c_validProgrammerCharacterSet = c_validStandardCharacterSet + L"()%abcdfABCDEF";

task<String^> CopyPasteManager::GetStringToPaste()
{
    // Retrieve the text in the clipboard
    auto dataPackageView = Clipboard::GetContent();

    return create_task((dataPackageView->GetTextAsync(::StandardDataFormats::Text)))
        .then([](String^ pastedText)
    {

        wsmatch sm;
        wstring text = std::wstring(pastedText->Data());
        if (regex_search(text, sm, regexTrimSpacesStart))
        {
            text.erase(sm.prefix().length(), sm.length());
        }

        if (regex_search(text, sm, regexTrimSpacesEnd))
        {
            text.erase(sm.prefix().length(), sm.length());
        }
        return ref new Platform::String(text.data());
    }
    , task_continuation_context::use_arbitrary());
}

void CopyPasteManager::CopyToClipboard(String ^ stringToCopy)
{
    // Copy the string to the clipboard
    auto dataPackage = ref new DataPackage();
    dataPackage->SetText(stringToCopy);
    Clipboard::SetContent(dataPackage);
}


int CopyPasteManager::ClipboardTextFormat()
{
    return Clipboard::GetContent()->Contains(StandardDataFormats::Text);
}

pair<size_t, uint64_t> CopyPasteManager::GetMaxOperandLengthAndValue(ViewMode mode, CategoryGroupType modeType, int programmerNumberBase, int bitLengthType)
{
    constexpr size_t defaultMaxOperandLength = 0;
    constexpr uint64_t defaultMaxValue = 0;
    CopyPasteMaxOperandLengthAndValue res;
    if (mode == ViewMode::Standard)
    {
        res.maxLength = MaxStandardOperandLength;
        res.maxValue = defaultMaxValue;
        return res;
    }
    else if (mode == ViewMode::Scientific)
    {
        res.maxLength = MaxScientificOperandLength;
        res.maxValue = defaultMaxValue;
        return res;
    }
    else if (mode == ViewMode::Programmer)
    {
        unsigned int bitLength = 0;
        switch (bitLengthType)
        {
        case BitLength::BitLengthQWord:
            bitLength = 64;
            break;
        case BitLength::BitLengthDWord:
            bitLength = 32;
            break;
        case BitLength::BitLengthWord:
            bitLength = 16;
            break;
        case BitLength::BitLengthByte:
            bitLength = 8;
            break;
        }

        double bitsPerDigit = 0;
        switch (programmerNumberBase)
        {
        case NumberBase::BinBase:
            bitsPerDigit = log2(2);
            break;
        case NumberBase::OctBase:
            bitsPerDigit = log2(8);
            break;
        case NumberBase::DecBase:
            bitsPerDigit = log2(10);
            break;
        case NumberBase::HexBase:
            bitsPerDigit = log2(16);
            break;
        }

        unsigned int signBit = (programmerNumberBase == NumberBase::DecBase) ? 1 : 0;

        const auto maxLength = static_cast<unsigned int>(ceil((bitLength - signBit) / bitsPerDigit));
        const uint64_t maxValue = UINT64_MAX >> (MaxProgrammerBitLength - (bitLength - signBit));

        res.maxLength = maxLength;
        res.maxValue = maxValue;
        return res;
    }
    else if (modeType == CategoryGroupType::Converter)
    {
        res.maxLength = MaxConverterInputLength;
        res.maxValue = defaultMaxValue;
        return res;
    }

    res.maxLength = defaultMaxOperandLength;
    res.maxValue = defaultMaxValue;
    return res;
}


ULONG32 CopyPasteManager::OperandLength(Platform::String ^ operand, ViewMode mode, CategoryGroupType modeType, NumberBase programmerNumberBase)
{
    if (modeType == CategoryGroupType::Converter)
    {
        return operand->Length();
    }

    switch (mode)
    {
    case ViewMode::Standard:
    case ViewMode::Scientific:
        return StandardScientificOperandLength(operand);

    case ViewMode::Programmer:
        return ProgrammerOperandLength(operand, programmerNumberBase);

    default:
        return 0;
    }
}

ULONG32 CopyPasteManager::StandardScientificOperandLength(Platform::String ^ operand)
{
    auto operandWstring = wstring(operand->Data());
    const bool hasDecimal = operandWstring.find('.') != wstring::npos;

    if (hasDecimal)
    {
        if (operandWstring.length() >= 2)
        {
            if ((operandWstring[0] == L'0') && (operandWstring[1] == L'.'))
            {
                return static_cast<ULONG32>(operandWstring.length() - 2);
            }
            else
            {
                return static_cast<ULONG32>(operandWstring.length() - 1);
            }
        }
    }

    return static_cast<ULONG32>(operandWstring.length());
}

ULONG32 CopyPasteManager::ProgrammerOperandLength(Platform::String ^ operand, NumberBase numberBase)
{
    vector<wstring> prefixes{};
    vector<wstring> suffixes{};
    switch (numberBase)
    {
    case NumberBase::BinBase:
        prefixes = { L"0B", L"0Y" };
        suffixes = { L"B" };
        break;
    case NumberBase::DecBase:
        prefixes = { L"-", L"0N" };
        break;
    case NumberBase::OctBase:
        prefixes = { L"0T", L"0O" };
        break;
    case NumberBase::HexBase:
        prefixes = { L"0X" };
        suffixes = { L"H" };
        break;
    default:
        // No defined prefixes/suffixes
        return 0;
    }

    // UInt suffixes are common across all modes
    const array<wstring, 5> uintSuffixes = { L"ULL", L"UL", L"LL", L"U", L"L" };
    suffixes.insert(suffixes.end(), uintSuffixes.begin(), uintSuffixes.end());

    wstring operandUpper = wstring(operand->Data());
    transform(operandUpper.begin(), operandUpper.end(), operandUpper.begin(), towupper);

    size_t len = operand->Length();

    // Detect if there is a suffix and subtract its length
    // Check suffixes first to allow e.g. "0b" to result in length 1 (value 0), rather than length 0 (no value).
    for (const auto& suffix : suffixes)
    {
        if (len < suffix.length())
        {
            continue;
        }

        if (operandUpper.compare(operandUpper.length() - suffix.length(), suffix.length(), suffix) == 0)
        {
            len -= suffix.length();
            break;
        }
    }

    // Detect if there is a prefix and subtract its length
    for (const auto& prefix : prefixes)
    {
        if (len < prefix.length())
        {
            continue;
        }

        if (operandUpper.compare(0, prefix.length(), prefix) == 0)
        {
            len -= prefix.length();
            break;
        }
    }

    return static_cast<ULONG32>(len);
}

// return wstring after removing characters like space, comma, double quotes, and monetary prefix currency symbols supported by the Windows keyboard:
// yen or yuan(¥) - 165
// unspecified currency sign(¤) - 164
// Ghanaian cedi(₵) - 8373
// dollar or peso($) - 36
// colón(₡) - 8353
// won(₩) - 8361
// shekel(₪) - 8362
// naira(₦) - 8358
// Indian rupee(₹) - 8377
// pound(£) - 163
// euro(€) - 8364
