#pragma once

#include "Common.h"

struct ID2D1Factory;
struct ID2D1RenderTarget;

namespace Graphing::Renderer
{
    struct IGraphRenderer : public NonCopyable, public NonMoveable
    {
        virtual ~IGraphRenderer() = default;

        virtual HRESULT SetGraphSize(unsigned int width, unsigned int height) = 0;
        virtual HRESULT SetDpi(float dpiX, float dpiY) = 0;

        virtual HRESULT DrawD2D1(ID2D1Factory* pDirect2dFactory, ID2D1RenderTarget* pRenderTarget, bool& hasSomeMissingDataOut) = 0;
        virtual HRESULT GetClosePointData(float inScreenPointX, float inScreenPointY, int& formulaIdOut, float& xScreenPointOut, float& yScreenPointOut, float& xValueOut, float& yValueOut) = 0;

        virtual HRESULT ScaleRange(double centerX, double centerY, double scale) = 0;
        virtual HRESULT ChangeRange(ChangeRangeAction action) = 0;
        virtual HRESULT MoveRangeByRatio(double ratioX, double ratioY) = 0;
        virtual HRESULT ResetRange() = 0;
    };
}
