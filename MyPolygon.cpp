#include "MyPolygon.h"
#include <GL/freeglut.h>

MyPolygon::MyPolygon(double red, double green, double blue):Physics()
{
	SetGeometry(pos_x, pos_y,
		-4 / 2, -3 / 2,
		4 / 2, 3 / 2);
	col_red=red;
	col_green=green;
	col_blue=blue;
}
MyPolygon:: ~ MyPolygon()
{
	
}

void MyPolygon::Draw()
{
	GLdouble x0=0.0;
	GLdouble x1=1.0;
	GLdouble x2=2.0;
	GLdouble y0=0.0;
	GLdouble y1=1.0;
	GLdouble y2=1.5;
	if (show)
	{
		glPushMatrix();
		{
			glTranslated(pos_x, pos_y, 0.0);
			glRotated(rot_z, 0.0, 0.0, 1.0);

			glColor3d(col_red, col_green, col_blue);

			glBegin(GL_POLYGON);
			{
				glVertex3d(-x1, y1, 0);
				glVertex3d(x0, y2, 0);
				glVertex3d(x1, y1, 0);
				glVertex3d(x2, -y1, 0);
				glVertex3d(x2, -y1, 0);
				glVertex3d(x0, y0, 0);
				glVertex3d(-x2, -y1, 0);
				glVertex3d(-x2, -y1, 0);


			}
			glEnd();
		}
		glPopMatrix();
	}
}