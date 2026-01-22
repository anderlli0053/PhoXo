#pragma once

class ToolBase
{
public:
    virtual ~ToolBase() = default;

    //----------------------------------------
    // Tool 生命周期
    //----------------------------------------
//     virtual void OnEnterTool() {} 暂时没用上，以后需要时再加
//     virtual void OnLeaveTool() {}

    virtual std::wstring_view GetToolName() const = 0;
    virtual void OnCanvasReloaded() {} // 画布变化

    //----------------------------------------
    // 光标：不能返回NULL
    //----------------------------------------
    virtual HCURSOR GetToolCursor(const ViewportContext& ctx)
    {
        return ::LoadCursor(NULL, IDC_ARROW);
    }

    //----------------------------------------
    // 鼠标事件
    //----------------------------------------
    virtual void OnLButtonDown(const ViewportContext& ctx, UINT nFlags, CPoint point) {}
    virtual void OnLButtonUp(const ViewportContext& ctx, UINT nFlags, CPoint point) {}
    virtual void OnMouseMove(const ViewportContext& ctx, UINT nFlags, CPoint point) {}

    // capture 变化时调用
    virtual void OnCaptureChanged() {}

    //----------------------------------------
    // 绘制 Tool 的覆盖层（辅助线 / 选框 / mask等）
    //----------------------------------------
    virtual void OnDrawToolOverlay(HDC hdc, const ViewportContext& ctx) {}
};
