#pragma once

_PHOXO_BEGIN
class Canvas; // forward declaration

struct CanvasDrawContext
{
public:
    const Canvas&   m_canvas;
    HDC   dst_hdc{};
    HBRUSH   background_brush{};

    // canvas（全部或区域）显示在HDC上区域
    CSize   dst_view_size;
    CRect   dst_rect_on_view;

    // Visible source rect on the zoomed canvas
    // 1. 如果小于view，居中显示，此值等于整个canvas大小 ({0,0} , zoomed_canvas)
    // 2. 大于view，此矩形表示 (scroll_pos , view_size)
    CRect   src_rect_on_zoomed_canvas;

public:
    CanvasDrawContext(const Canvas& canvas) : m_canvas{ canvas }
    {
    }

    void SetHdcAndBrush(HDC hdc, HBRUSH brush)
    {
        dst_hdc = hdc;
        background_brush = brush;
    }
};

_PHOXO_NAMESPACE_END
