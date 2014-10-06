// RightTriangle.h
//
// CompSci 141 / CSE 141 / Informatics 101 Spring 2013
// Project #4

#ifndef RIGHTTRIANGLE_H
#define RIGHTTRIANGLE_H

#include "Shape.h"

struct RightTriangle
{
	void** vmt;

	// Shape part
	double positionX;
	double positionY;

	// Right triangle part
	double width;
	double height;
};


void RightTriangle_createVMT();

RightTriangle* RightTriangle_new(double positionX, double positionY, double width, double height);
void RightTriangle_RightTriangle(RightTriangle* _this, double positionX, double positionY, double width, double height);
double RightTriangle_area(Shape* _this);
double RightTriangle_getWidth(RightTriangle* _this);
double RightTriangle_getHeight(RightTriangle* _this);
double RightTriangle_getHypotenuseLength(RightTriangle* _this);
void RightTriangle_resize(RightTriangle* _this, double width, double height);

typedef double (*fp_RightTriangle_getWidth)(RightTriangle*);
typedef double (*fp_RightTriangle_getHeight)(RightTriangle*);
typedef double (*fp_RightTriangle_getHypotenuseLength)(RightTriangle*);
typedef void (*fp_RightTriangle_resize)(RightTriangle*, double, double);

#endif // RIGHTTRIANGLE_H
