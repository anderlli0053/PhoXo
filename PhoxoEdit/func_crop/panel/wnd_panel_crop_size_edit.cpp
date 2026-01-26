#include "pch.h"
#include "local.h"
#include "wnd_panel_crop.h"
#include "../tool_crop.h"
using namespace crop;

namespace
{
    int GetEditInt(const CWnd& wnd)
    {
        CString   str;
        wnd.GetWindowText(str);
        return StrToInt(str);
    }

    bool HandleOversize(int width, int height, CSize canvas_size)
    {
        if (width > canvas_size.cx || height > canvas_size.cy)
        {
            // 尺寸超出canvas，居中显示
            ToolCrop::ApplyCropAspectRatio(width, height);
            return true;
        }
        return false;
    }
}

void WndPanelCrop::InitSizeEdit()
{
    for (auto ctrl : { &m_width_edit, &m_height_edit })
    {
        ctrl->SetLimitText(6);
        ctrl->SetVerticalAlignment(TA_CENTER);
    }
    UpdateSizeEdit();
}

void WndPanelCrop::UpdateSizeEdit()
{
    if (CSize sz = ToolCrop::s_crop_on_canvas.Size(); sz.cx && sz.cy)
    {
        m_width_edit.SetWindowText(FCString::From(sz.cx));
        m_height_edit.SetWindowText(FCString::From(sz.cy));
    }
    else
    {
        LanguageTextGroup   text(PanelCropText(0));
        for (auto ctrl : { &m_width_edit, &m_height_edit })
        {
            ctrl->SetWindowText(L"");
            ctrl->SetPrompt(text.PopFront());
        }
    }
}

void WndPanelCrop::ApplyCropSizeFromSingleEdit(HWND edit_ctrl)
{
    auto   canvas = theRuntime.GetCurrentCanvas();
    if (!canvas)
        return;

    const CSize   canvas_size = canvas->Size();

    CRect   rc = ToolCrop::s_crop_on_canvas;
    if (edit_ctrl == m_width_edit)
    {
        if (int width = GetEditInt(m_width_edit); width > 0)
        {
            rc.right = rc.left + width;
            if (ToolCrop::s_aspect_ratio.IsLocked())
            {
                int   height = std::max<int>(1, (int)(width / ToolCrop::s_aspect_ratio.Value()));
                rc.bottom = rc.top + height;
                if (HandleOversize(width, height, canvas_size))
                    return;
            }
        }
    }
    else
    {
        if (int height = GetEditInt(m_height_edit); height > 0)
        {
            rc.bottom = rc.top + height;
            if (ToolCrop::s_aspect_ratio.IsLocked())
            {
                int   width = std::max<int>(1, (int)(height * ToolCrop::s_aspect_ratio.Value()));
                rc.right = rc.left + width;
                if (HandleOversize(width, height, canvas_size))
                    return;
            }
        }
    }

    // 推回canvas内
    FCWnd::MoveRectInside(rc, canvas_size);

    // 必须调用，如果用户输入无效值，则恢复显示当前值
    ToolCrop::SetCropOnCanvas(rc);
}

void WndPanelCrop::OnWidthEditKillFocus()
{
    ApplyCropSizeFromSingleEdit(m_width_edit);
}

void WndPanelCrop::OnHeightEditKillFocus()
{
    ApplyCropSizeFromSingleEdit(m_height_edit);
}

BOOL WndPanelCrop::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
    {
        HWND   focus = ::GetFocus();
        if (focus == m_width_edit)
        {
            ApplyCropSizeFromSingleEdit(m_width_edit);
            m_width_edit.SetSel(0, -1);
            return TRUE;
        }
        else if (focus == m_height_edit)
        {
            ApplyCropSizeFromSingleEdit(m_height_edit);
            m_height_edit.SetSel(0, -1);
            return TRUE;
        }
    }
    return __super::PreTranslateMessage(pMsg);
}
