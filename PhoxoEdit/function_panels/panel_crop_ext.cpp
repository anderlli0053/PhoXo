#include "pch.h"
#include "PhoxoEdit.h"
#include "panel_crop_ext.h"

class WndPanelCropShapePage : public CBCGPDialog
{
    enum
    {
        IDC_SHAPE_RECT = 3000,
        IDC_SHAPE_ROUND_RECT = 3001,
        IDC_SHAPE_CIRCLE = 3002,
    };

    BCGImageButton   m_rect, m_round_rect, m_circle;

public:
    DECLARE_DYNCREATE(WndPanelCropShapePage)

    WndPanelCropShapePage(CWnd* pParent = NULL) : CBCGPDialog(IDD_PANEL_CROP_SHAPE_PAGE, pParent)
    {
        EnableVisualManagerStyle();
    }

    BOOL OnInitDialog() override
    {
        __super::OnInitDialog();

        std::pair<BCGImageButton*, int>   buttons[] =
        {
            { &m_rect, IDSVG_CROP_SHAPE_RECT },
            { &m_round_rect, IDSVG_CROP_SHAPE_ROUND_RECT },
            { &m_circle, IDSVG_CROP_SHAPE_CIRCLE },
        };

        LanguageTextGroup   text(L"panel_crop", 11);
        for (auto [btn, svg] : buttons)
        {
            btn->SetTooltip(text.PopFront());
            btn->SetIcon(PhoxoUtils::LoadSvgWithDpi(svg, PhoxoUtils::GetIconColor()));
        }
        return TRUE;
    }

    void DoDataExchange(CDataExchange* pDX) override
    {
        __super::DoDataExchange(pDX);
        DDX_Control(pDX, IDC_SHAPE_RECT, m_rect);
        DDX_Control(pDX, IDC_SHAPE_ROUND_RECT, m_round_rect);
        DDX_Control(pDX, IDC_SHAPE_CIRCLE, m_circle);
    }
};

IMPLEMENT_DYNCREATE(WndPanelCropShapePage, CBCGPDialog)

_PHOXO_NAMESPACE(panel_crop)

void CropShapePanel::OnSetupDelayedGroup(int nGroupIndex)
{
    AddDialogToGroup(nGroupIndex, IDD_PANEL_CROP_SHAPE_PAGE, RUNTIME_CLASS(WndPanelCropShapePage));
}

_PHOXO_NAMESPACE_END
