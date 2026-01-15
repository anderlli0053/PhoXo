#pragma once
#include "tool_base.h"

class ToolManager : public IEventObserverBase
{
public:
    static ToolManager& GetInstance()
    {
        static ToolManager   v;
        return v;
    }

    ToolBase* GetActiveTool() const { return m_activeTool.get(); }

    void ActivateTool(ToolType type);
    void Shutdown();

private:
    void OnObserveEvent(ObservedEvent& event) override;

private:
    unique_ptr<ToolBase>   m_activeTool;
};

#define theToolManager ToolManager::GetInstance()
