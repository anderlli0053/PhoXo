#include "pch.h"
#include "move_strategy.h"

_PHOXO_NAMESPACE(crop)

namespace
{
    void ClampToCanvas(CRect& rc, CSize canvas_size)
    {
        if (rc.left < 0)
            rc.OffsetRect(-rc.left, 0);
        if (rc.top < 0)
            rc.OffsetRect(0, -rc.top);
        if (rc.right > canvas_size.cx)
            rc.OffsetRect(canvas_size.cx - rc.right, 0);
        if (rc.bottom > canvas_size.cy)
            rc.OffsetRect(0, canvas_size.cy - rc.bottom);
    }
}

CRect MoveStrategy::HandleMouseMove(GPointF curr, const Canvas& canvas)
{
    const CSize     canvas_size = canvas.OriginalSize();
    const GPointF   delta = curr - m_anchor;
    CRect   rc = m_begin_rect;
    if (m_type == GripType::Move)
    {
        rc.OffsetRect(lround(delta.X), lround(delta.Y));
        ClampToCanvas(rc, canvas_size);
        return rc;
    }

    if (m_type == GripType::ResizeTop)
    {
        rc.top = std::clamp(rc.top + lround(delta.Y), 0L, rc.bottom - 1);

    }

    if (m_type == GripType::ResizeTopLeft || m_type == GripType::ResizeTopRight)
    {
        rc.top = std::clamp(rc.top + lround(delta.Y), 0L, rc.bottom - 1);
    }

    if (m_type == GripType::ResizeBottom || m_type == GripType::ResizeBottomLeft || m_type == GripType::ResizeBottomRight)
    {
        rc.bottom = std::clamp(rc.bottom + lround(delta.Y), rc.top + 1, canvas_size.cy);
    }

    if (m_type == GripType::ResizeLeft || m_type == GripType::ResizeTopLeft || m_type == GripType::ResizeBottomLeft)
    {
        rc.left = std::clamp(rc.left + lround(delta.X), 0L, rc.right - 1);
    }

    if (m_type == GripType::ResizeRight || m_type == GripType::ResizeTopRight || m_type == GripType::ResizeBottomRight)
    {
        rc.right = std::clamp(rc.right + lround(delta.X), rc.left + 1, canvas_size.cx);
    }
    return rc;
}

_PHOXO_NAMESPACE_END
