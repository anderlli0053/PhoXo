#pragma once

class MaskOverlay
{
private:
    ID2D1DCRenderTargetPtr   m_target;

    FCImage   m_buffer;

public:
    void BuildMask(const phoxo::CanvasDrawTarget& target);

private:
    void EnsureRenderTarget();
};
