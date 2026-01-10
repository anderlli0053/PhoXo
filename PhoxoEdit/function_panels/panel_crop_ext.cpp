#include "pch.h"
#include "PhoxoEdit.h"
#include "panel_crop_ext.h"
#include "../panel_crop/rotate_page.h"

class WndPanelCropShapePage : public CBCGPDialog
{
    enum
    {
        IDC_SHAPE_RECT = 3000,
        IDC_SHAPE_ROUND_RECT = 3001,
        IDC_SHAPE_CIRCLE = 3002,
    };

    BCGImageButton   m_rect, m_round_rect, m_circle;

    DECLARE_DYNCREATE(WndPanelCropShapePage)

public:
    WndPanelCropShapePage(CWnd* pParent = NULL) : CBCGPDialog(IDD_PANEL_CROP_SHAPE_PAGE, pParent)
    {
        EnableVisualManagerStyle();
        EnableLayout();
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
            btn->LoadSvgWithDpi(svg);
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

namespace
{
    HICON BuildGroupIcon(int svg_res_id)
    {
        FCResource   res(svg_res_id, L"SVG");
        FCImage   img = phoxo::ImageHandler::Make(res.LoadSvgWithDpi(), WICNormal32bpp);
        FCColor   cls = PhoxoUtils::GetIconColor();
        phoxo::ImageFastPixel::FillRGBKeepAlpha(img, cls);
        return FCIcon::CreateIcon(img);
    }
}

IMPLEMENT_DYNCREATE(WndPanelCropShapePage, CBCGPDialog)

_PHOXO_NAMESPACE(panel_crop)

void CropShapePanel::Create(CWnd* parent, UINT placeholder_id)
{
    CreateOnPlaceHolder(parent, placeholder_id, ID_PANEL_CROP_EXT_PAGES);

    AddRotatePage(LanguageText::Get(L"panel_crop", 12));

    int   group = AddDelayedGroup(LanguageText::Get(L"panel_crop", 10));
    SetGroupIcon(group, BuildGroupIcon(IDSVG_GROUP_SHAPE), TRUE);
}

void CropShapePanel::AddRotatePage(CStringRef caption)
{
    int   group = AddDialog(caption, IDD_PANEL_CROP_ROTATE_PAGE, RUNTIME_CLASS(RotatePage));
    SetGroupIcon(group, BuildGroupIcon(IDSVG_GROUP_ROTATE), TRUE);
}

void CropShapePanel::OnSetupDelayedGroup(int nGroupIndex)
{
    AddDialogToGroup(nGroupIndex, IDD_PANEL_CROP_SHAPE_PAGE, RUNTIME_CLASS(WndPanelCropShapePage));
}

_PHOXO_NAMESPACE_END
