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

void ToolCrop::ResetCropToPresetRatio(int width, int height)
{
    if (auto canvas = theRuntime.GetCurrentCanvas())
    {
        //s_keep_aspect = true;


    }
}

HCURSOR ToolCrop::GetToolCursor(const ViewportContext& ctx)
{
        POINT   pt{};
        ::GetCursorPos(&pt);
        ::ScreenToClient(ctx.m_view, &pt);
        if (HCURSOR cursor = m_handle_overlay.GetCursor(pt, CropOnView(ctx)))
            return cursor;
    return __super::GetToolCursor(ctx);
}

void ToolCrop::OnLButtonDown(CMainView& view, UINT nFlags, CPoint point)
{
    auto   canvas = view.GetCanvas();
    if (!canvas)
        return;

    ViewportContext   ctx(*canvas, view);
    CRect   crop_on_view = CropOnView(ctx);

    auto   type = m_handle_overlay.HitTest(point, crop_on_view);
    if (type == GripType::None)
        return;

    m_move_strategy.emplace(type, ctx.ViewToCanvas(point), s_crop_on_canvas);
}

void ToolCrop::OnLButtonUp(CMainView& view, UINT nFlags, CPoint point)
{
    m_move_strategy = std::nullopt;
}

void ToolCrop::OnMouseMove(CMainView& view, UINT, CPoint point)
{
    auto   canvas = view.GetCanvas();
    if (!canvas)
        return;

    ViewportContext   ctx(*canvas, view);
    if (m_move_strategy)
    {
        s_crop_on_canvas = m_move_strategy->HandleMouseMove(ctx.ViewToCanvas(point), *canvas);
        ctx.InvalidateView();
        IEventObserverBase::FireEvent(AppEvent::CropRectChanged);
    }
    else
    {
        if (m_handle_overlay.OnMouseMove(point, CropOnView(ctx)))
        {
            ctx.InvalidateView();
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
