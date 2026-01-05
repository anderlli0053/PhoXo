#pragma once

class PanelManager
{
private:
    std::map<UINT, unique_ptr<CBCGPDockingControlBar>>   m_func_panel;
    CBCGPDockingControlBar*   m_current_panel = nullptr;
    UINT   m_current_tab_id = 0;

public:
    UINT CurrentTabID() const { return m_current_tab_id; }

    void OnClickTab(CBCGPFrameWnd& main_wnd, UINT tab_id);
    static CBCGPDockingControlBar* CreatePanel(CWnd* parent, UINT tab_id);
};
