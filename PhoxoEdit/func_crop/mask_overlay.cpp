#include "pch.h"
#include "mask_overlay.h"
using namespace phoxo;

MaskOverlay::MaskOverlay()
{
    m_target = D2D::CreateDCRenderTarget(D2D1_RENDER_TARGET_TYPE_SOFTWARE);
    m_target->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), &m_black_brush);
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

void MaskOverlay::UpdateOverlayMask(const CRect& crop_rect)
{
    BitmapHDC   memdc(m_buffer);
    m_target->BindDC(memdc, CRect({}, m_buffer.Size()));

    // 裁剪区域draw，然后处理alpha
    CD2DEllipse   ellipse{ CD2DRectF(crop_rect) };
    m_target->BeginDraw();
    m_target->Clear(D2D1::ColorF(0, 0, 0, 0.5f)); // mask透明度
    m_target->FillEllipse(ellipse, m_black_brush);
    //m_target->FillRectangle(CD2DRectF(crop_rect), m_black_brush);
    m_target->EndDraw();

    // 翻转alpha，让挖空的地方露出来
    if (ImageFastPixel::PixelSpan pv{ m_buffer })
    {
        pv.ForEachPixel([](auto& px) { px.a = 0xFF - px.a; });
    }
}
