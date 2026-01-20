#pragma once
class CMainView; // forward declare

class RuntimeContext : public FCSingleton<RuntimeContext>
{
private:
    COLORREF   m_accent_color = CLR_NONE;
    CBrush     m_accent_brush;

public:
    RuntimeContext();

    CBrush   m_canvas_back;

    HBRUSH GetAccentBrush();

    CMainView* GetActiveView() const;
    void InvalidateView() const;

private:
    void UpdateAccentBrush();
};

#define theRuntime RuntimeContext::GetInstance()
