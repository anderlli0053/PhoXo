#pragma once
#include "grip_handle.h"
#include "tool_base.h"
#include "mask_overlay.h"

class ToolCrop : public ToolBase
{
private:
    std::optional<CRect>   m_crop_on_canvas;
    std::vector<GripHandle>   m_grip_handles;
    MaskOverlay   m_mask_overlay;

public:
    static inline bool   m_keep_aspect = false;

    void OnEnterTool() override;

    void OnLButtonDown(CMainView& view, UINT nFlags, CPoint point) override;
    void OnDrawToolOverlay(const ScrollViewDrawContext& ctx) override;
};
