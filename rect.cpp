#include "rect.h"
#include <cmath>


template<class T>
Rect<T>::Rect(vector<Point<T>> limits, bool is_point)
{
	rect_limits = limits;
	rect_is_point = is_point;
}

template<class T>
Rect<T>::Rect(Point<T> p1, Point<T> p2)
{
	for (int i = 0; i < p1.p_coords.size(); i++)
	{
		if (p1.p_coords[i] > p2.p_coords[i])
			rect_limits.push_back(Point<T>(p1.p_coords[i], p2.p_coords[i]));
		else
			rect_limits.push_back(Point<T>(p2.p_coords[i], p1.p_coords[i]));
	}
}

template<class T>
Rect<T>::Rect(Point<T> x)
{
	for (int i = 0; i < x.p_coords.size(); i++)
	{
		rect_limits.push_back(Point<T>(x.p_coords[i], x.p_coords[i]));
	}
}


template<class T>
bool Rect<T>::inside(Point<T> x)
{
	for (int i = 0; i < this->rect_limits.size(); i++)
	{
		if (x.p_coords[i] > this->rect_limits[i].p_coords[0] or x.p_coords[i] < this->rect_limits[i].p_coords[1])
			return false;
	}
	return true;
}

template<class T>
bool Rect<T>::inside(Rect<T> x)
{
	for (int i = 0; i < this->rect_limits.size(); i++)
	{
		if (x.rect_limits[i].p_coords[0] > this->rect_limits[i].p_coords[0] or x.rect_limits[i].p_coords[0] < this->rect_limits[i].p_coords[1]
			or x.rect_limits[i].p_coords[1] > this->rect_limits[i].p_coords[0] or x.rect_limits[i].p_coords[1] < this->rect_limits[i].p_coords[1])
			return false;
	}
	return true;
}


template<class T>
double Rect<T>::calc_enlargement(Point<T> x, Rect<T> &rect_act)
{
	if (inside(x)) return 0;
	double area = 1;
	rect_act = *this;
	for (int i = 0; i < rect_act.rect_limits.size(); i++)
	{
		if (x.p_coords[i] > rect_act.rect_limits[i].p_coords[0])
			rect_act.rect_limits[i].p_coords[0] = x.p_coords[i];
		else if(x.p_coords[i] < rect_act.rect_limits[i].p_coords[1])
			rect_act.rect_limits[i].p_coords[1] = x.p_coords[i];
	}
	return rect_act.calc_area() - this->calc_area();
}


template<class T>
double Rect<T>::calc_enlargement(Rect<T> x, Rect<T> &rect_act)
{
	if (inside(x)) return 0;
	double area = 1;
	rect_act = *this;
	for (int i = 0; i < rect_act.rect_limits.size(); i++)
	{
		if (x.rect_limits[i].p_coords[0] > rect_act.rect_limits[i].p_coords[0])
		{
			rect_act.rect_limits[i].p_coords[0] = x.rect_limits[i].p_coords[0];
		}
		if (x.rect_limits[i].p_coords[1] < rect_act.rect_limits[i].p_coords[1])
		{
			rect_act.rect_limits[i].p_coords[1] = x.rect_limits[i].p_coords[1];
		}
	}
	return rect_act.calc_area() - this->calc_area();
}


template<class T>
double Rect<T>::calc_area()
{
	double result;
	for (int i = 0; i < this->rect_limits.size(); i++)
	{
		result *= abs(this->rect_limits[i].p_coords[0] - this->rect_limits[i].p_coords[1]);
	}
	return result;
}
