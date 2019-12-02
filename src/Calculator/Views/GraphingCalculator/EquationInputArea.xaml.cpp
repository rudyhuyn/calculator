#include "pch.h"
#include "EquationInputArea.xaml.h"
#include "CalcViewModel/Common/KeyboardShortcutManager.h"

using namespace CalculatorApp;
using namespace CalculatorApp::Common;
using namespace CalculatorApp::ViewModel;
using namespace Platform;
using namespace std;
using namespace Windows::System;
using namespace Windows::UI;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Input;

namespace
{
    const Color accentColor = (ref new UISettings())->GetColorValue(UIColorType::Accent);
    const Color lineColors[] = {
        accentColor,
        Colors::DarkOrange,
        Colors::MediumPurple,
        Colors::ForestGreen,
        Colors::BlueViolet,
        Colors::DarkRed,
        Colors::LightGoldenrodYellow,
        Colors::DarkOliveGreen
    };
    const size_t lineColorsSize = std::size(lineColors);

    StringReference EquationsPropertyName(L"Equations");
}

EquationInputArea::EquationInputArea()
    : m_lastLineColorIndex{ -1 }
{
	InitializeComponent();
}

void EquationInputArea::OnPropertyChanged(String^ propertyName)
{
    if (propertyName == EquationsPropertyName)
    {
        OnEquationsPropertyChanged();
    }
}

void EquationInputArea::OnEquationsPropertyChanged()
{
    if (Equations != nullptr && Equations->Size == 0)
    {
        AddNewEquation();

        // For now, the first equation needs to be y = 0.
        // We can remove this when we can create empty graphs.
        if (EquationViewModel^ eqvm = Equations->GetAt(0))
        {
            eqvm->Expression = L"0";
        }
    }
}

void EquationInputArea::AddEquationButton_Click(Object^ sender, RoutedEventArgs^ e)
{
    AddNewEquation();
}

void EquationInputArea::AddNewEquation()
{
    auto eq = ref new EquationViewModel();
    eq->LineColor = GetNextLineColor();

    Equations->Append(eq);
    EquationInputList->ScrollIntoView(eq);
}

void EquationInputArea::InputTextBox_GotFocus(Object^ sender, RoutedEventArgs^ e)
{
    KeyboardShortcutManager::HonorShortcuts(false);
}

void EquationInputArea::InputTextBox_LostFocus(Object^ sender, RoutedEventArgs^ e)
{
    KeyboardShortcutManager::HonorShortcuts(true);
    
    auto tb = static_cast<TextBox^>(sender);
    auto eq = static_cast<EquationViewModel^>(tb->DataContext);
    tb->Text = eq->Expression;
}

void EquationInputArea::InputTextBox_KeyUp(Object^ sender, KeyRoutedEventArgs^ e)
{
    if (e->Key == VirtualKey::Enter)
    {
        auto tb = static_cast<TextBox^>(sender);
        auto eq = static_cast<EquationViewModel^>(tb->DataContext);
        eq->Expression = tb->Text;

        e->Handled = true;
    }
}

Color EquationInputArea::GetNextLineColor()
{
    m_lastLineColorIndex = (m_lastLineColorIndex + 1) % lineColorsSize;
    return lineColors[m_lastLineColorIndex];
}
