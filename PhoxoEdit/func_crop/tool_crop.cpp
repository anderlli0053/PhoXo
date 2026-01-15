#include "pch.h"
#include "PhoxoEdit.h"
#include "tool_crop.h"
#include "main_view.h"

namespace
{
    void ZoomForCropMode(const Canvas canvas)
    {
        CMainView&   view = *theApp.GetActiveView();
        CSize   margin{ DPICalculator::Cast(10), DPICalculator::Cast(10) };
        CRect   rc = FCWnd::GetClientRect(view);
        rc.DeflateRect(margin);
        float   ratio = phoxo::Utils::CalcFitZoomRatio(rc.Size(), canvas.OriginalSize());
        view.UpdateZoomRatio(ratio, ZoomChangedBy::Other);
    }
}

void ToolCrop::OnEnterTool()
{
    OnResetForNewImage();
}

void ToolCrop::OnLButtonDown(CMainView& view, UINT nFlags, CPoint point)
{
    auto   canvas = view.GetCanvas();
    if (!canvas)
        return;

    if (m_crop_on_canvas)
    {
        // ´¦Àí²Ã¼ô¾ØÐÎ
    }
    else
    {
        ZoomForCropMode(*canvas);
        m_crop_on_canvas.emplace(CPoint(), canvas->OriginalSize());
    }
}

void ToolCrop::OnDrawToolOverlay(const ScrollViewDrawContext& ctx)
{
    if (m_crop_on_canvas)
    {
        GPointF   tl = ctx.CanvasToView(m_crop_on_canvas->TopLeft());
        GPointF   br = ctx.CanvasToView(m_crop_on_canvas->BottomRight());
        CRect   rc{ (int)floor(tl.X), (int)floor(tl.Y), (int)floor(br.X), (int)floor(br.Y) };
        m_mask_overlay.Draw(ctx.dst_hdc, ctx.dst_view_size, rc);
    }
}

void ToolCrop::OnObserveEvent(ObservedEvent& event)
{
    if (event.m_type == (int)AppEvent::ImageChanged)
    {
        OnResetForNewImage();
    }
}

void ToolCrop::OnResetForNewImage()
{
    m_crop_on_canvas = std::nullopt;

    if (auto canvas = theApp.GetCurrentCanvas())
    {
        ZoomForCropMode(*canvas);
        m_crop_on_canvas.emplace(CPoint(), canvas->OriginalSize());
    }
}
