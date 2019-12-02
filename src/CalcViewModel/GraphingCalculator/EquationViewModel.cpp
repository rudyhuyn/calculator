#include "pch.h"
#include "EquationViewModel.h"

using namespace Windows::UI;
using namespace Windows::UI::Xaml;

namespace CalculatorApp::ViewModel
{
    EquationViewModel::EquationViewModel()
        : m_LineColor{ nullptr }, m_KeyGraphFeaturesVisibility{ ::Visibility::Collapsed }
        , m_Expression{ "" }
    {
    }
}
