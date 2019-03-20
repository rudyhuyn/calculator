// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "AppResourceProvider.h"
#include "NavCategory.h"
#include "BitLength.h"
#include "NumberBase.h"

namespace CalculatorUnitTests
{
    class CopyPasteManagerTest;
}

namespace CalculatorApp
{
public
    value struct CopyPasteMaxOperandLengthAndValue
    {
        unsigned int maxLength;
        unsigned long long maxValue;
    };

    public ref class CopyPasteManager sealed
    {
    public:
        static void CopyToClipboard(Platform::String^ stringToCopy);
        static concurrency::task<Platform::String^> GetStringToPaste();
        static bool HasStringToPaste()
        {
            unsigned int get()
            {
                return MaxPasteableLengthValue;
            }
        }
        static property unsigned int MaxOperandCount
        {
            unsigned int get()
            {
                return MaxOperandCountValue;
            }
        }
        static property unsigned int MaxStandardOperandLength
        {
            unsigned int get()
            {
                return MaxStandardOperandLengthValue;
            }
        }
        static property unsigned int MaxScientificOperandLength
        {
            unsigned int get()
            {
                return MaxScientificOperandLengthValue;
            }
        }

        static property unsigned int MaxConverterInputLength
        {
            unsigned int get()
            {
                return MaxConverterInputLengthValue;
            }
        }

        static property unsigned int MaxExponentLength
        {
            unsigned int get()
            {
                return MaxExponentLengthValue;
            }
        }

        static property unsigned int MaxProgrammerBitLength
        {
            unsigned int get()
            {
                return MaxProgrammerBitLengthValue;
            }
        }

    private:
        static int ClipboardTextFormat();

        static std::pair<size_t, uint64_t> GetMaxOperandLengthAndValue(CalculatorApp::Common::ViewMode mode, CalculatorApp::Common::CategoryGroupType modeType, int programmerNumberBase = -1, int bitLengthType = -1);
        static size_t OperandLength(std::wstring operand, CalculatorApp::Common::ViewMode mode, CalculatorApp::Common::CategoryGroupType modeType, int programmerNumberBase = -1);
        static size_t StandardScientificOperandLength(std::wstring operand);
        static size_t ProgrammerOperandLength(const std::wstring& operand, int numberBase);

        static constexpr size_t MaxStandardOperandLength = 16;
        static constexpr size_t MaxScientificOperandLength = 32;
        static constexpr size_t MaxConverterInputLength = 16;
        static constexpr size_t MaxOperandCount = 100;
        static constexpr size_t MaxPasteableLength = 512;
        static constexpr size_t MaxExponentLength = 4;
        static constexpr size_t MaxProgrammerBitLength = 64;

        static Platform::String^ supportedFormats[];

    private:
        static constexpr size_t MaxStandardOperandLengthValue = 16;
        static constexpr size_t MaxScientificOperandLengthValue = 32;
        static constexpr size_t MaxConverterInputLengthValue = 16;
        static constexpr size_t MaxOperandCountValue = 100;
        static constexpr size_t MaxExponentLengthValue = 4;
        static constexpr size_t MaxProgrammerBitLengthValue = 64;
        static constexpr size_t MaxPasteableLengthValue = 512;
    };
}
