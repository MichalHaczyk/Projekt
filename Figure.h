#pragma once

class Figure
{
public:
	Figure(double red, double green, double blue);
	~Figure();

	double GetPositionX();
	double GetPositionY();
	void Move(double dx, double dy);
	void SetPosition(double x, double y);

	virtual void Draw() = 0;

protected:
	double pos_x, pos_y;
	double rot_z;
	double col_red, col_green, col_blue;
	bool show;
};