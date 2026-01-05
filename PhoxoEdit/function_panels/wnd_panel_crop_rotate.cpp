#include "pch.h"
#include "wnd_panel_crop_rotate.h"

void WndPanelCropRotate::Create(CWnd* parent)
{
    CBCGPDialogBar::Create(NULL, parent,
        FALSE,                                  // bHasGripper，是否显示抓手
        MAKEINTRESOURCE(IDD_PANEL_CROP_ROTATE),   // 对话框资源 ID
        WS_VISIBLE | WS_CHILD | CBRS_RIGHT | CBRS_HIDE_INPLACE, // right dock
        ID_PANEL_CROP_ROTATE,
        CBRS_BCGP_REGULAR_TABS,
        CBRS_BCGP_AUTOHIDE
    );

    // EnableDocking(CBRS_ALIGN_RIGHT);

    EnableVisualManagerStyle(TRUE);
}
