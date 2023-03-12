#include "color_utils.h"
#include <cmath>

void ColorUtils::HSVtoRGB(uint8_t H, uint8_t S, uint8_t V, uint8_t& R, uint8_t& G, uint8_t& B)
{
    uint8_t region, remainder, p, q, t;

    if (S == 0)
    {
        R = V;
        G = V;
        B = V;
        return;
    }

    region = H / 43;
    remainder = (H - (region * 43)) * 6;

    p = (V * (255 - S)) >> 8;
    q = (V * (255 - ((S * remainder) >> 8))) >> 8;
    t = (V * (255 - ((S * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
    case 0:
        R = V; G = t; B = p;
        break;
    case 1:
        R = q; G = V; B = p;
        break;
    case 2:
        R = p; G = V; B = t;
        break;
    case 3:
        R = p; G = q; B = V;
        break;
    case 4:
        R = t; G = p; B = V;
        break;
    default:
        R = V; G = p; B = q;
        break;
    }
}