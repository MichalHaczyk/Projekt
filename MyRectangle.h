#pragma once
#include "Physics.h"

class MyRectangle : public Physics
{
public:
	MyRectangle(double width, double height, double red, double green, double blue);
	~MyRectangle();

	void Draw();

private:
	double width_size;
	double height_size;

};