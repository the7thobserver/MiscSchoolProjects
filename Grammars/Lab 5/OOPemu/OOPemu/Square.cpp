// Square.cpp
//
// CompSci 141 / CSE 141 / Informatics 101 Spring 2013
// Project #4

#include "Square.h"
#include <iostream>

void** vmtSquare;

Square* Square_new(double positionX, double positionY, double sideLength)
{
	Square* sq = new Square;
	Square_Square(sq, positionX, positionY, sideLength);
	sq->vmt = vmtSquare;

	return sq;
}

void Square_Square(Square* _this, double positionX, double positionY, double sideLength)
{
	_this->positionX = positionX;
	_this->positionY = positionY;
	_this->sideLength = sideLength;
	_this->height = sideLength;
	_this->width = sideLength;
}

double Square_area(Shape* _this)
{
	double sideLength = ((fp_Square_getSideLength)(_this->vmt[7]))((Square*) _this);

	return sideLength * sideLength;
}

double Square_getSideLength(Square* _this)
{
	std::cout << "sq sidelength"<< std::endl;
	return _this->sideLength;
}

void Square_resize(Square* _this, double sideLength)
{
	std::cout << "sq resize"<< std::endl;
	_this->sideLength = sideLength;
	((fp_Rectangle_resize)(_this->vmt[6]))((Rectangle*)_this, sideLength, sideLength);
}

void Square_createVMT()
{
	vmtSquare = new void*[9];
	vmtSquare[0] = (void*) Shape_getPositionX;
	vmtSquare[1] = (void*) Shape_getPositionY;
	vmtSquare[2] = (void*) Shape_move;
	vmtSquare[3] = (void*) Square_area;
	vmtSquare[4] = (void*) Rectangle_getWidth;
	vmtSquare[5] = (void*) Rectangle_getHeight;
	vmtSquare[6] = (void*) Rectangle_resize;
	vmtSquare[7] = (void*) Square_getSideLength;
	vmtSquare[8] = (void*) Square_resize;
}