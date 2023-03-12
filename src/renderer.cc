#include "renderer.h"

Renderer::Renderer(Canvas *canvas)
{
    this->canvas = canvas;
}

Renderer::~Renderer()
{
    delete canvas;
}

void Renderer::DrawPoint(int& x, int& y, uint8_t& r, uint8_t& g, uint8_t& b) const
{
    canvas->SetPixel(x, y, r, g, b);
}
