#include "pch.h"
#include "local.h"
#include "wnd_panel_crop_rotate.h"
using namespace crop;

namespace
{
    enum
    {
        ID_CROP_FREE = 3000,
        ID_CROP_ORIGINAL = 3001,
        ID_CROP_1_1 = 3002,
        ID_CROP_16_9 = 3003,
        ID_CROP_3_2 = 3004,
        ID_CROP_4_3 = 3005,
        ID_CROP_9_16 = 3006,
        ID_CROP_2_3 = 3007,

        IDC_CROP_WIDTH = 3100,
        IDC_CROP_HEIGHT = 3101,
        ID_KEEP_ASPECT = 3201, // 保持宽高比按钮

        ID_APPLY_CROP = 3200,  // 应用裁剪

        ID_POST_UPDATE_KEEP_ASPECT = 4000,
        ID_CROP_EXPAND_HOLDER = 6000,
    };

    int RatioButtonSvgId(UINT id)
    {
        switch (id)
        {
            case ID_CROP_FREE:      return IDSVG_CROP_FREE;
            case ID_CROP_ORIGINAL:  return IDSVG_CROP_ORIGINAL;
            case ID_CROP_1_1:       return IDSVG_CROP_1_1;
            case ID_CROP_16_9:      return IDSVG_CROP_16_9;
            case ID_CROP_3_2:       return IDSVG_CROP_3_2;
            case ID_CROP_4_3:       return IDSVG_CROP_4_3;
            case ID_CROP_9_16:      return IDSVG_CROP_9_16;
            case ID_CROP_2_3:       return IDSVG_CROP_2_3;
            default:                return 0;
        }
    }

    void SetTextAndTooltip(BCGImageButton& btn, int key)
    {
        LanguageTextGroup   text(PanelCropText(key));
        btn.SetWindowText(text[0]);
        btn.SetTooltip(text[1]);
    }

    DWORD DockStyle()
    {
        return (theConfig.m_panel_dock == PanelDock::Right) ? CBRS_RIGHT : CBRS_LEFT;
    }
}

BEGIN_MESSAGE_MAP(WndPanelCropRotate, CBCGPDialogBar)
    ON_COMMAND_RANGE(ID_CROP_FREE, ID_CROP_2_3, OnRatioButton)
    ON_COMMAND(ID_KEEP_ASPECT, OnKeepAspect)
    ON_COMMAND(ID_POST_UPDATE_KEEP_ASPECT, OnPostUpdateKeepAspect)
END_MESSAGE_MAP()

WndPanelCropRotate::WndPanelCropRotate()
{
    EnableVisualManagerStyle();

    // 构造的时候不能设置text and tip
    for (int id = ID_CROP_FREE; id <= ID_CROP_2_3; id++)
    {
        auto&   btn = AddImageButton(id);
        btn.m_bTopImage = true;
        btn.LoadSvgWithDpi(RatioButtonSvgId(id));
    }
    AddImageButton(ID_KEEP_ASPECT);

    auto&   btn = AddImageButton(ID_APPLY_CROP);
    btn.m_always_default_status = true;
    btn.LoadSvgWithDpi(IDSVG_CROP_APPLY, ThemeMode::InverseBCG);
}

void WndPanelCropRotate::Create(CWnd* parent)
{
    CBCGPDialogBar::Create(NULL, parent,
        FALSE,                             // bHasGripper，是否显示抓手
        MAKEINTRESOURCE(IDD_PANEL_CROP),   // 对话框资源 ID
        WS_VISIBLE | WS_CHILD | DockStyle() | CBRS_HIDE_INPLACE, // left/right dock
        ID_PANEL_CROP_ROTATE,
        CBRS_BCGP_REGULAR_TABS,
        CBRS_BCGP_AUTOHIDE
    );

    SetTextAndTooltip(*m_image_buttons[ID_CROP_FREE], 1);
    SetTextAndTooltip(*m_image_buttons[ID_CROP_ORIGINAL], 2);
    m_image_buttons[ID_APPLY_CROP]->SetWindowText(PanelCropText(3));
    InitSizeEdit();
    UpdateKeepAspectButton();

    m_shape_panel.Create(this, ID_CROP_EXPAND_HOLDER);
}

BCGImageButton& WndPanelCropRotate::AddImageButton(int id)
{
    auto [it, _] = m_image_buttons.try_emplace(id, make_unique<BCGImageButton>());
    return *it->second;
}

void WndPanelCropRotate::InitSizeEdit()
{
    for (auto ctrl : { &m_width_edit, &m_height_edit })
    {
        ctrl->SetLimitText(6);
        ctrl->SetVerticalAlignment(TA_CENTER);
    }
    ResetSizeEdit();
}

void WndPanelCropRotate::ResetSizeEdit()
{
    LanguageTextGroup   text(PanelCropText(0));
    for (auto ctrl : { &m_width_edit, &m_height_edit })
    {
        ctrl->SetWindowText(L"");
        ctrl->SetPrompt(text.PopFront());
    }
}

void WndPanelCropRotate::UpdateKeepAspectButton()
{
    LanguageTextGroup   stat(PanelCropText(5));
    auto&   btn = *m_image_buttons[ID_KEEP_ASPECT];
    btn.SetTooltip(m_keep_aspect ? stat[0] : stat[1], PanelCropText(4), TRUE);
    btn.SetImageEx(PhoxoUtils::LoadSvgWithDpi(m_keep_aspect ? IDSVG_CROP_LINK : IDSVG_CROP_UNLINK, PhoxoUtils::GetIconColor()));
    btn.Invalidate();
}

void WndPanelCropRotate::DoDataExchange(CDataExchange* pDX)
{
    __super::DoDataExchange(pDX);

    for (const auto& [id, btn] : m_image_buttons)
    {
        DDX_Control(pDX, id, *btn);
    }
    DDX_Radio(pDX, ID_CROP_FREE, m_ratio_index);
    DDX_Control(pDX, IDC_CROP_WIDTH, m_width_edit);
    DDX_Control(pDX, IDC_CROP_HEIGHT, m_height_edit);
    // keep aspect
    DDX_Check(pDX, ID_KEEP_ASPECT, m_keep_aspect);
}

void WndPanelCropRotate::OnPostUpdateKeepAspect()
{
    UpdateKeepAspectButton();
}

void WndPanelCropRotate::OnRatioButton(UINT id)
{
    bool   want_keep_aspect = (id != ID_CROP_FREE);
    if (want_keep_aspect != (bool)m_keep_aspect)
    {
        UpdateData();
        m_keep_aspect = !m_keep_aspect;
        UpdateKeepAspectButton();
        UpdateData(FALSE);
    }
}

void WndPanelCropRotate::OnKeepAspect()
{
    UpdateData();
    if (!m_keep_aspect)
        m_ratio_index = 0; // free
    UpdateData(FALSE);

    PostMessage(WM_COMMAND, ID_POST_UPDATE_KEEP_ASPECT); // 在这里更新tip会闪烁，post后处理
}
