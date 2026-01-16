#include "pch.h"
#include "PhoxoEdit.h"
#include "tool_crop.h"
#include "main_view.h"

namespace
{
    void ZoomForCropMode(const Canvas& canvas)
    {
        CMainView&   view = *theApp.GetActiveView();
        CSize   margin{ DPICalculator::Cast(10), DPICalculator::Cast(10) };
        CRect   rc = FCWnd::GetClientRect(view);
        rc.DeflateRect(margin);
        float   ratio = phoxo::Utils::CalcFitZoomRatio(rc.Size(), canvas.OriginalSize());
        view.UpdateZoomRatio(ratio, ZoomChangedBy::Other);
    }

    CRect GetCropRectOnView(const ScrollViewDrawContext& ctx)
    {
        GPointF   tl = ctx.CanvasToView(ToolCrop::s_crop_on_canvas.TopLeft());
        GPointF   br = ctx.CanvasToView(ToolCrop::s_crop_on_canvas.BottomRight());
        return { (int)floor(tl.X), (int)floor(tl.Y), (int)floor(br.X), (int)floor(br.Y) };
    }
}

ToolCrop::ToolCrop()
{
    OnResetForNewImage();
}

HCURSOR ToolCrop::GetToolCursor(const CMainView& view)
{
    if (auto crop_on_view = GetCropOnView(view))
    {
        POINT   pt{};
        ::GetCursorPos(&pt);
        view.ScreenToClient(&pt);
        if (HCURSOR cursor = m_handle_overlay.GetCursor(pt, *crop_on_view))
            return cursor;
    }
    return __super::GetToolCursor(view);
}

void ToolCrop::OnLButtonDown(CMainView& view, UINT nFlags, CPoint point)
{
    auto   canvas = view.GetCanvas();
    if (!canvas)
        return;

    ScrollViewDrawContext   ctx(*canvas, view);
    CRect   crop_on_view = GetCropRectOnView(ctx);

    auto   type = m_handle_overlay.HitTest(point, crop_on_view);
    if (type == crop::GripType::None)
        return;

    m_move_strategy.emplace(type, ctx.ViewToCanvas(point), s_crop_on_canvas, canvas->OriginalSize(), s_keep_aspect);
    view.SetCapture();
}

void ToolCrop::OnLButtonUp(CMainView& view, UINT nFlags, CPoint point)
{
    m_move_strategy = std::nullopt;
}

void ToolCrop::OnMouseMove(CMainView& view, UINT nFlags, CPoint point)
{
    auto   canvas = view.GetCanvas();
    if (!canvas)
        return;

    ScrollViewDrawContext   ctx(*canvas, view);
    if (m_move_strategy)
    {
        GPointF   pt_on_canvas = ctx.ViewToCanvas(point);
        s_crop_on_canvas = m_move_strategy->HandleMouseMove(pt_on_canvas);
        view.Invalidate();
    }
    else
    {
        CRect   crop_on_view = GetCropRectOnView(ctx);
        if (m_handle_overlay.OnMouseMove(point, *crop_on_view))
        {
            view.Invalidate();
        }
    }
}

void ToolCrop::OnCaptureChanged(CMainView& view)
{
    // ASSERT(!m_move_strategy.has_value());
    m_move_strategy = std::nullopt;
}

void ToolCrop::OnDrawToolOverlay(const ScrollViewDrawContext& ctx)
{
    CRect   rc = GetCropRectOnView(ctx);
    m_mask_overlay.Draw(ctx.dst_hdc, ctx.dst_view_size, rc);
    m_handle_overlay.Draw(ctx, rc);
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
    s_crop_on_canvas = CRect();

    if (auto canvas = theApp.GetCurrentCanvas())
    {
        ZoomForCropMode(*canvas);
        s_crop_on_canvas = CRect(CPoint(), canvas->OriginalSize());
    }
}

std::optional<CRect> ToolCrop::GetCropOnView(const CMainView& view) const
{
    if (auto canvas = view.GetCanvas())
    {
        return GetCropRectOnView(ScrollViewDrawContext(*canvas, view));
    }
    return std::nullopt;
}
