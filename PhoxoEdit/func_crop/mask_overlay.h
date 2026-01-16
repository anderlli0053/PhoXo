#pragma once

namespace crop
{
    // ÷ªª≠’⁄’÷≤„£¨Õ⁄ø’crop«¯”Ú
    class MaskOverlay
    {
    private:
        ID2D1DCRenderTargetPtr   m_target;
        ID2D1SolidColorBrushPtr   m_black_brush;
        ID2D1SolidColorBrushPtr   m_grid_brush;

        FCImage   m_buffer;

    public:
        MaskOverlay();

        void Draw(HDC dc, CSize view_size, const CRect& crop_on_view);

    private:
        void UpdateOverlayMask(const CRect& crop_on_view);
        void DrawGridLines(const CRect& crop_on_view);
    };
}
