#pragma once

#include <iostream>

#include "led-matrix.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

class Renderer {

private:
    Canvas* canvas;
public:
	Renderer(Canvas* canvas);
	~Renderer();

	void DrawPoint(int x, int y, uint8_t r, uint8_t g, uint8_t b) const;
};