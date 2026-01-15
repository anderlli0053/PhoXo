#include "pch.h"
#include "tool_crop.h"
#include "main_view.h"

namespace
{
    void ZoomForCropMode(CMainView& view, CSize actual_size)
    {
        CSize   margin{ DPICalculator::Cast(10), DPICalculator::Cast(10) };
        CRect   rc = FCWnd::GetClientRect(view);
        rc.DeflateRect(margin);
        float   ratio = phoxo::Utils::CalcFitZoomRatio(rc.Size(), actual_size);
        view.UpdateZoomRatio(ratio, ZoomChangedBy::Other);
    }
}

void ToolCrop::OnEnterTool()
{
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
        CSize   actual_size = canvas->OriginalSize();
        ZoomForCropMode(view, actual_size);
        m_crop_on_canvas.emplace(CPoint(), actual_size);
    }
}

void ToolCrop::OnDrawToolOverlay(const ScrollViewDrawContext& ctx)
{
    if (m_crop_on_canvas)
    {
        GPointF   tl = ctx.CanvasToView(m_crop_on_canvas->TopLeft());
        GPointF   br = ctx.CanvasToView(m_crop_on_canvas->BottomRight());
        CRect   rc{ (int)ceil(tl.X), (int)ceil(tl.Y), (int)floor(br.X), (int)floor(br.Y) };
        m_mask_overlay.Draw(ctx.dst_hdc, ctx.dst_view_size, rc);
    }
}

void ToolCrop::OnResetForNewImage()
{
    m_crop_on_canvas = std::nullopt;
}
