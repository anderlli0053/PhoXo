#include "pch.h"
#include "tool_manager.h"
#include "func_crop/tool_crop.h"

void ToolManager::ActivateTool(ToolType type)
{
    if (m_activeTool)
        m_activeTool->OnLeaveTool();

    switch (type)
    {
    case ToolType::Crop:
        m_activeTool = new ToolCrop();
        break;

    case ToolType::None:
        m_activeTool = nullptr;
        break;
    }

    if (m_activeTool)
        m_activeTool->OnEnterTool();
}
