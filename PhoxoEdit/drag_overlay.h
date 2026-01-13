#pragma once

class IDragOverlay
{
public:
    virtual ~IDragOverlay() = default;

    virtual void OnDraw(CDC& dc, const CMainView& view) = 0;
    virtual void OnDragMouseMove(UINT flags, CPoint point) = 0;
};

class DragOverlayRect : public IDragOverlay
{
public:
    CRect   m_rect;

    //void OnDraw(CDC& dc, const CMainView& view) override;
};
