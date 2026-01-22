#include "pch.h"
#include "handle_overlay.h"

_PHOXO_NAMESPACE(crop)

HCURSOR GripCursorByType(GripType type)
{
    using enum GripType;
    switch (type)
    {
        case ResizeTopLeft:
        case ResizeBottomRight:
            return ::LoadCursor(NULL, IDC_SIZENWSE);
        case ResizeTopRight:
        case ResizeBottomLeft:
            return ::LoadCursor(NULL, IDC_SIZENESW);
        case ResizeTop:
        case ResizeBottom:
            return ::LoadCursor(NULL, IDC_SIZENS);
        case ResizeLeft:
        case ResizeRight:
            return ::LoadCursor(NULL, IDC_SIZEWE);
        case Move:
            return ::LoadCursor(NULL, IDC_SIZEALL);
    }
    return NULL;
}

HandleOverlay::HandleOverlay()
{
    using enum GripType;
    m_grip_handles.reserve(8);
    m_grip_handles.emplace_back(ResizeTopLeft);
    m_grip_handles.emplace_back(ResizeTop);
    m_grip_handles.emplace_back(ResizeTopRight);
    m_grip_handles.emplace_back(ResizeLeft);
    m_grip_handles.emplace_back(ResizeRight);
    m_grip_handles.emplace_back(ResizeBottomLeft);
    m_grip_handles.emplace_back(ResizeBottom);
    m_grip_handles.emplace_back(ResizeBottomRight);
}

GripType HandleOverlay::HitTest(CPoint pt_on_view, const CRect& crop_on_view) const
{
    for (const auto& handle : m_grip_handles)
    {
        if (handle.GetHitZone(crop_on_view).PtInRect(pt_on_view))
            return handle.m_type;
    }

    if (crop_on_view.PtInRect(pt_on_view))
        return GripType::Move;
    return GripType::None;
}

HCURSOR HandleOverlay::GetCursor(CPoint cursor_on_view, const CRect& crop_on_view) const
{
    auto   type = HitTest(cursor_on_view, crop_on_view);
    return (type != GripType::None) ? GripCursorByType(type) : NULL;
}

void HandleOverlay::Draw(HDC hdc, const CRect& crop_on_view) const
{
    CRect   rc = crop_on_view;
    rc.InflateRect(1, 1);
    ::FrameRect(hdc, rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
    rc.InflateRect(1, 1);
    ::FrameRect(hdc, rc, (HBRUSH)GetStockObject(WHITE_BRUSH));

    for (const auto& handle : m_grip_handles)
    {
        handle.Draw(hdc, crop_on_view);
    }
}

bool HandleOverlay::OnMouseMove(CPoint pt_on_view, const CRect& crop_on_view)
{
    // 可能从一个handle瞬间移动到另一个handle，需要全部更新
    int   count = 0;
    for (auto& handle : m_grip_handles)
    {
        if (handle.UpdateHoverState(pt_on_view, crop_on_view))
            count++;
    }
    return (count > 0);
}

_PHOXO_NAMESPACE_END
