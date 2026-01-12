#pragma once

namespace crop
{
    class ShapePage : public CBCGPDialog
    {
    private:
        BCGImageButton   m_rect, m_round_rect, m_circle;

    public:
        ShapePage()
        {
            EnableVisualManagerStyle();
        }

    private:
        BOOL OnInitDialog() override;
        void DoDataExchange(CDataExchange* pDX) override;

        DECLARE_MESSAGE_MAP()
        DECLARE_DYNCREATE(ShapePage)
    };
}
