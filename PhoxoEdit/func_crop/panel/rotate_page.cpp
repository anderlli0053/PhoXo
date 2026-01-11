#include "pch.h"
#include "rotate_page.h"

namespace
{
    enum
    {
        ID_ROTATE_CW = 3300,  // 顺时针 90°
        ID_ROTATE_CCW = 3301, // 逆时针 90°
        ID_FLIP_HORZ = 3302,  // 左右翻转
        ID_FLIP_VERT = 3303,  // 上下翻转
    };
}

_PHOXO_NAMESPACE(crop)

IMPLEMENT_DYNCREATE(RotatePage, CBCGPDialog)

BEGIN_MESSAGE_MAP(RotatePage, CBCGPDialog)
END_MESSAGE_MAP()

BOOL RotatePage::OnInitDialog()
{
    __super::OnInitDialog();

    BCGImageButton::ButtonInfo    buttons[] =
    {
        { &m_cw,     IDSVG_ROTATE_CW, 6 },
        { &m_ccw,    IDSVG_ROTATE_CCW, 7 },
        { &m_flip,   IDSVG_FLIP_VERT, 8 },
        { &m_mirror, IDSVG_FLIP_HORZ, 9 },
    };
    InitButtons(buttons);
    return TRUE;
}

void RotatePage::DoDataExchange(CDataExchange * pDX)
{
    __super::DoDataExchange(pDX);
    DDX_Control(pDX, ID_ROTATE_CW, m_cw);
    DDX_Control(pDX, ID_ROTATE_CCW, m_ccw);
    DDX_Control(pDX, ID_FLIP_HORZ, m_mirror);
    DDX_Control(pDX, ID_FLIP_VERT, m_flip);
}

_PHOXO_NAMESPACE_END
