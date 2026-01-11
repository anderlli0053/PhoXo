#pragma once
#include "tool_base.h"

class ToolCrop : public ToolBase
{
private:
    CRect   m_crop_rect;

public:
    void OnSetCursor() override;
};
