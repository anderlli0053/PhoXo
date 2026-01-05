#include "pch.h"
#include "panel_manager.h"
#include "function_panels/wnd_panel_crop_rotate.h"

void PanelManager::OnClickTab(CBCGPFrameWnd& main_wnd, UINT tab_id)
{
    m_current_tab_id = tab_id;

    auto   pos = m_func_panel.find(tab_id);
    if (pos != m_func_panel.end())
    {
        auto   dst_panel = pos->second.get();
        if (m_current_panel == dst_panel)
            return;

//         if (m_current_panel)
//         {
//             m_current_panel->ShowControlBar(FALSE, TRUE, FALSE);
//         }
//         dst_panel->ShowControlBar(TRUE, TRUE, FALSE);
//         m_current_panel = dst_panel;
    }
    else
    {
        auto   new_panel = CreatePanel(&main_wnd, tab_id);
        if (!m_current_panel)
        {
            main_wnd.DockControlBar(new_panel);
        }
        else
        {
//             //m_current_panel->ShowControlBar(FALSE, TRUE, FALSE);
//             new_panel->ShowControlBar(TRUE, FALSE, FALSE);
//             new_panel->DockToWindow(m_current_panel, CBRS_ALIGN_TOP);
//             m_current_panel->ShowControlBar(FALSE, TRUE, FALSE);
// 
//             //main_wnd.DockControlBar(new_panel);
        }
        m_current_panel = new_panel;
        m_func_panel[tab_id].reset(new_panel);
    }
    main_wnd.RecalcLayout();
}

CBCGPDockingControlBar* PanelManager::CreatePanel(CWnd* parent, UINT tab_id)
{
    if (tab_id == ID_TAB_CROP_ROTATE)
    {
        auto   dlg = new WndPanelCropRotate;
        dlg->Create(parent);
        return dlg;
    }
    //     if (tab_id == ID_FUNC_TAB_ROTATE)
    //     {
    //         auto   dlg = new WndFunctionPanelRotate;
    //         dlg->Create();
    //         return dlg;
    //     }
    ASSERT(FALSE);
    return nullptr;
}
