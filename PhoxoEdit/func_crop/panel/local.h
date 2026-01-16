#pragma once

namespace crop
{
    inline CString PanelCropText(int key)
    {
        return LanguageText::Get(L"panel_crop", key);
    }

    inline void InitButtons(std::span<const BCGImageButton::ButtonInfo> buttons)
    {
        for (const auto& [btn, svg, tip] : buttons)
        {
            btn->SetTooltip(PanelCropText(tip));
            btn->LoadSvgWithDpi(svg);
        }
    }
}
