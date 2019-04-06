// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "TitleBar.xaml.h"
#include "CalcViewModel/Common/AppResourceProvider.h"
#include "CalcViewModel/Common/Utils.h"

using namespace std;
using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Foundation;
using namespace Windows::UI;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::Foundation::Collections;

namespace CalculatorApp
{
    TitleBar::TitleBar() :
        m_coreTitleBar(CoreApplication::GetCurrentView()->TitleBar)
    {
        InitializeComponent();
        m_uiSettings = ref new UISettings();

        Loaded += ref new RoutedEventHandler(this, &TitleBar::OnLoaded);
        Unloaded += ref new RoutedEventHandler(this, &TitleBar::OnUnloaded);

        m_coreTitleBar->ExtendViewIntoTitleBar = true;
        AppName->Text = AppResourceProvider::GetInstance().GetResourceString(L"AppName");
        LayoutRoot->Height = m_coreTitleBar->Height;
        SetTitleBarVisibility(m_coreTitleBar->IsVisible);
        SetTitleBarPadding();
    }

    void TitleBar::OnLoaded(_In_ Object^ sender, _In_ RoutedEventArgs^ e)
    {
        m_visibilityChangedToken = m_coreTitleBar->IsVisibleChanged += ref new TypedEventHandler<CoreApplicationViewTitleBar^, Object^>(
            [&](CoreApplicationViewTitleBar^ cTitleBar, Object^)
        {
            // Update title bar visibility
            this->SetTitleBarVisibility(cTitleBar->IsVisible);
        });
        m_layoutChangedToken = m_coreTitleBar->LayoutMetricsChanged += ref new TypedEventHandler<CoreApplicationViewTitleBar^, Object^>(
            [this](CoreApplicationViewTitleBar^ cTitleBar, Object^)
        {
            this->LayoutRoot->Height = cTitleBar->Height;
            this->SetTitleBarPadding();
        });

        m_colorValuesChangedToken = m_uiSettings->ColorValuesChanged += ref new TypedEventHandler<UISettings^, Object^>(this, &TitleBar::ColorValuesChanged);
        SetTitleBarControlColors();
    }

    void TitleBar::OnUnloaded(_In_ Object^ sender, _In_ RoutedEventArgs^ e)
    {
        m_coreTitleBar->LayoutMetricsChanged -= m_layoutChangedToken;
        m_layoutChangedToken.Value = 0;
        m_coreTitleBar->IsVisibleChanged -= m_visibilityChangedToken;
        m_visibilityChangedToken.Value = 0;
        m_uiSettings->ColorValuesChanged -= m_colorValuesChangedToken;
        m_colorValuesChangedToken.Value = 0;
    }

    void TitleBar::SetTitleBarVisibility(bool isVisible)
    {
        this->LayoutRoot->Visibility = isVisible ? ::Visibility::Visible : ::Visibility::Collapsed;
    }

    void TitleBar::SetTitleBarPadding()
    {
        double leftAddition = 0;
        double rightAddition = 0;

        if (this->FlowDirection == ::FlowDirection::LeftToRight)
        {
            leftAddition = m_coreTitleBar->SystemOverlayLeftInset;
            rightAddition = m_coreTitleBar->SystemOverlayRightInset;
        }
        else
        {
            leftAddition = m_coreTitleBar->SystemOverlayRightInset;
            rightAddition = m_coreTitleBar->SystemOverlayLeftInset;
        }

        auto padding = Thickness(leftAddition, 0, rightAddition, 0);

        this->LayoutRoot->Padding = padding;
    }

    void TitleBar::ColorValuesChanged(_In_ UISettings^ sender, _In_ Object^ e)
    {
        WeakReference weakThis(this);
        Utils::RunOnUIThreadNonblocking([weakThis]()
        {
            auto refThis = weakThis.Resolve<TitleBar>();
            if (refThis != nullptr)
            {
                refThis->SetTitleBarControlColors();
            }
        }, this->Dispatcher);
    }

    void TitleBar::SetTitleBarControlColors()
    {
        auto applicationView = ApplicationView::GetForCurrentView();
        if (applicationView == nullptr) { return; }

        auto applicationTitleBar = applicationView->TitleBar;
        if (applicationTitleBar == nullptr) { return; }

        auto bgColor = Colors::Transparent;
        auto fgbrush = safe_cast<SolidColorBrush^>(Application::Current->Resources->Lookup("SystemControlPageTextBaseHighBrush"));
        auto inactivefgbrush = safe_cast<SolidColorBrush^>(Application::Current->Resources->Lookup("SystemControlForegroundChromeDisabledLowBrush"));
        auto hoverbgbrush = safe_cast<SolidColorBrush^>(Application::Current->Resources->Lookup("SystemControlBackgroundListLowBrush"));
        auto hoverfgbrush = safe_cast<SolidColorBrush^>(Application::Current->Resources->Lookup("SystemControlForegroundBaseHighBrush"));
        auto pressedbgbrush = safe_cast<SolidColorBrush^>(Application::Current->Resources->Lookup("SystemControlBackgroundListMediumBrush"));
        auto pressedfgbrush = safe_cast<SolidColorBrush^>(Application::Current->Resources->Lookup("SystemControlForegroundBaseHighBrush"));

        applicationTitleBar->ButtonBackgroundColor = bgColor;
        applicationTitleBar->ButtonForegroundColor = fgbrush->Color;
        applicationTitleBar->ButtonInactiveBackgroundColor = bgColor;
        applicationTitleBar->ButtonInactiveForegroundColor = inactivefgbrush->Color;
        applicationTitleBar->ButtonHoverBackgroundColor = hoverbgbrush->Color;
        applicationTitleBar->ButtonHoverForegroundColor = hoverfgbrush->Color;
        applicationTitleBar->ButtonPressedBackgroundColor = pressedbgbrush->Color;
        applicationTitleBar->ButtonPressedForegroundColor = pressedfgbrush->Color;
    }

}

