#include "pch.h"
#include "tool_manager.h"
#include "func_crop/tool_crop.h"

void ToolManager::ActivateTool(ToolType type)
{
    if (m_activeTool)
    {
        m_activeTool->OnLeaveTool();
        m_activeTool = nullptr;
    }

    switch (type)
    {
    case ToolType::Crop:
        m_activeTool = make_unique<ToolCrop>();
        break;

    case ToolType::None:
        m_activeTool = nullptr;
        break;
    }

    if (m_activeTool)
        m_activeTool->OnEnterTool();
}

void ToolManager::Shutdown()
{
    UnregisterObserver();
    m_activeTool = nullptr;
}

void ToolManager::OnObserveEvent(ObservedEvent& event)
{
    if (event.m_type == (int)AppEvent::ImageChanged)
    {
        if (m_activeTool)
            m_activeTool->OnResetForNewImage();
    }
}
