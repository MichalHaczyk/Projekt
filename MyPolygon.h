#include "Physics.h"

class MyPolygon:public Physics
{
public:
	MyPolygon(double red, double green, double blue);
	~ MyPolygon();

	void Draw();
};

