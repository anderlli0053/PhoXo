#pragma once

// Ö»»­ÕÚÕÖ²ã£¬ÍÚ¿ÕcropÇøÓò
class MaskOverlay
{
private:
    ID2D1DCRenderTargetPtr   m_target;
    ID2D1SolidColorBrushPtr   m_black_brush;

    FCImage   m_buffer;

public:
    MaskOverlay();

    void Draw(HDC dc, CSize view_size, const CRect& crop_on_view);

private:
    void UpdateOverlayMask(const CRect& crop_rect);
};
