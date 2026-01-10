#pragma once

namespace panel_crop
{
    class CropShapePanel : public CBCGPExpanderCtrl
    {
    public:
        void Create(CWnd* parent, UINT placeholder_id);
        void AddRotatePage(CStringRef caption);
        void OnSetupDelayedGroup(int nGroupIndex) override;
    };
}
