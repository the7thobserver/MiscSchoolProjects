// Rectangle.h
//
// CompSci 141 / CSE 141 / Informatics 101 Spring 2013
// Project #4

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

struct Rectangle
{
	void** vmt;

	// Shape part
	double positionX;
	double positionY;

	// Rectangle part
	double width;
	double height;
};


void Rectangle_createVMT();

Rectangle* Rectangle_new(double positionX, double positionY, double width, double height);
void Rectangle_Rectangle(Rectangle* _this, double positionX, double positionY, double width, double height);
double Rectangle_area(Shape* _this);
double Rectangle_getWidth(Rectangle* _this);
double Rectangle_getHeight(Rectangle* _this);
void Rectangle_resize(Rectangle* _this, double width, double height);

typedef double (*fp_Rectangle_getWidth)(Rectangle*);
typedef double (*fp_Rectangle_getHeight)(Rectangle*);
typedef void (*fp_Rectangle_resize)(Rectangle*, double, double);

#endif // RECTANGLE_H
