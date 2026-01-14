#include "pch.h"
#include "tool_crop.h"
#include "main_view.h"

namespace
{
    void ZoomForCropMode(CMainView& view, Canvas& canvas)
    {
        CSize   margin{ DPICalculator::Cast(10), DPICalculator::Cast(10) };
        CRect   rc = FCWnd::GetClientRect(view);
        rc.DeflateRect(margin);
        float   ratio = phoxo::Utils::CalcFitZoomRatio(rc.Size(), canvas.OriginalSize());
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
        ZoomForCropMode(view, *canvas);
        m_crop_on_canvas.emplace(CPoint(), canvas->OriginalSize());
    }
}

void ToolCrop::OnDrawToolOverlay(CMainView& view, const CanvasDrawContext& ctx)
{
    if (m_crop_on_canvas)
    {
        m_mask_overlay.Draw(ctx, *m_crop_on_canvas);
    }
}
