// RightTriangle.cpp
//
// CompSci 141 / CSE 141 / Informatics 101 Spring 2013
// Project #4

#include <cmath>
#include "RightTriangle.h"

void** vmtRightTriangle;

RightTriangle* RightTriangle_new(double positionX, double positionY, double width, double height)
{
	RightTriangle* rt = new RightTriangle;
	RightTriangle_RightTriangle(rt, positionX, positionY, width, height);
	rt->vmt = vmtRightTriangle;

	return rt;
}

void RightTriangle_RightTriangle(RightTriangle* _this, double positionX, double positionY, double width, double height)
{
	_this->height = height;
	_this->width = width;
	_this->positionX = positionX;
	_this->positionY = positionY;
}

double RightTriangle_area(Shape* _this)
{
	double width = ((fp_RightTriangle_getWidth)(_this->vmt[4]))((RightTriangle*)_this);
	double height = ((fp_RightTriangle_getHeight)(_this->vmt[5]))((RightTriangle*)_this);

	return width * height / 2;
}

double RightTriangle_getWidth(RightTriangle* _this)
{
	return _this->width;
}

double RightTriangle_getHeight(RightTriangle* _this)
{
	return _this->height;
}

double RightTriangle_getHypotenuseLength(RightTriangle* _this)
{
	double width = ((fp_RightTriangle_getWidth)(_this->vmt[4]))((RightTriangle*)_this);
	double height = ((fp_RightTriangle_getHeight)(_this->vmt[5]))((RightTriangle*)_this);

	return sqrt(width * width + height * height);
}

void RightTriangle_resize(RightTriangle* _this, double width, double height)
{
	_this->height = height;
	_this->width = width;
}

void RightTriangle_createVMT()
{
	vmtRightTriangle = new void*[8];
	vmtRightTriangle[0] = (void*) Shape_getPositionX;
	vmtRightTriangle[1] = (void*) Shape_getPositionY;
	vmtRightTriangle[2] = (void*) Shape_move;
	vmtRightTriangle[3] = (void*) RightTriangle_area;
	vmtRightTriangle[4] = (void*) RightTriangle_getWidth;
	vmtRightTriangle[5] = (void*) RightTriangle_getHeight;
	vmtRightTriangle[6] = (void*) RightTriangle_getHypotenuseLength;
	vmtRightTriangle[7] = (void*) RightTriangle_resize;
}