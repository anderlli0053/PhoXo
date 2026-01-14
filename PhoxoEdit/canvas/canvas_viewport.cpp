#include "pch.h"
#include "canvas.h"
#include "viewport_composer.h"

_PHOXO_BEGIN

namespace
{
    void FillImageCheckerboard(Image& img, const CanvasDrawContext& ctx)
    {
        BitmapHDC   dc(img);
        ::SetBrushOrgEx(dc, -ctx.src_rect_on_zoomed_canvas.left, -ctx.src_rect_on_zoomed_canvas.top, NULL); // 加入滚动条偏移
        ::FillRect(dc, CRect({}, img.Size()), ctx.background_brush);
    }
}

void CanvasViewport::Draw(const CanvasDrawContext& ctx)
{
    if (!IsCacheValid(ctx))
    {
        RebuildCache(ctx);
    }

    POINT   pt = ctx.dst_rect_on_view.TopLeft();
    ::BitBlt(ctx.dst_hdc, pt.x, pt.y, m_cache.Width(), m_cache.Height(), BitmapHDC(m_cache), 0, 0, SRCCOPY);
}

bool CanvasViewport::IsCacheValid(const CanvasDrawContext& ctx) const
{
    return m_cache
        && (m_rect_on_zoomed_canvas == ctx.src_rect_on_zoomed_canvas) // zoom区域大小改变，或者滚动条位置改变
        && (m_canvas_total_zoomed_size == m_canvas.ZoomedSize()) // zoom改变
        && (m_canvas_content_ver == m_canvas.ContentVersion()); // canvas内容改变
}

void CanvasViewport::RebuildCache(const CanvasDrawContext& ctx)
{
    // 更新缓存帧信息
    m_rect_on_zoomed_canvas = ctx.src_rect_on_zoomed_canvas;
    m_canvas_total_zoomed_size = m_canvas.ZoomedSize();
    m_canvas_content_ver = m_canvas.ContentVersion();

    // 比如滚动图片/图片画线，缓存尺寸是不变的，这里不需要重新创建位图
    if (CSize sz = m_rect_on_zoomed_canvas.Size(); m_cache.Size() != sz)
        m_cache.Create(sz);

    // 填充背景棋盘格
    FillImageCheckerboard(m_cache, ctx);

    // 渲染 Canvas 到缓存
    ViewportComposer   fx(m_canvas, m_rect_on_zoomed_canvas.TopLeft());
    m_cache.ApplyEffect(fx);
}

_PHOXO_NAMESPACE_END
