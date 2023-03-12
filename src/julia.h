#pragma once

#include "renderer.h"
#include "complex.h"

class Julia
{
private:
	Complex current, next, prev, center;
	double scale = 1.0f;
	int iterations = 255;
	int hueShift = 0;

	bool changed = true;
	bool draw = true;

	int width, height;
	unsigned char* results;

public:
	Julia() = default;
	Julia(double real, double imag, int windowWidth, int windowHeight);
	~Julia();

	void MoveReal(double value);
	void MoveImag(double value);
	void MoveCenterX(double value);
	void MoveCenterY(double value);
	void Zoom(double value);
	void AddHueShift(int value);

	void Calculate();
	void Draw(const Renderer* renderer);
};