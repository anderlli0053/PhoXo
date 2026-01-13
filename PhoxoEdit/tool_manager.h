#pragma once
#include "tool_base.h"

class ToolManager
{
public:
    static ToolManager& GetInstance()
    {
        static ToolManager   v;
        return v;
    }

    ToolBase* GetActiveTool() const { return m_activeTool; }

    void ActivateTool(ToolType type);

private:
    ToolBase*   m_activeTool = nullptr;
};

#define theToolManager ToolManager::GetInstance()
