#pragma once
class CMainView;

class ToolBase
{
public:
    virtual ~ToolBase() = default;

    virtual HCURSOR GetToolCursor(const CMainView& view)
    {
        return ::LoadCursor(NULL, IDC_ARROW);
    }

    virtual void OnLButtonDown(CMainView& view, UINT nFlags, CPoint point) {}
};

extern ToolBase*   g_activeTool;
