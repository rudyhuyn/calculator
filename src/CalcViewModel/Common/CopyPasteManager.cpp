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
using namespace Windows::Foundation;
using namespace Windows::System;
using namespace Windows::ApplicationModel::DataTransfer;

unsigned long long maxOperandNumber;
const wregex regexTrimSpacesStart = wregex(L"^\\s+");
const wregex regexTrimSpacesEnd = wregex(L"\\s+$");

String ^ CopyPasteManager::supportedFormats[] = { StandardDataFormats::Text };

task<String ^> CopyPasteManager::GetStringToPaste()
{
    // Retrieve the text in the clipboard
    auto dataPackageView = Clipboard::GetContent();

    return create_task((dataPackageView->GetTextAsync(::StandardDataFormats::Text)))
        .then(
            [](String ^ pastedText) {
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
            },
            task_continuation_context::use_arbitrary());
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
    int result = -1;

    auto dataPackageView = Clipboard::GetContent();

    for (int i = 0; i < RTL_NUMBER_OF(supportedFormats); i++)
    {
        if (dataPackageView->Contains(supportedFormats[i]))
        {
            result = i;
            break;
        }
    }
    return result;
}

pair<size_t, uint64_t> CopyPasteManager::GetMaxOperandLengthAndValue(ViewMode mode, CategoryGroupType modeType, NumberBase programmerNumberBase, BitLength bitLengthType)
{
    size_t maxLength = 0;
    uint64_t maxValue = 0;

    if (mode == ViewMode::Standard)
    {
        maxLength = MaxStandardOperandLength;
    }
    else if (mode == ViewMode::Scientific)
    {
        maxLength = MaxScientificOperandLength;
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

        maxLength = (size_t)ceil((bitLength - signBit) / bitsPerDigit);
        maxValue = UINT64_MAX >> (MaxProgrammerBitLength - (bitLength - signBit));
    }
    else if (modeType == CategoryGroupType::Converter)
    {
        maxLength = MaxConverterInputLength;
    }

    return make_pair(maxLength, maxValue);
}

size_t CopyPasteManager::OperandLength(wstring operand, ViewMode mode, CategoryGroupType modeType, NumberBase programmerNumberBase)
{
    size_t len = 0;
    if (mode == ViewMode::Standard || mode == ViewMode::Scientific)
    {
        len = StandardScientificOperandLength(operand);
    }
    else if (mode == ViewMode::Programmer)
    {
        len = ProgrammerOperandLength(operand, programmerNumberBase);
    }
    else if (modeType == CategoryGroupType::Converter)
    {
        len = operand.length();
    }

    return len;
}

size_t CopyPasteManager::StandardScientificOperandLength(wstring operand)
{
    bool hasDecimal = false;
    for (size_t i = 0; i < operand.length(); i++)
    {
        if (operand[i] == L'.')
        {
            hasDecimal = true;
        }
    }

    if (hasDecimal)
    {
        if (operand.length() >= 2)
        {
            if ((operand[0] == L'0') && (operand[1] == L'.'))
            {
                return operand.length() - 2;
            }
            else
            {
                return operand.length() - 1;
            }
        }
    }

    return operand.length();
}

size_t CopyPasteManager::ProgrammerOperandLength(const wstring& operand, NumberBase numberBase)
{
    size_t len = operand.length();

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
        break;
    }

    // UInt suffixes are common across all modes
    const array<wstring, 5> uintSuffixes = { L"ULL", L"UL", L"LL", L"U", L"L" };
    suffixes.insert(suffixes.end(), uintSuffixes.begin(), uintSuffixes.end());

    wstring operandUpper = operand;
    transform(operandUpper.begin(), operandUpper.end(), operandUpper.begin(), towupper);

    // Detect if there is a suffix and subtract its length
    // Check suffixes first to allow e.g. "0b" to result in length 1 (value 0), rather than length 0 (no value).
    for (const wstring& suffix : suffixes)
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
    for (const wstring& prefix : prefixes)
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

    return len;
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
