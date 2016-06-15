#include "Figure.h"

Figure::Figure(double red, double green, double blue)
{
	pos_x = 0.0;
	pos_y = 0.0;
	rot_z = 0.0;
	col_red = red;
	col_green = green;
	col_blue = blue;
	show = true;
}

Figure::~Figure()
{
	
}

double Figure::GetPositionX()
{
	return pos_x;
}

double Figure::GetPositionY()
{
	return pos_y;
}

void Figure::Move(double dx, double dy)
{
	pos_x += dx;
	pos_y += dy;
}

void Figure::SetPosition(double x, double y)
{
	pos_x = x;
	pos_y = y;
}


