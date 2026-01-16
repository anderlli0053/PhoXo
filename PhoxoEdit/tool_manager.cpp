#include "pch.h"
#include "tool_manager.h"
#include "func_crop/tool_crop.h"

void ToolManager::ActivateTool(ToolType type)
{
    m_activeTool = nullptr;

    switch (type)
    {
    case ToolType::Crop:
        m_activeTool = make_unique<ToolCrop>();
        break;

    case ToolType::None:
        m_activeTool = nullptr;
        break;
    }
}

void ToolManager::Shutdown()
{
    m_activeTool = nullptr;
}
