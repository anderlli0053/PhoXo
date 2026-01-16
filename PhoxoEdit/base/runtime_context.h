#pragma once

class RuntimeContext : public FCSingleton<RuntimeContext>
{
private:
    COLORREF   m_accent_color = CLR_NONE;
    CBrush     m_accent_brush;

public:
    RuntimeContext();

    CBrush   m_canvas_back;

    HBRUSH GetAccentBrush();

private:
    void UpdateAccentBrush();
};

#define theRuntime RuntimeContext::GetInstance()
