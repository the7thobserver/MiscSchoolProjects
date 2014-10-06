// Square.h
//
// CompSci 141 / CSE 141 / Informatics 101 Spring 2013
// Project #4

#ifndef SQUARE_H
#define SQUARE_H

#include "Rectangle.h"

struct Square
{
	void** vmt;

	// Shape part
	double positionX;
	double positionY;

	// Square part
	double sideLength;
	
	// Rectangle parts
	double width;
	double height;
};


void Square_createVMT();

Square* Square_new(double positionX, double positionY, double sideLength);
void Square_Square(Square* _this, double positionX, double positionY, double sideLength);
double Square_area(Shape* _this);
double Square_getSideLength(Square* _this);
void Square_resize(Square* _this, double sideLength);

typedef double (*fp_Square_getSideLength)(Square*);
typedef void (*fp_Square_resize)(Square*, double);

#endif // SQUARE_H
