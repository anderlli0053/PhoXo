#pragma once

namespace panel_crop
{
    class CropShapePanel : public CBCGPExpanderCtrl
    {
        void OnSetupDelayedGroup(int nGroupIndex) override;
    };
}
