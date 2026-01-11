#pragma once

class ToolContext
{
public:
    virtual CPoint  GetCursorPos() const = 0;
    virtual bool    IsZoomed() const = 0;
    virtual HCURSOR LoadCursor(int id) const = 0;
};

class ToolBase
{
public:
    virtual ~ToolBase() = default;
};

extern ToolBase*   g_activeTool;
