#include "pch.h"
#include "move_strategy.h"

_PHOXO_NAMESPACE(crop)

CRect MoveStrategy::HandleMouseMove(GPointF curr)
{
    if (m_type == GripType::Move)
    {
        GPointF   delta = curr - m_anchor;
        CRect   rc = m_begin_rect;
        rc.OffsetRect((int)delta.X, (int)delta.Y);
        return rc;
    }
    return {};
}

_PHOXO_NAMESPACE_END
