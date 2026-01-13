#pragma once
class CMainView;

enum class ToolType
{
    None,
    Crop,
    Text,
    Adjust,
    Effect,
    Widget,
    Frame
};

class ToolBase
{
public:
    virtual ~ToolBase() = default;

    //----------------------------------------
    // Tool 生命周期
    //----------------------------------------
    virtual void OnEnterTool() {}
    virtual void OnLeaveTool() {}

    //----------------------------------------
    // 光标：Tool 决定当前光标
    //----------------------------------------
    virtual HCURSOR GetToolCursor(const CMainView& view)
    {
        return ::LoadCursor(NULL, IDC_ARROW);
    }

    //----------------------------------------
    // 鼠标事件
    //----------------------------------------
    virtual void OnLButtonDown(CMainView& view, UINT nFlags, CPoint point) {}
    virtual void OnMouseMove(CMainView& view, UINT nFlags, CPoint point) {}
    virtual void OnLButtonUp(CMainView& view, UINT nFlags, CPoint point) {}

    //----------------------------------------
    // 绘制 Tool 的覆盖层（辅助线 / 选框 / 高亮等）
    //----------------------------------------
    virtual void OnDrawToolOverlay(CMainView& view) {}
};
