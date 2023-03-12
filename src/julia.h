#pragma once

#include "renderer.h"
#include "complex.h"

class Julia
{
private:
	Complex current, next, prev, center;
	float scale = 1.0f;
	int iterations = 255;
	int hueShift = 0;

	bool changed = true;
	bool draw = true;

	int width, height;
	unsigned char* results;

public:
	Julia() = default;
	Julia(float real, float imag, int windowWidth, int windowHeight);
	~Julia();

	void MoveReal(float value);
	void MoveImag(float value);
	void MoveCenterX(float value);
	void MoveCenterY(float value);
	void Zoom(float value);
	void AddHueShift(int value);

	void Calculate();
	void Draw(const Renderer* renderer);
};