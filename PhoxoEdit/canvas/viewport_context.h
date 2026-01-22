#pragma once

_PHOXO_BEGIN
class Canvas; // forward declaration

struct ViewportContext
{
public:
    const Canvas&   m_canvas;
    HWND   m_view{};

    // canvas area drawn on the view
    CRect   dst_rect_on_view;

    // Visible source rect on the zoomed canvas
    // 1) If canvas is smaller than view, this equals the whole zoomed canvas ({0,0} , zoomed_canvas)
    // 2) If canvas is larger than view, this equals (scroll_pos, view_size)
    CRect   src_rect_on_zoomed_canvas;

public:
    ViewportContext(const Canvas& canvas, const CScrollView& view);

    GPointF ViewToCanvas(CPoint view_pos) const;
    GPointF CanvasToView(CPoint canvas_pos) const;
};

_PHOXO_NAMESPACE_END
