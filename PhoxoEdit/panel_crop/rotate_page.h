#pragma once

namespace panel_crop
{
    class RotatePage : public CBCGPDialog
    {
    private:
        BCGImageButton   m_cw, m_ccw, m_mirror, m_flip;

    public:
        RotatePage()
        {
            EnableVisualManagerStyle();
        }

    private:
        BOOL OnInitDialog() override;
        void DoDataExchange(CDataExchange* pDX) override;

        DECLARE_MESSAGE_MAP()
        DECLARE_DYNCREATE(RotatePage)
    };
}
