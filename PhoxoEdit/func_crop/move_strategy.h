#pragma once
#include "grip_handle.h"

namespace crop
{
    class MoveStrategy
    {
    private:
        // 所有坐标都是在canvas上的
        const GripType  m_type;
        const GPointF   m_anchor;
        const CRect     m_begin;
        const CSize     m_canvas_size;

    public:
        MoveStrategy(GripType type, GPointF anchor, const CRect& begin_rect, CSize canvas_size)
            : m_type(type)
            , m_anchor(anchor)
            , m_begin(begin_rect)
            , m_canvas_size(canvas_size)
        {
            assert(type != GripType::None);
        }

        // 返回计算后的裁剪框
        CRect HandleMouseMove(GPointF curr, const CropAspectRatio& ratio);

    private:
        CRect MoveCrop(GPointF delta) const;
        int ClampEdge(double v, GripType edge) const;
        void MoveSingleEdge(CRect& rc, GPointF delta, GripType edge) const;
        void BackCalculateEdge(CRect& rc, double ratio, GripType edge) const;
        CRect ResizeEdge(GPointF delta, GripType edge, const CropAspectRatio& ratio, GripType fixed_side) const;

        CRect ResizeCornerLocked(GPointF delta, const CropAspectRatio& ratio) const;
        CRect ResizeCornerUnlocked(GPointF delta) const;
    };
}
