#pragma once

class GripHandle
{
public:
    enum Position
    {
        TopLeft,
        Top,
        TopRight,
        Left,
        Right,
        BottomLeft,
        Bottom,
        BottomRight
    };

    Position   m_pos;
    CPoint   m_view_pos;
    FCImage   m_image;

    GripHandle(Position position) : m_pos(position)
    {
    }


    static int GripWidth()
    {
        return DPICalculator::Cast(2);
    }

//     void Draw(CDC& dc) const
//     {
//         phoxo::ImageDrawer::Draw(dc, view_pos, image);
//     }
};
