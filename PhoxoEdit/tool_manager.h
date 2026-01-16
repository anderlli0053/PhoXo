#pragma once
#include "tool_base.h"

class ToolManager : public FCSingleton<ToolManager>
{
public:
    ToolBase* GetActiveTool() const { return m_activeTool.get(); }

    void ActivateTool(ToolType type);
    void Shutdown();

private:
    unique_ptr<ToolBase>   m_activeTool;
};

#define theToolManager ToolManager::GetInstance()
