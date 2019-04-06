// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "Views/TitleBar.g.h"

namespace CalculatorApp
{
    public ref class TitleBar sealed
    {
    public:
        TitleBar();
    private:
        void OnLoaded(_In_ Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        void OnUnloaded(_In_ Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

        void Initialize();
        void SetTitleBarText(Platform::String^ text);
        void SetTitleBarVisibility(bool isVisible);
        void SetTitleBarPadding();
        void SetTitleBarControlColors();
        void ColorValuesChanged(_In_ Windows::UI::ViewManagement::UISettings^ sender, _In_ Platform::Object^ e);

        Platform::Agile<Windows::ApplicationModel::Core::CoreApplicationViewTitleBar^> m_coreTitleBar;
        Windows::Foundation::EventRegistrationToken m_layoutChangedToken;
        Windows::Foundation::EventRegistrationToken m_visibilityChangedToken;
        Windows::Foundation::EventRegistrationToken m_colorValuesChangedToken;
        Windows::UI::ViewManagement::UISettings^ m_uiSettings;
    };
}
