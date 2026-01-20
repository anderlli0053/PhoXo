#include "pch.h"
#include "tool_manager.h"
#include "func_crop/tool_crop.h"

void ToolManager::ActivateTool(std::wstring_view tool_name)
{
    // 如果当前已经是同一个 tool，就不做任何事
    if (m_activeTool && m_activeTool->GetToolName() == tool_name)
        return;

    if (tool_name == ToolCrop::TOOL_NAME)
    {
        m_activeTool = make_unique<ToolCrop>();
    }
}

void ToolManager::Shutdown()
{
    m_activeTool = nullptr;
}
