#include "pch.h"
#include "panel_manager.h"
#include "func_crop/panel/wnd_panel_crop_rotate.h"
#include "tool_manager.h"

namespace
{
    ToolType ToolTypeFromTabId(UINT id)
    {
        switch (id)
        {
            case ID_TAB_CROP_ROTATE: return ToolType::Crop;
            case ID_TAB_TEXT:        return ToolType::Text;
            case ID_TAB_ADJUST:      return ToolType::Adjust;
            case ID_TAB_EFFECT:      return ToolType::Effect;
            case ID_TAB_WIDGET:      return ToolType::Widget;
            case ID_TAB_FRAME:       return ToolType::Frame;
            default:                 return ToolType::None;
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

    ToolType   tool_type = ToolTypeFromTabId(tab_id);
    if (!m_current_panel)
        tool_type = ToolType::None;
    theToolManager.ActivateTool(tool_type);
}

CBCGPDockingControlBar* PanelManager::CreatePanel(CWnd* parent, UINT tab_id)
{
    if (tab_id == ID_TAB_CROP_ROTATE)
    {
        auto   dlg = new WndPanelCropRotate;
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
