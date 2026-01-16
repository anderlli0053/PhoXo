#include "pch.h"
#include "mask_overlay.h"
using namespace phoxo;
using namespace D2D1;

_PHOXO_NAMESPACE(crop)

MaskOverlay::MaskOverlay()
{
    m_target = D2D::CreateDCRenderTarget(D2D1_RENDER_TARGET_TYPE_SOFTWARE);
    m_target->CreateSolidColorBrush(ColorF(ColorF::Black, 1), &m_black_brush);
    m_target->CreateSolidColorBrush(ColorF(ColorF::White, 0.5f), &m_grid_brush);
}

void MaskOverlay::Draw(HDC dc, CSize view_size, const CRect& crop_on_view)
{
    if (m_buffer.Size() != view_size)
    {
        m_buffer.Create(view_size);
    }

    UpdateOverlayMask(crop_on_view);
    ImageDrawer::Draw(dc, { 0,0 }, m_buffer);
}

void MaskOverlay::UpdateOverlayMask(const CRect& crop_on_view)
{
    BitmapHDC   memdc(m_buffer);
    m_target->BindDC(memdc, CRect({}, m_buffer.Size()));

    // 裁剪区域draw，然后处理alpha
    CD2DEllipse   ellipse{ CD2DRectF(crop_on_view) };
    m_target->BeginDraw();
    m_target->Clear(ColorF(ColorF::Black, 0.5f)); // mask透明度
    m_target->FillEllipse(ellipse, m_black_brush);
    //m_target->FillRectangle(CD2DRectF(crop_on_view), m_black_brush);
    m_target->EndDraw();

    // 翻转alpha，让挖空的地方露出来
    if (ImageFastPixel::PixelSpan pv{ m_buffer })
    {
        pv.ForEachPixel([](auto& px) { px.a = 0xFF - px.a; });
    }

    DrawGridLines(crop_on_view);
}

void MaskOverlay::DrawGridLines(const CRect& crop_on_view)
{
    CD2DRectF   rc(crop_on_view);
    m_target->BeginDraw();
    float   width = (float)crop_on_view.Width();
    float   height = (float)crop_on_view.Height();

    float   x1 = rc.left + round(width / 3) + 0.5f;
    float   x2 = rc.left + round(width / 3) * 2 + 0.5f;
    float   y1 = rc.top + round(height / 3) + 0.5f;
    float   y2 = rc.top + round(height / 3) * 2 + 0.5f;

    m_target->DrawLine({ x1, rc.top }, { x1, rc.bottom }, m_grid_brush);
    m_target->DrawLine({ x2, rc.top }, { x2, rc.bottom }, m_grid_brush);
    m_target->DrawLine({ rc.left, y1 }, { rc.right, y1 }, m_grid_brush);
    m_target->DrawLine({ rc.left, y2 }, { rc.right, y2 }, m_grid_brush);
    m_target->EndDraw();
}

_PHOXO_NAMESPACE_END
