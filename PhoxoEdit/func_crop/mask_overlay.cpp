#include "pch.h"
#include "mask_overlay.h"

void MaskOverlay::BuildMask(const phoxo::CanvasDrawContext& target)
{
    EnsureRenderTarget();

    CSize   dcsize = phoxo::Utils::GetBitmapSize((HBITMAP)GetCurrentObject(target.dst_hdc, OBJ_BITMAP));
    if (m_buffer.Size() != dcsize)
    {
        m_buffer.Create(dcsize);
    }

    phoxo::BitmapHDC   memdc(m_buffer);
    m_target->BindDC(memdc, CRect({}, dcsize));
}

void MaskOverlay::EnsureRenderTarget()
{
    if (!m_target)
    {
        m_target = D2D::CreateDCRenderTarget(D2D1_RENDER_TARGET_TYPE_SOFTWARE);

    }
}
