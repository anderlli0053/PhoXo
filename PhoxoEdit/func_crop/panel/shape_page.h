#pragma once

namespace crop
{
    class ShapePage : public CBCGPDialog
    {
    private:
        BCGImageButton   m_rect, m_round_rect, m_circle;
        int   m_shape_index;

    public:
        ShapePage();

    private:
        BOOL OnInitDialog() override;
        void DoDataExchange(CDataExchange* pDX) override;

        afx_msg void OnSelectShape(UINT id);
        DECLARE_MESSAGE_MAP()
        DECLARE_DYNCREATE(ShapePage)
    };
}
