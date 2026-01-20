#include "pch.h"
#include "canvas.h"
#include "viewport_composer.h"

_PHOXO_BEGIN

namespace
{
    void FillImageCheckerboard(Image& img, CPoint scroll, HBRUSH background)
    {
        BitmapHDC   dc(img);
        ::SetBrushOrgEx(dc, -scroll.x, -scroll.y, NULL); // 加入滚动条偏移
        ::FillRect(dc, CRect({}, img.Size()), background);
    }
}

void CanvasViewport::Draw(HDC hdc, HBRUSH background, const ViewportContext& ctx)
{
    if (!IsCacheValid(ctx))
    {
        RebuildCache(ctx, background);
    }

    POINT   pt = ctx.dst_rect_on_view.TopLeft();
    ::BitBlt(hdc, pt.x, pt.y, m_cache.Width(), m_cache.Height(), BitmapHDC(m_cache), 0, 0, SRCCOPY);
}

bool CanvasViewport::IsCacheValid(const ViewportContext& ctx) const
{
    return m_cache
        && (m_rect_on_zoomed_canvas == ctx.src_rect_on_zoomed_canvas) // zoom区域大小改变，或者滚动条位置改变
        && (m_canvas_total_zoomed_size == m_canvas.ZoomedSize()) // zoom改变
        && (m_canvas_content_ver == m_canvas.ContentVersion()); // canvas内容改变
}

void CanvasViewport::RebuildCache(const ViewportContext& ctx, HBRUSH background)
{
    // 更新缓存帧信息
    m_rect_on_zoomed_canvas = ctx.src_rect_on_zoomed_canvas;
    m_canvas_total_zoomed_size = m_canvas.ZoomedSize();
    m_canvas_content_ver = m_canvas.ContentVersion();

    // 比如滚动图片/图片画线，缓存尺寸是不变的，这里不需要重新创建位图
    if (CSize sz = m_rect_on_zoomed_canvas.Size(); m_cache.Size() != sz)
        m_cache.Create(sz);

    // 填充背景棋盘格
    FillImageCheckerboard(m_cache, ctx.src_rect_on_zoomed_canvas.TopLeft(), background);

    // 渲染 Canvas 到缓存
    ViewportComposer   fx(m_canvas, m_rect_on_zoomed_canvas.TopLeft());
    m_cache.ApplyEffect(fx);
}

_PHOXO_NAMESPACE_END
