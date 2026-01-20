#include "pch.h"
#include "runtime_context.h"

namespace
{
    void CreateCanvasGridBack(CBrush& br)
    {
        using namespace Gdiplus;
        phoxo::effect::CheckerFill   eff(FCColor(Color::Silver), FCColor(Color::White), 16);
        FCImage   img;
        img.Create(32, 32);
        img.ApplyEffect(eff);
        br.Attach(::CreatePatternBrush(img));
    }
}

RuntimeContext::RuntimeContext()
{
    CreateCanvasGridBack(m_canvas_back);
}

HBRUSH RuntimeContext::GetAccentBrush()
{
    UpdateAccentBrush();
    return m_accent_brush;
}

CMainView* RuntimeContext::GetActiveView() const
{
    if (auto main = (CFrameWnd*)AfxGetMainWnd())
    {
        return (CMainView*)main->GetActiveView();
    }
    return nullptr;
}

void RuntimeContext::InvalidateView() const
{
    if (auto view = (CView*)GetActiveView())
    {
        view->Invalidate();
    }
}

void RuntimeContext::UpdateAccentBrush()
{
    COLORREF   new_color = CBCGPVisualManager::GetInstance()->GetDefaultAccentColor();
    if (new_color != m_accent_color)
    {
        m_accent_color = new_color;
        m_accent_brush.DeleteObject();
        m_accent_brush.CreateSolidBrush(m_accent_color);
    }
}
