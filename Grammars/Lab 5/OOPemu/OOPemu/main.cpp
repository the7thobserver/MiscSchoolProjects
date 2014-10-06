// main.cpp
//
// CompSci 141 / CSE 141 / Informatics 101 Spring 2013
// Project #4
//
// In this file, you'll need to do two things:
//
// (1) Finish the createVirtualMethodTables() function, making sure to
//     create VMT's for all of the "classes" you're emulating.
// (2) Add code to the main() function that creates at least one object
//     of each type and demonstrates your emulation of polymorphism by
//     calling all of the methods on it.
//
// (Note: The program will not compile until you fill in the missing parts
// of Circle.cpp.)

#include <iostream>
using namespace std;

#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "RightTriangle.h"
#include "Square.h"

void createVMTs()
{
	Shape_createVMT();
	Circle_createVMT();
	Rectangle_createVMT();
	RightTriangle_createVMT();
	Square_createVMT();
}


int main()
{
	createVMTs();

	// Here is an example of creating a Circle object and calling its
	// area() method.  Notice that we must be aware that the area()
	// method is at position 3 in the VMT.  (Of course, it must be in
	// that position in the VMT's in *all* kinds of Shapes, otherwise
	// dynamic binding will choose the wrong method and all hell will
	// very likely break loose.)
	//
	// The toughest part of the code to understand is the call to the
	// area() method...
	//
	//    ((fp_Shape_area)(s->vmt[3]))(s)
	//
	// Here's what it means...
	//
	// We start with s->vmt[3], which is a pointer to a function;
	// specifically, we know that it's a pointer to an area() function.
	// So, in order to use it that way, we need to first cast it:
	//
	//    (fp_Shape_area)(s->vmt[3])
	//
	// According to a declaration in Shape.h, here's what an fp_Shape_area
	// is...
	//
	//     typedef double (*fp_Shape_area)(Shape* s);
	//
	// That's just a fancy way of saying "fp_Shape_area is a pointer to a
	// function that takes a Shape pointer as a parameter and returns a
	// double."
	//
	// In order to call it, we simply follow it with a parameter list:
	//
	//    ((fp_Shape_area)(s->vmt[3]))(s)
    //
	// ...and we've got ourselves a call to the appropriate function.
	//
	
	Shape* s = (Shape*) Circle_new(4.0, 5.0, 3.0);
	double circleArea = ((fp_Shape_area)(s->vmt[3]))(s);
	double r = ((fp_Circle_getRadius)(s->vmt[4]))((Circle*) s);
	cout << "Area of circle w/ radius " << r << " is " << circleArea << endl;

	// Resize
	((fp_Circle_resize)(s->vmt[5]))((Circle*) s, 5.0);
	r = ((fp_Circle_getRadius)(s->vmt[4]))((Circle*) s);
	circleArea = ((fp_Shape_area)(s->vmt[3]))(s);
	cout << "Area of circle w/ radius " << r << " is " << circleArea << endl;

	// PosX, Y
	cout << s->positionX << " and " << s->positionY << " == ";
	cout << ((fp_Shape_getPositionX)(s->vmt[0]))(s) << " and " << ((fp_Shape_getPositionY)(s->vmt[1]))(s) << endl;

	// Move
	((fp_Shape_move)(s->vmt[2]))(s,0.0,1.0);
	cout << ((fp_Shape_getPositionX)(s->vmt[0]))(s) << " and " << ((fp_Shape_getPositionY)(s->vmt[1]))(s);

	cout << endl;
	
	s = (Shape*) Rectangle_new(3.0, 3.0, 3.0, 4.0);
	double rArea = ((fp_Shape_area)(s->vmt[3]))(s);
	double w = ((fp_Rectangle_getWidth)(s->vmt[4]))((Rectangle*) s);
	double h = ((fp_Rectangle_getWidth)(s->vmt[5]))((Rectangle*) s);
	cout << "Area of rectangle w/ width, height " << w << " and " << h << " is " << rArea << endl;

	((fp_Rectangle_resize)(s->vmt[6]))((Rectangle*) s, 6.0, 7.0);
	rArea = ((fp_Shape_area)(s->vmt[3]))(s);
	w = ((fp_Rectangle_getWidth)(s->vmt[4]))((Rectangle*) s);
	h = ((fp_Rectangle_getWidth)(s->vmt[5]))((Rectangle*) s);
	cout << "Area of rectangle w/ width, height " << w << " and " << h << " is " << rArea << endl;
	
	// PosX, Y
	cout << s->positionX << " and " << s->positionY << " == ";
	cout << ((fp_Shape_getPositionX)(s->vmt[0]))(s) << " and " << ((fp_Shape_getPositionY)(s->vmt[1]))(s) << endl;

	// Move
	((fp_Shape_move)(s->vmt[2]))(s,4.0,5.0);
	cout << ((fp_Shape_getPositionX)(s->vmt[0]))(s) << " and " << ((fp_Shape_getPositionY)(s->vmt[1]))(s);

	cout << endl;
	
	s = (Shape*) RightTriangle_new(1.0, 2.0, 4.0, 6.0);
	double sArea = ((fp_Shape_area)(s->vmt[3]))(s);
	h = ((fp_RightTriangle_getHeight)(s->vmt[4]))((RightTriangle*) s);
	w = ((fp_RightTriangle_getWidth)(s->vmt[5]))((RightTriangle*) s);
	sArea = ((fp_Shape_area)(s->vmt[3]))(s);
	cout << "Area of right triangle w/ width, height " << w << " and " << h << " is " << sArea << endl;

	double hyp = ((fp_RightTriangle_getHypotenuseLength)(s->vmt[6]))((RightTriangle*) s);
	cout << "Hypotenuse is " << hyp << endl;

	((fp_RightTriangle_resize)(s->vmt[7]))((RightTriangle*) s, 6.0, 7.0);
	h = ((fp_RightTriangle_getHeight)(s->vmt[5]))((RightTriangle*) s);
	w = ((fp_RightTriangle_getWidth)(s->vmt[4]))((RightTriangle*) s);
	sArea = ((fp_Shape_area)(s->vmt[3]))(s);
	cout << "Area of right triangle w/ width, height " << w << " and " << h << " is " << sArea << endl;

	// PosX, Y
	cout << s->positionX << " and " << s->positionY << " == ";
	cout << ((fp_Shape_getPositionX)(s->vmt[0]))(s) << " and " << ((fp_Shape_getPositionY)(s->vmt[1]))(s) << endl;

	// Move
	((fp_Shape_move)(s->vmt[2]))(s,-1.0,-3.0);
	cout << ((fp_Shape_getPositionX)(s->vmt[0]))(s) << " and " << ((fp_Shape_getPositionY)(s->vmt[1]))(s);

	cout << endl;
	
	 s = (Shape*) Square_new(5.0, 5.0, 4.0);
	double sqArea = ((fp_Shape_area)(s->vmt[3]))(s);
	double side = ((fp_Square_getSideLength)(s->vmt[7]))((Square*)s);
	cout << "Area of square w/ side " << side << " is " << sqArea << endl;

	((fp_Square_resize)(s->vmt[8]))((Square*) s, 5.4);
	side = ((fp_Square_getSideLength)(s->vmt[7]))((Square*)s);
	sqArea = ((fp_Shape_area)(s->vmt[3]))(s);
	cout << "Area of square w/ side " << side << " is " << sqArea << endl;

	w = ((fp_Rectangle_getWidth)(s->vmt[4]))((Rectangle*)s);
	h = ((fp_Rectangle_getHeight)(s->vmt[5]))((Rectangle*)s);
	
	cout << "W/H = " << w << " and " << h << endl;

	// PosX, Y
	cout << s->positionX << " and " << s->positionY << " == ";
	cout << ((fp_Shape_getPositionX)(s->vmt[0]))(s) << " and " << ((fp_Shape_getPositionY)(s->vmt[1]))(s) << endl;

	// Move
	((fp_Shape_move)(s->vmt[2]))(s,15.0,16.0);
	cout << ((fp_Shape_getPositionX)(s->vmt[0]))(s) << " and " << ((fp_Shape_getPositionY)(s->vmt[1]))(s);

	int temp;
	cin >> temp;

	return 0;
}
