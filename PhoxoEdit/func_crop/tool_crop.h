#pragma once
#include "tool_base.h"
#include "mask_overlay.h"
#include "handle_overlay.h"
#include "move_strategy.h"

class ToolCrop : public ToolBase,
                 public IEventObserverBase
{
private:
    crop::MaskOverlay   m_mask_overlay;
    crop::HandleOverlay   m_handle_overlay;
    std::optional<crop::MoveStrategy>   m_move_strategy;

public:
    static inline CRect   s_crop_on_canvas;
    static inline CropShape   s_crop_shape = CropShape::Rectangle;
    static inline bool   s_keep_aspect = false;

    ToolCrop();

    HCURSOR GetToolCursor(const CMainView& view) override;
    void OnLButtonDown(CMainView& view, UINT nFlags, CPoint point) override;
    void OnLButtonUp(CMainView& view, UINT nFlags, CPoint point) override;
    void OnMouseMove(CMainView& view, UINT nFlags, CPoint point) override;
    void OnCaptureChanged(CMainView& view) override;
    void OnDrawToolOverlay(const ScrollViewDrawContext& ctx) override;

    void OnObserveEvent(ObservedEvent& event) override;

private:
    void ResetForNewImage();
};
