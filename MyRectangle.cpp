#include "MyRectangle.h"
#include <GL/freeglut.h>

MyRectangle::MyRectangle(double width, double height, double red, double green, double blue) : Physics()
{
	width_size = width;
	height_size = height;
	SetGeometry(pos_x, pos_y,
		-width_size/2, -height_size/2,
		width_size/2, height_size/2);
	col_red = red;
	col_green = green;
	col_blue = blue;
}
MyRectangle::~MyRectangle()
{
	
}

void MyRectangle::Draw()
{
	if (show)
	{
		glPushMatrix();
		{
			glTranslated(pos_x, pos_y, 0.0);
			glRotated(rot_z, 0.0, 0.0, 1.0);

			glColor3d(col_red, col_green, col_blue);

			glBegin(GL_POLYGON);
			{
				glVertex3d(-width_size/2, height_size/2, 0);
				glVertex3d(width_size/2, height_size/2, 0);
				glVertex3d(width_size/2, -height_size/2, 0);
				glVertex3d(-width_size/2, -height_size/2, 0);
			}
			glEnd();
		}
		glPopMatrix();
	}
}