#pragma once

namespace crop
{
    enum class GripType
    {
        None,
        ResizeTopLeft,
        ResizeTop,
        ResizeTopRight,
        ResizeLeft,
        ResizeRight,
        ResizeBottomLeft,
        ResizeBottom,
        ResizeBottomRight,
        Move,   // 点击中心，移动整个裁剪框
    };

    class GripHandle
    {
    public:
        const GripType   m_type;
        bool   m_hovered = false;

        GripHandle(GripType type) : m_type(type) {}

        CRect GetHitZone(const CRect& crop_on_view) const;
        void Draw(HDC hdc, const CRect& crop_on_view) const;
        bool UpdateHoverState(CPoint cursor_on_view, const CRect& crop_on_view);
    };
}
