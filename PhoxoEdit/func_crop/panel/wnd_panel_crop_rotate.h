#pragma once
#include "page_expander.h"

class WndPanelCropRotate : public CBCGPDialogBar,
                           public IEventObserverBase
{
private:
    int   m_ratio_index = 0;
    std::map<int, unique_ptr<BCGImageButton>>   m_image_buttons;

    int   m_keep_aspect = FALSE;
    CBCGPEdit   m_width_edit, m_height_edit;

    // 初始shape panel隐藏，点击按钮后展开
    crop::PageExpander   m_shape_panel;

public:
    WndPanelCropRotate();
    void Create(CWnd* parent);

private:
    BCGImageButton& AddImageButton(int id);

    void InitSizeEdit();
    void ResetSizeEdit();
    void UpdateKeepAspectButton();

    void DoDataExchange(CDataExchange* pDX) override;
    void OnObserveEvent(ObservedEvent& event) override;
    void OnEventCanvasReloaded();

    afx_msg void OnEnableIfCanvasValid(CCmdUI* pCmdUI);
    afx_msg void OnPostUpdateKeepAspect();
    afx_msg void OnRatioButton(UINT id);
    afx_msg void OnKeepAspect();
    DECLARE_MESSAGE_MAP()
};
