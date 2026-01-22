#pragma once

namespace crop
{
    struct CropAspectRatio
    {
        // 宽高比（例如 16:9 或 4:3, 1:1），默认0表示没有锁定比例
        double   m_width = 0;
        double   m_height = 0;

        bool IsLocked() const
        {
            return m_width > 0 && m_height > 0;
        }

        double Value() const
        {
            return IsLocked() ? (m_width / m_height) : 0;
        }

        void Unlock()
        {
            m_width = m_height = 0;
        }

        void Lock(int width, int height)
        {
            m_width = width;
            m_height = height;
            assert(IsLocked());
        }

        // 目标：返回一个矩形尺寸，使其至少覆盖 canvas（>= canvas），并且保持比例。
        CRect FitCanvas(CSize canvas_size) const
        {
            if (!IsLocked())
                return {};

            double   t = (std::max)(canvas_size.cx / m_width, canvas_size.cy / m_height);

            // t * m_width >= canvas_width
            // t * m_height >= canvas_height
            CSize   objsize{ (int)ceil(t * m_width), (int)ceil(t * m_height) };
            return phoxo::Utils::CalculateFitWindow(objsize, CRect({}, canvas_size));
        }
    };
}
