// Circle.h
//
// CompSci 141 / CSE 141 / Informatics 101 Spring 2013
// Project #4
//
// Contains declarations that support the emulation of the Circle "class."

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"



// It's very important that Circle is laid out like this:
//
//    (1) virtual method table pointer
//    (2) the Shape fields, in the same order they're specified in the Shape
//        struct
//    (3) the Circle-specific fields
//
// If you don't lay things out this way, when you call a Shape function
// (e.g. Shape_getPositionX) on a Circle "object," you won't get back the
// right answer, since Shape_getPositionX assumes that positionX is the
// second field in any kind of Shape.

struct Circle
{
	void** vmt;

	// Shape part
	double positionX;
	double positionY;

	// Circle part
	double radius;
};


void Circle_createVMT();

Circle* Circle_new(double positionX, double positionY, double radius);
void Circle_Circle(Circle* _this, double positionX, double positionY, double radius);
double Circle_area(Shape* _this);
double Circle_getRadius(Circle* _this);
void Circle_resize(Circle* _this, double radius);

typedef double (*fp_Circle_getRadius)(Circle*);
typedef void (*fp_Circle_resize)(Circle*, double);



#endif // CIRCLE_H
