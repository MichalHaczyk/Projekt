#include "Physics.h"

Physics::Physics() : Figure(0.5, 0.5, 0.5)
{
	
}

Physics::~Physics()
{
	
}

void Physics::SetGeometry(double _x, double _y, double _x_min, double _y_min, double _x_max, double _y_max)
{
	pos_x = _x;
	pos_y = _y;
	borders.x_min = _x_min;
	borders.x_max = _x_max;
	borders.y_min = _y_min;
	borders.y_max = _y_max;
}

bool Physics::Collision(const Physics& obj)
{
	bool collision = false;

	double thisTopBorder = pos_y + borders.y_max;
	double thisBottomBorder = pos_y + borders.y_min;
	double thisLeftBorder = pos_x + borders.x_min;
	double thisRightBorder = pos_x + borders.x_max;

	double objTopBorder = obj.pos_y + obj.borders.y_max;
	double objBottomBorder = obj.pos_y + obj.borders.y_min;
	double objLeftBorder = obj.pos_x + obj.borders.x_min;
	double objRightBorder = obj.pos_x + obj.borders.x_max;

	// top wall
	if (thisTopBorder >= objBottomBorder && thisTopBorder <= objTopBorder &&
		((thisLeftBorder >= objLeftBorder && thisLeftBorder <= objRightBorder) || (thisRightBorder >= objLeftBorder && thisRightBorder <= objRightBorder) ||
			(thisLeftBorder <= objLeftBorder && thisRightBorder >= objRightBorder))) collision = true;
		
	// bottom wall
	if (thisBottomBorder >= objBottomBorder && thisBottomBorder <= objTopBorder && 
		((thisLeftBorder >= objLeftBorder && thisLeftBorder <= objRightBorder) || (thisRightBorder >= objLeftBorder && thisRightBorder <= objRightBorder) ||
			(thisLeftBorder <= objLeftBorder && thisRightBorder >= objRightBorder))) collision = true;

	// left wall
	if (thisLeftBorder >= objLeftBorder && thisLeftBorder <= objRightBorder &&
		((thisBottomBorder >= objBottomBorder && thisBottomBorder <= objTopBorder) || (thisTopBorder >= objBottomBorder && thisTopBorder <= objTopBorder) ||
			(thisBottomBorder <= objBottomBorder && thisTopBorder >= objTopBorder))) collision = true;

	// right wall
	if (thisRightBorder >= objLeftBorder && thisRightBorder <= objRightBorder &&
		((thisBottomBorder >= objBottomBorder && thisBottomBorder <= objTopBorder) || (thisTopBorder >= objBottomBorder && thisTopBorder <= objTopBorder) ||
			(thisBottomBorder <= objBottomBorder && thisTopBorder >= objTopBorder))) collision = true;


	// inverse checking (if obj is smaller than this)
	// obj top wall
	if (objTopBorder >= thisBottomBorder && objTopBorder <= thisTopBorder &&
		((objLeftBorder >= thisLeftBorder && objLeftBorder <= thisRightBorder) || (objRightBorder >= thisLeftBorder && objRightBorder <= thisRightBorder) ||
			(objLeftBorder <= thisLeftBorder && objRightBorder >= thisRightBorder))) collision = true;

	// obj bottom wall
	if (objBottomBorder >= thisBottomBorder && objBottomBorder <= thisTopBorder &&
		((objLeftBorder >= thisLeftBorder && objLeftBorder <= thisRightBorder) || (objRightBorder >= thisLeftBorder && objRightBorder <= thisRightBorder) ||
			(objLeftBorder <= thisLeftBorder && objRightBorder >= thisRightBorder))) collision = true;

	// obj left wall
	if (objLeftBorder >= thisLeftBorder && objLeftBorder <= thisRightBorder &&
		((objBottomBorder >= thisBottomBorder && objBottomBorder <= thisTopBorder) || (objTopBorder >= thisBottomBorder && objTopBorder <= thisTopBorder) ||
			(objBottomBorder <= thisBottomBorder && objTopBorder >= thisTopBorder))) collision = true;

	// obj right wall
	if (objRightBorder >= thisLeftBorder && objRightBorder <= thisRightBorder &&
		((objBottomBorder >= thisBottomBorder && objBottomBorder <= thisTopBorder) || (objTopBorder >= thisBottomBorder && objTopBorder <= thisTopBorder) ||
			(objBottomBorder <= thisBottomBorder && objTopBorder >= thisTopBorder))) collision = true;

	return collision;
}
