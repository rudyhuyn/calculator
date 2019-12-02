// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

namespace GraphControl
{
    namespace EquationProperties
    {
        extern Platform::String ^ Expression;
        extern Platform::String ^ LineColor;
    }

    ref class Equation;
    delegate void PropertyChangedEventHandler(Equation ^ sender, Platform::String ^ propertyName);

    [Windows::UI::Xaml::Data::Bindable] public ref class Equation sealed : public Windows::UI::Xaml::DependencyObject
    {
    public:

        Equation()
        {
        }

        static void RegisterDependencyProperties();

#pragma region Platform::String ^ Expression DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ ExpressionProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_expressionProperty;
            }
        }
        property Platform::String^ Expression
        {
            Platform::String^ get()
            {
                return static_cast<Platform::String^>(GetValue(s_expressionProperty));
            }
            void set(Platform::String^ value)
            {
                SetValue(s_expressionProperty, value);
            }
        }
#pragma endregion

#pragma region Windows::UI::Xaml::Media::SolidColorBrush ^ LineColor DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ LineColorProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_lineColorProperty;
            }
        }
        property Windows::UI::Xaml::Media::SolidColorBrush^ LineColor
        {
            Windows::UI::Xaml::Media::SolidColorBrush^ get()
            {
                return static_cast<Windows::UI::Xaml::Media::SolidColorBrush^>(GetValue(s_lineColorProperty));
            }
            void set(Windows::UI::Xaml::Media::SolidColorBrush^ value)
            {
                if (value == nullptr || LineColor == nullptr || (value->Color.A != LineColor->Color.A) || (value->Color.R != LineColor->Color.R)
                    || (value->Color.G != LineColor->Color.G) || (value->Color.B != LineColor->Color.B))
                SetValue(s_lineColorProperty, value);
            }
        }
#pragma endregion

#pragma region Key Graph Features


#pragma region Platform::String ^ XIntercept DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ XInterceptProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_xInterceptProperty;
            }
        }
        property Platform::String^ XIntercept
        {
            Platform::String^ get()
            {
                return static_cast<Platform::String^>(GetValue(s_xInterceptProperty));
            }
            void set(Platform::String^ value)
            {
                SetValue(s_xInterceptProperty, value);
            }
        }
#pragma endregion

#pragma region Platform::String ^ YIntercept DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ YInterceptProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_yInterceptProperty;
            }
        }
        property Platform::String^ YIntercept
        {
            Platform::String^ get()
            {
                return static_cast<Platform::String^>(GetValue(s_yInterceptProperty));
            }
            void set(Platform::String^ value)
            {
                SetValue(s_yInterceptProperty, value);
            }
        }
#pragma endregion

#pragma region int Parity DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ ParityProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_parityProperty;
            }
        }
        property int Parity
        {
            int get()
            {
                return static_cast<int>(GetValue(s_parityProperty));
            }
            void set(int value)
            {
                SetValue(s_parityProperty, value);
            }
        }
#pragma endregion

#pragma region int Periodicity DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ PeriodicityDirectionProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_periodicityDirectionProperty;
            }
        }
        property int PeriodicityDirection
        {
           int get()
            {
                return static_cast<int>(GetValue(s_periodicityDirectionProperty));
            }
            void set(int value)
            {
                SetValue(s_periodicityDirectionProperty, value);
            }
        }
#pragma endregion

        #pragma region Platform::String ^ PeriodicityExpression DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ PeriodicityExpressionProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_periodicityExpressionProperty;
            }
        }
        property Platform::String ^ PeriodicityExpression
        {
            Platform::String ^ get()
            {
                return static_cast<Platform::String ^>(GetValue(s_periodicityExpressionProperty));
            }
            void set(Platform::String ^ value)
            {
                SetValue(s_periodicityExpressionProperty, value);
            }
        }
#pragma endregion

#pragma region Windows::Foundation::Collections::IVector < Platform::String ^ > ^ Minima DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ MinimaProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_minimaProperty;
            }
        }
        property Windows::Foundation::Collections::IVector<Platform::String^> ^ Minima
        {
            Windows::Foundation::Collections::IVector<Platform::String^> ^ get()
            {
                return static_cast<Windows::Foundation::Collections::IVector<Platform::String^> ^>(GetValue(s_minimaProperty));
            }
            void set(Windows::Foundation::Collections::IVector<Platform::String^> ^ value)
            {
                SetValue(s_minimaProperty, value);
            }
        }
#pragma endregion

#pragma region Windows::Foundation::Collections::IVector < Platform::String ^ > ^ Maxima DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ MaximaProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_maximaProperty;
            }
        }
        property Windows::Foundation::Collections::IVector<Platform::String^> ^ Maxima
        {
            Windows::Foundation::Collections::IVector<Platform::String^> ^ get()
            {
                return static_cast<Windows::Foundation::Collections::IVector<Platform::String^> ^>(GetValue(s_maximaProperty));
            }
            void set(Windows::Foundation::Collections::IVector<Platform::String^> ^ value)
            {
                SetValue(s_maximaProperty, value);
            }
        }
#pragma endregion

#pragma region Platform::String ^ Domain DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ DomainProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_domainProperty;
            }
        }
        property Platform::String^ Domain
        {
            Platform::String^ get()
            {
                return static_cast<Platform::String^>(GetValue(s_domainProperty));
            }
            void set(Platform::String^ value)
            {
                SetValue(s_domainProperty, value);
            }
        }
#pragma endregion

#pragma region Platform::String ^ Range DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ RangeProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_rangeProperty;
            }
        }
        property Platform::String^ Range
        {
            Platform::String^ get()
            {
                return static_cast<Platform::String^>(GetValue(s_rangeProperty));
            }
            void set(Platform::String^ value)
            {
                SetValue(s_rangeProperty, value);
            }
        }
#pragma endregion

#pragma region Windows::Foundation::Collections::IVector < Platform::String ^ > ^ InflectionPoints DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ InflectionPointsProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_inflectionPointsProperty;
            }
        }
        property Windows::Foundation::Collections::IVector<Platform::String^> ^ InflectionPoints
        {
            Windows::Foundation::Collections::IVector<Platform::String^> ^ get()
            {
                return static_cast<Windows::Foundation::Collections::IVector<Platform::String^> ^>(GetValue(s_inflectionPointsProperty));
            }
            void set(Windows::Foundation::Collections::IVector<Platform::String^> ^ value)
            {
                SetValue(s_inflectionPointsProperty, value);
            }
        }
#pragma endregion

#pragma region Windows::Foundation::Collections::IObservableMap < Platform::String ^, Platform::String ^ > ^ Monotonicity DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ MonotonicityProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_monotonicityProperty;
            }
        }
        property Windows::Foundation::Collections::IObservableMap<Platform::String^, Platform::String ^> ^ Monotonicity
        {
            Windows::Foundation::Collections::IObservableMap<Platform::String^, Platform::String ^> ^ get()
            {
                return static_cast<Windows::Foundation::Collections::IObservableMap<Platform::String^, Platform::String ^> ^>(GetValue(s_monotonicityProperty));
            }
            void set(Windows::Foundation::Collections::IObservableMap<Platform::String^, Platform::String ^> ^ value)
            {
                SetValue(s_monotonicityProperty, value);
            }
        }
#pragma endregion

#pragma region Windows::Foundation::Collections::IVector < Platform::String ^ > ^ VerticalAsymptotes DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ VerticalAsymptotesProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_verticalAsymptotesProperty;
            }
        }
        property Windows::Foundation::Collections::IVector<Platform::String^> ^ VerticalAsymptotes
        {
            Windows::Foundation::Collections::IVector<Platform::String^> ^ get()
            {
                return static_cast<Windows::Foundation::Collections::IVector<Platform::String^> ^>(GetValue(s_verticalAsymptotesProperty));
            }
            void set(Windows::Foundation::Collections::IVector<Platform::String^> ^ value)
            {
                SetValue(s_verticalAsymptotesProperty, value);
            }
        }
#pragma endregion

#pragma region Windows::Foundation::Collections::IVector < Platform::String ^ > ^ HorizontalAsymptotes DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ HorizontalAsymptotesProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_horizontalAsymptotesProperty;
            }
        }
        property Windows::Foundation::Collections::IVector<Platform::String^> ^ HorizontalAsymptotes
        {
           Windows::Foundation::Collections::IVector<Platform::String^> ^ get()
            {
                return static_cast<Windows::Foundation::Collections::IVector<Platform::String^> ^>(GetValue(s_horizontalAsymptotesProperty));
            }
            void set(Windows::Foundation::Collections::IVector<Platform::String^> ^ value)
            {
                SetValue(s_horizontalAsymptotesProperty, value);
            }
        }
#pragma endregion

#pragma region Windows::Foundation::Collections::IVector < Platform::String ^ > ^ ObliqueAsymptotes DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ ObliqueAsymptotesProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_obliqueAsymptotesProperty;
            }
        }
        property Windows::Foundation::Collections::IVector<Platform::String^> ^ ObliqueAsymptotes
        {
            Windows::Foundation::Collections::IVector<Platform::String^> ^ get()
            {
                return static_cast<Windows::Foundation::Collections::IVector<Platform::String^> ^>(GetValue(s_obliqueAsymptotesProperty));
            }
            void set(Windows::Foundation::Collections::IVector<Platform::String^> ^ value)
            {
                SetValue(s_obliqueAsymptotesProperty, value);
            }
        }
#pragma endregion

#pragma region int TooComplexFeatures DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty^ TooComplexFeaturesProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get()
            {
                return s_tooComplexFeaturesProperty;
            }
        }
        property int TooComplexFeatures
        {
            int get()
            {
                return static_cast<int>(GetValue(s_tooComplexFeaturesProperty));
            }
            void set(int value)
            {
                SetValue(s_tooComplexFeaturesProperty, value);
            }
        }
#pragma endregion

#pragma region int AnalysisError DependencyProperty
        static property Windows::UI::Xaml::DependencyProperty ^ AnalysisErrorProperty
        {
            Windows::UI::Xaml::DependencyProperty ^ get()
            {
                return s_analysisErrorProperty;
            }
        }
        property int AnalysisError
        {
            int get()
            {
                return static_cast<int>(GetValue(s_analysisErrorProperty));
            }
            void set(int value)
            {
                SetValue(s_analysisErrorProperty, value);
            }
        }

#pragma endregion

        internal : event PropertyChangedEventHandler ^ PropertyChanged;

        std::wstring GetRequest();

    private:
        static void OnCustomDependencyPropertyChanged(Windows::UI::Xaml::DependencyObject ^ obj, Windows::UI::Xaml::DependencyPropertyChangedEventArgs ^ args);

        std::wstring GetRequestHeader();
        std::wstring GetExpression();
        std::wstring GetLineColor();

    private:
        static Windows::UI::Xaml::DependencyProperty ^ s_expressionProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_lineColorProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_xInterceptProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_yInterceptProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_parityProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_periodicityDirectionProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_periodicityExpressionProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_minimaProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_maximaProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_domainProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_rangeProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_inflectionPointsProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_monotonicityProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_verticalAsymptotesProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_horizontalAsymptotesProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_obliqueAsymptotesProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_tooComplexFeaturesProperty;
        static Windows::UI::Xaml::DependencyProperty ^ s_analysisErrorProperty;
    };
}
