#pragma once
#include "grip_handle.h"

namespace crop
{
    class MoveStrategy
    {
    private:
        // 所有坐标都是在canvas上的
        GripType  m_type;
        GPointF   m_anchor;
        CRect     m_begin_rect;
        CSize     m_canvas_size;
        bool      m_keep_aspect;

    public:
        MoveStrategy(GripType type, GPointF anchor, const CRect& begin_rect, CSize canvas_size, bool keep_aspect)
            : m_type(type)
            , m_anchor(anchor)
            , m_begin_rect(begin_rect)
            , m_canvas_size(canvas_size)
            , m_keep_aspect(keep_aspect)
        {
        }

        // 返回计算后的裁剪框
        CRect HandleMouseMove(GPointF curr);
    };
}
