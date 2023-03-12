#include "julia.h"
#include "color_utils.h"
#include <cmath>
#include <iostream>

Julia::Julia(double real, double imag, int width, int height) {
    current.real = real;
    current.imag = imag;

    this->width = width;
    this->height = height;

    results = new unsigned char[width * height];
}

void Julia::MoveReal(double value)       { this->current.real += value;                      changed = true; }
void Julia::MoveImag(double value)       { this->current.imag += value;                      changed = true; }
void Julia::MoveCenterX(double value)    { this->center.real += value * 1.0 / this->scale;   changed = true; }
void Julia::MoveCenterY(double value)    { this->center.imag += value * 1.0 / this->scale;   changed = true; }
void Julia::Zoom(double value)           { this->scale += value;                             changed = true; }
void Julia::AddHueShift(int value)       { this->hueShift += value;                          changed = true; }

void Julia::Calculate()
{
    if(!changed)
        return;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++)
        {

            next.real = 1.5 * (x - width / 2.0) / (0.5 * scale * width) + center.real;
            next.imag = (y - height / 2.0) / (0.5 * scale * height) + center.imag;

            int i;
            for (i = 0; i < iterations; i++)
            {
                prev.real = next.real;
                prev.imag = next.imag;

                next.real = prev.real * prev.real - prev.imag * prev.imag + current.real;
                next.imag = 2.0 * prev.real * prev.imag + current.imag;

                if ((next.real * next.real + next.imag * next.imag) > 4.0) break;
            }

            results[x + width * y] = i;
        }
    }

    changed = false;
    draw = true;
}

void Julia::Draw(const Renderer* renderer) {
    if(!draw)
        return;

    for (int i = 0; i < height * width; i++) {
        int x = i % width;
        int y = i / width;

        unsigned char z = results[x + width * y];
        results[x + width * y] = 0;

        uint8_t r, g, b;
        ColorUtils::HSVtoRGB(z % 255 + hueShift, 255, 255 * (z < iterations), r, g, b);

        renderer->DrawPoint(x, y, r, g, b);
    }

    draw = false;
}

Julia::~Julia()
{
    delete results;
}