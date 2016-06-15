#pragma once
#include "Figure.h"

typedef struct Border
{
	double x_min, x_max;
	double y_min, y_max;
} Border;

class Physics : public Figure
{
public:
	Physics();
	~Physics();

	 bool Collision(const Physics& obj);
protected:
	Border borders;
	void SetGeometry(double _x, double _y, double _x_min, double _y_min, double _x_max, double _y_max);
};