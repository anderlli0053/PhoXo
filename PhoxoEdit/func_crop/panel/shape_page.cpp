#include "pch.h"
#include "shape_page.h"
#include "local.h"

namespace
{
    enum
    {
        IDC_SHAPE_RECT = 3000,
        IDC_SHAPE_ROUND_RECT = 3001,
        IDC_SHAPE_CIRCLE = 3002,
    };
}

_PHOXO_NAMESPACE(crop)

IMPLEMENT_DYNCREATE(ShapePage, CBCGPDialog)

BEGIN_MESSAGE_MAP(ShapePage, CBCGPDialog)
END_MESSAGE_MAP()

BOOL ShapePage::OnInitDialog()
{
    __super::OnInitDialog();

    BCGImageButton::ButtonInfo   buttons[] =
    {
        { &m_rect, IDSVG_CROP_SHAPE_RECT, 15 },
        { &m_round_rect, IDSVG_CROP_SHAPE_ROUND_RECT, 16 },
        { &m_circle, IDSVG_CROP_SHAPE_CIRCLE, 17 },
    };
    InitButtons(buttons);
    return TRUE;
}

void ShapePage::DoDataExchange(CDataExchange * pDX)
{
    __super::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SHAPE_RECT, m_rect);
    DDX_Control(pDX, IDC_SHAPE_ROUND_RECT, m_round_rect);
    DDX_Control(pDX, IDC_SHAPE_CIRCLE, m_circle);
}

_PHOXO_NAMESPACE_END
