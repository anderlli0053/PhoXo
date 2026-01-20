#include "pch.h"
#include "canvas.h"

_PHOXO_BEGIN

GPointF ViewportContext::ViewToCanvas(CPoint view_pos) const
{
    CPoint   tmp = view_pos - dst_rect_on_view.TopLeft() + src_rect_on_zoomed_canvas.TopLeft();
    return m_canvas.ZoomMapper().ToOriginal(tmp);
}

GPointF ViewportContext::CanvasToView(CPoint canvas_pos) const
{
    GPointF   tmp = m_canvas.ZoomMapper().ToZoomed(canvas_pos);
    float   x = tmp.X - src_rect_on_zoomed_canvas.left + dst_rect_on_view.left;
    float   y = tmp.Y - src_rect_on_zoomed_canvas.top + dst_rect_on_view.top;
    return { x,y };
}

namespace
{
    static void CenterAlign(int view, int canvas, LONG& begin, LONG& end)
    {
        int   diff = view - canvas; assert(diff >= 0);
        begin = diff / 2;
        end = begin + canvas;
    }
}

// 一共四种形态：No-SB , Horz-SB , Vert-SB , H+V-SB
ViewportContext::ViewportContext(const Canvas& canvas, const CScrollView& view) : m_canvas{ canvas }, m_view{ view.m_hWnd }
{
    const CSize   view_size = FCWnd::GetClientSize(view);
    const CSize   zoomed_canvas_size = canvas.ZoomedSize();

    // 先充满整个区域再调整
    dst_rect_on_view = CRect({}, view_size);
    src_rect_on_zoomed_canvas = CRect({}, zoomed_canvas_size);

    BOOL   horz, vert;
    view.CheckScrollBars(horz, vert);
    if (!horz)
    {
        CenterAlign(view_size.cx, zoomed_canvas_size.cx, dst_rect_on_view.left, dst_rect_on_view.right);
    }
    else
    {
        src_rect_on_zoomed_canvas.left = view.GetScrollPos(SB_HORZ);
        src_rect_on_zoomed_canvas.right = src_rect_on_zoomed_canvas.left + view_size.cx;
    }

    if (!vert)
    {
        CenterAlign(view_size.cy, zoomed_canvas_size.cy, dst_rect_on_view.top, dst_rect_on_view.bottom);
    }
    else
    {
        src_rect_on_zoomed_canvas.top = view.GetScrollPos(SB_VERT);
        src_rect_on_zoomed_canvas.bottom = src_rect_on_zoomed_canvas.top + view_size.cy;
    }
}

_PHOXO_NAMESPACE_END
