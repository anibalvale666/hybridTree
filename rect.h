#ifndef RECT_H
#define RECT_H
#include <vector>
#include "point.h"
#include "point.cpp"

using namespace std;
//clase rectangulo formado por vectores (puntos de dos dimensiones) donde el punto inicial del vector es el max y el final el min en los ejes

template<class T>
class Rect
{
public:

	//compuesto por puntos que representan las lineas de un rectangulo el 0 es el maximo el 1 el minimo
	vector<Point<T>> rect_limits; 
	bool rect_is_point;

	Rect(vector<Point<T>>, bool);
	Rect(Point<T>, Point<T>);
	Rect(Point<T>);
	Rect();

	bool inside(Point<T>);
	bool inside(Rect<T>);

	double calc_enlargement(Point<T>, Rect<T> &);
	double calc_enlargement(Rect<T>, Rect<T> &);

	double calc_area();
};

#endif

