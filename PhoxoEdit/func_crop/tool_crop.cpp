#include "pch.h"
#include "PhoxoEdit.h"
#include "tool_crop.h"
#include "main_view.h"
using namespace crop;

namespace
{
    void ZoomForCropMode(const Canvas& canvas)
    {
        CMainView&   view = *theRuntime.GetActiveView();
        CSize   margin{ DPICalculator::Cast(10), DPICalculator::Cast(10) };
        CRect   rc = FCWnd::GetClientRect(view);
        rc.DeflateRect(margin);
        float   ratio = phoxo::Utils::CalcFitZoomRatio(rc.Size(), canvas.OriginalSize());
        view.UpdateZoomRatio(ratio, ZoomChangedBy::Other);
    }

    CRect CropOnView(const ViewportContext& ctx)
    {
        GPointF   tl = ctx.CanvasToView(ToolCrop::s_crop_on_canvas.TopLeft());
        GPointF   br = ctx.CanvasToView(ToolCrop::s_crop_on_canvas.BottomRight());
        return { (int)floor(tl.X), (int)floor(tl.Y), (int)floor(br.X), (int)floor(br.Y) };
    }
}

ToolCrop::ToolCrop()
{
    ResetForNewImage();
}

void ToolCrop::SetCropOnCanvas(const CRect& rc)
{
    s_crop_on_canvas = rc;
    theRuntime.InvalidateView();
    IEventObserverBase::FireEvent(AppEvent::CropRectChanged);
}

void ToolCrop::ResetCropToPresetRatio(int width, int height)
{
    if (auto canvas = theRuntime.GetCurrentCanvas())
    {
        //s_keep_aspect = true;


    }
}

HCURSOR ToolCrop::GetToolCursor(const ViewportContext& ctx)
{
    CPoint   pt;
    ::GetCursorPos(&pt);
    ::ScreenToClient(ctx.m_view, &pt);
    if (HCURSOR cursor = m_handle_overlay.GetCursor(pt, CropOnView(ctx)))
        return cursor;
    return __super::GetToolCursor(ctx);
}

void ToolCrop::OnLButtonDown(const ViewportContext& ctx, UINT nFlags, CPoint point)
{
    auto   type = m_handle_overlay.HitTest(point, CropOnView(ctx));
    if (type == GripType::None)
        return;

    m_move_strategy.emplace(type, ctx.ViewToCanvas(point), s_crop_on_canvas);
}

void ToolCrop::OnLButtonUp(const ViewportContext& ctx, UINT nFlags, CPoint point)
{
    m_move_strategy = std::nullopt;
}

void ToolCrop::OnMouseMove(const ViewportContext& ctx, UINT, CPoint point)
{
    if (m_move_strategy)
    {
        s_crop_on_canvas = m_move_strategy->HandleMouseMove(ctx.ViewToCanvas(point), ctx.m_canvas);
        theRuntime.InvalidateView();
        IEventObserverBase::FireEvent(AppEvent::CropRectChanged);
    }
    else
    {
        if (m_handle_overlay.OnMouseMove(point, CropOnView(ctx)))
        {
            theRuntime.InvalidateView();
        }
    }
}

void ToolCrop::OnCaptureChanged()
{
    // ASSERT(!m_move_strategy.has_value());
    m_move_strategy = std::nullopt;
}

void ToolCrop::OnDrawToolOverlay(HDC hdc, const ViewportContext& ctx)
{
    if (s_crop_on_canvas.IsRectEmpty())
        return;

    MaskOverlay::DrawParams   params{
        .shape = s_crop_shape,
        .draw_grid = m_move_strategy.has_value()
    };

    CRect   rc = CropOnView(ctx);
    m_mask_overlay.Draw(hdc, rc, FCWnd::GetClientSize(ctx.m_view), params);
    m_handle_overlay.Draw(hdc, rc);
}

void ToolCrop::OnCanvasReloaded()
{
    ResetForNewImage();
}

void ToolCrop::ResetForNewImage()
{
    s_crop_on_canvas = CRect();
    s_crop_shape = CropShape::Rectangle;
    s_keep_aspect = false;

    if (auto canvas = theRuntime.GetCurrentCanvas())
    {
        ZoomForCropMode(*canvas);
        s_crop_on_canvas = CRect({}, canvas->OriginalSize());
        IEventObserverBase::FireEvent(AppEvent::CanvasReloaded, canvas);
    }
}
