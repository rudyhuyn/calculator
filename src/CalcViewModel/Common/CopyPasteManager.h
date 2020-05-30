// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "AppResourceProvider.h"
#include "NavCategory.h"
#include "NumberBase.h"
#include "BitLength.h"

namespace CalculatorUnitTests
{
    class CopyPasteManagerTest;
}

namespace CalculatorApp
{
    class CopyPasteManager
    {
    public:
        static void CopyToClipboard(Platform::String ^ stringToCopy);
        static concurrency::task<Platform::String ^> GetStringToPaste();
        static bool HasStringToPaste()
        {
            return ClipboardTextFormat() >= 0;
        }

        static constexpr auto PasteErrorString = L"NoOp";

    private:
        static int ClipboardTextFormat();

        static std::pair<size_t, uint64_t> GetMaxOperandLengthAndValue(
            CalculatorApp::Common::ViewMode mode,
            CalculatorApp::Common::CategoryGroupType modeType,
            CalculatorApp::Common::NumberBase programmerNumberBase = CalculatorApp::Common::NumberBase::Unknown,
            CalculatorApp::Common::BitLength bitLengthType = CalculatorApp::Common::BitLength::BitLengthUnknown);
        static size_t OperandLength(
            std::wstring operand,
            CalculatorApp::Common::ViewMode mode,
            CalculatorApp::Common::CategoryGroupType modeType,
            CalculatorApp::Common::NumberBase programmerNumberBase = CalculatorApp::Common::NumberBase::Unknown);
        static size_t StandardScientificOperandLength(std::wstring operand);
        static size_t ProgrammerOperandLength(const std::wstring& operand, CalculatorApp::Common::NumberBase numberBase);

        static constexpr size_t MaxStandardOperandLength = 16;
        static constexpr size_t MaxScientificOperandLength = 32;
        static constexpr size_t MaxConverterInputLength = 16;
        static constexpr size_t MaxOperandCount = 100;
        static constexpr size_t MaxPasteableLength = 512;
        static constexpr size_t MaxExponentLength = 4;
        static constexpr size_t MaxProgrammerBitLength = 64;

        static Platform::String ^ supportedFormats[];

        friend class CalculatorUnitTests::CopyPasteManagerTest;
    };
}
