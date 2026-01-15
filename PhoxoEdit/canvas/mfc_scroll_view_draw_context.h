#pragma once

_PHOXO_BEGIN

// 一共四种形态：NoSB , H-SB , V-SB , H+V-SB
struct ScrollViewDrawContext : public CanvasDrawContext
{
    ScrollViewDrawContext(const Canvas& src_canvas, const CScrollView& view) : CanvasDrawContext{ src_canvas }
    {
        const CSize   view_size = FCWnd::GetClientSize(view);
        const CSize   zoomed_canvas_size = canvas.ZoomedSize();

        // 先充满整个区域再调整
        dst_view_size = view_size;
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

    static GPointF ViewToCanvas(const CScrollView& view, CPoint view_pt, const Canvas& canvas)
    {
        ScrollViewDrawContext   info(canvas, view);
        CPoint   tmp = view_pt - info.dst_rect_on_view.TopLeft() + info.src_rect_on_zoomed_canvas.TopLeft();
        return canvas.ZoomMapper().ToOriginal(tmp);
    }

    GPointF CanvasToView(CPoint canvas_pt) const
    {
        GPointF   tmp = canvas.ZoomMapper().ToZoomed(canvas_pt);
        float   x = tmp.X - src_rect_on_zoomed_canvas.left + dst_rect_on_view.left;
        float   y = tmp.Y - src_rect_on_zoomed_canvas.top + dst_rect_on_view.top;
        return { x,y };
    }

private:
    static void CenterAlign(int view, int canvas, LONG& begin, LONG& end)
    {
        int   diff = view - canvas; ASSERT(diff >= 0);
        begin = diff / 2;
        end = begin + canvas;
    }
};

_PHOXO_NAMESPACE_END
