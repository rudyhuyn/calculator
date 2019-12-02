// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "EquationStylePanelControl.g.h"
#include "CalcViewModel/Common/Utils.h"

namespace CalculatorApp
{
	[Windows::Foundation::Metadata::WebHostHidden] public ref class EquationStylePanelControl sealed
	{
	public:
        EquationStylePanelControl();
        DEPENDENCY_PROPERTY_OWNER(EquationStylePanelControl);

        DEPENDENCY_PROPERTY_WITH_CALLBACK(Windows::UI::Xaml::Media::SolidColorBrush ^, SelectedColor);

        property Windows::Foundation::Collections::IVector<Windows::UI::Xaml::Media::SolidColorBrush^>^ AvailableColors
        {
            Windows::Foundation::Collections::IVector<Windows::UI::Xaml::Media::SolidColorBrush^>^ get() {
                return m_AvailableColors;
            }
        }

	private:
        void InitializeAvailableColors();
        void SelectionChanged(Platform::Object ^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs ^ e);
        void OnSelectedColorPropertyChanged(Windows::UI::Xaml::Media::SolidColorBrush ^ oldValue, Windows::UI::Xaml::Media::SolidColorBrush ^ newValue);
        void ColorChooserLoaded(Platform::Object ^ sender, Windows::UI::Xaml::RoutedEventArgs ^ e);
        void SelectColor(Windows::UI::Xaml::Media::SolidColorBrush ^ selectedColor);

        Windows::Foundation::Collections::IVector<Windows::UI::Xaml::Media::SolidColorBrush ^>^ m_AvailableColors;
    };
}
