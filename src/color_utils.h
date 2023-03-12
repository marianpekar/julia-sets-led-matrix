#pragma once

#include <iostream>

class ColorUtils
{
public:
	static void HSVtoRGB(uint8_t H, uint8_t S, uint8_t V, uint8_t& R, uint8_t& G, uint8_t& B);
};