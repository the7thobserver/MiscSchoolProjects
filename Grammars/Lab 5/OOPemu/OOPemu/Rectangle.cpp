// Rectangle.cpp
//
// CompSci 141 / CSE 141 / Informatics 101 Spring 2013
// Project #4

#include "Rectangle.h"
#include <iostream>

void** vmtRectangle;

Rectangle* Rectangle_new(double positionX, double positionY, double width, double height)
{
	Rectangle* r = new Rectangle;
	Rectangle_Rectangle(r, positionX, positionY, width, height);
	r->vmt = vmtRectangle;
	return r;
}

void Rectangle_Rectangle(Rectangle* _this, double positionX, double positionY, double width, double height)
{
	_this->positionX = positionX;
	_this->positionY = positionY;
	_this->width = width;
	_this->height = height;
}

double Rectangle_area(Shape* _this)
{
	double width = ((fp_Rectangle_getWidth)(_this->vmt[4]))((Rectangle*)_this);
	double height = ((fp_Rectangle_getHeight)(_this->vmt[5]))((Rectangle*)_this);

	return width * height;
}

double Rectangle_getWidth(Rectangle* _this)
{
	std::cout << "rect WIDTH"<< std::endl;
	return _this->width;
}

double Rectangle_getHeight(Rectangle* _this)
{
	std::cout << "rect HEIGHT"<< std::endl;
	return _this->height;
}

void Rectangle_resize(Rectangle* _this, double width, double height)
{
	std::cout << "rect RESIZE"<< std::endl;
	_this->width = width;
	_this->height = height;
}

void Rectangle_createVMT()
{
	vmtRectangle = new void*[7];
	vmtRectangle[0] = (void*) Shape_getPositionX;
	vmtRectangle[1] = (void*) Shape_getPositionY;
	vmtRectangle[2] = (void*) Shape_move;
	vmtRectangle[3] = (void*) Rectangle_area;
	vmtRectangle[4] = (void*) Rectangle_getWidth;
	vmtRectangle[5] = (void*) Rectangle_getHeight;
	vmtRectangle[6] = (void*) Rectangle_resize;
}