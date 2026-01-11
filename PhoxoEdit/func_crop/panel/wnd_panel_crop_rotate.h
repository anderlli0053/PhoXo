#pragma once
#include "page_expander.h"

class WndPanelCropRotate : public CBCGPDialogBar
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

    void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler) override
    {
        __super::OnUpdateCmdUI(pTarget, FALSE); // enable全部控件
    }

    afx_msg void OnPostUpdateKeepAspect();
    afx_msg void OnRatioButton(UINT id);
    afx_msg void OnKeepAspect();
    DECLARE_MESSAGE_MAP()
};
