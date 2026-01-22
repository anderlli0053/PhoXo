#include "pch.h"
#include "panel_manager.h"
#include "func_crop/panel/wnd_panel_crop.h"
#include "func_crop/tool_crop.h"
#include "tool_manager.h"

namespace
{
    std::wstring_view ToolNameFromTabId(UINT id)
    {
        switch (id)
        {
            case ID_TAB_CROP_ROTATE: return ToolCrop::TOOL_NAME;

            default: return {};
        }
    }
}

UINT PanelManager::CurrentTabID() const
{
    if (m_current_panel)
    {
        return m_panel_tab_map.at(m_current_panel->GetDlgCtrlID());
    }
    return 0;
}

void PanelManager::OnClickTab(CBCGPFrameWnd& main_wnd, UINT tab_id)
{
    auto   pos = m_func_panel.find(tab_id);
    if (pos != m_func_panel.end())
    {
        auto   dst_panel = pos->second.get();
        if (m_current_panel == dst_panel)
        {
            m_current_panel->ShowControlBar(FALSE, TRUE, FALSE);
            m_current_panel = nullptr;
        }
        else
        {
            //             if (m_current_panel)
            //             {
            //                 m_current_panel->ShowControlBar(FALSE, TRUE, FALSE);
            //             }
            dst_panel->ShowControlBar(TRUE, TRUE, TRUE);
            m_current_panel = dst_panel;
        }
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

    auto   tool_name = ToolNameFromTabId(tab_id);
    if (m_current_panel)
    {
        theToolManager.ActivateTool(tool_name);
    }
}

CBCGPDockingControlBar* PanelManager::CreatePanel(CWnd* parent, UINT tab_id)
{
    if (tab_id == ID_TAB_CROP_ROTATE)
    {
        auto   dlg = new WndPanelCrop;
        dlg->Create(parent);
        m_panel_tab_map[dlg->GetDlgCtrlID()] = tab_id;
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
