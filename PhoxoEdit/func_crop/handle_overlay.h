#pragma once
#include "grip_handle.h"

namespace crop
{
    // 负责画8个调整把手，hittest等
    class HandleOverlay
    {
    private:
        std::vector<GripHandle>   m_grip_handles;

    public:
        HandleOverlay();

        GripType HitTest(CPoint pt_on_view, const CRect& crop_on_view) const;
        HCURSOR GetCursor(CPoint cursor_on_view, const CRect& crop_on_view) const;

        void Draw(HDC hdc, const CRect& crop_on_view) const;
        bool OnMouseMove(CPoint pt_on_view, const CRect& crop_on_view);
    };
}
