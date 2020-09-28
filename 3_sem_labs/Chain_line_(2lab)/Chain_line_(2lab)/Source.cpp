#include "Chain_Line.h"
#include <math.h>
#include <iostream>

namespace Chain_Line {
	CH_Line::CH_Line(double ad) 
	{
		if (ad <= 0)
			throw std::exception("Invalid height");
		a = ad;
		CH_Line::p1.x = -1, CH_Line::p1.y = f(-1);
		CH_Line::p2.x = 1, CH_Line::p2.y = f(1);
	}
	CH_Line::CH_Line(const double x1, const double x2, double ad)
	{
		if (ad <= 0)
			throw std::exception("Invalid height");
		a = ad;
		CH_Line::p1.x = -x1, CH_Line::p1.y = f(x1);
		CH_Line::p2.x = x2, CH_Line::p2.y = f(x2);
		correct(CH_Line::p1, CH_Line::p2);
	}
	//Сеттеры
	//Сделаем ввод по x
	CH_Line& CH_Line::setPoints(const double x1, const double x2)
	{
		Point p1, p2;
		p1.x = -x1, p1.y = f(x1);
		p2.x = x2, p2.y = f(x2);
		correct(p1,p2);
		return *this;
	}

	void CH_Line::correct(const Point& p1, const Point& p2)
	{
		if(p1.y  <0)
			throw std::exception("Invalid coordinae y for Point \"p1\"");
		if (p2.y < 0)
			throw std::exception("Invalid coordinae y for Point \"p2\"");
		//Если координате в 1 и 2-ой четвертях, то продолжам их сравнивать, вдруг p1 справа
		if (p1.x > p2.x)
		{
			Point tmp;
			tmp = CH_Line::p1, CH_Line::p1 = p2, CH_Line::p2 = tmp;
		}
	}
	//Методы по работе с цепочкой
	double CH_Line::f(double x) const
	{
		//Y(x) = a *cosh( x/a)
		return  CH_Line::a * (exp(x / CH_Line::a) + exp(-x / CH_Line::a)) / 2;
	}
	CH_Line& CH_Line::setHeight(double a)
	{
		if (a <= 0)
			throw std::exception("Invalid height");
		CH_Line::a = a;
		CH_Line::p1.y = f(CH_Line::p1.x);
		CH_Line::p2.y = f(CH_Line::p2.x);
	}
	double CH_Line::L(double l)const
	{
		/*
		Point p;
		if ((CH_Line::p1.x == p.x) && (CH_Line::p1.y == p.y));
		*/
		return  CH_Line::a * (exp(l / 2 * CH_Line::a) - exp(-l / 2 * CH_Line::a));

	}
	double CH_Line::ch(double x) const
	{
		return (exp(x) + exp(-x)) / 2;
	}
	double CH_Line::sh(double x) const
	{
		return (exp(x) - exp(-x)) / 2;
	}
	double CH_Line::L2()const
	{
		if ((this->p1.x * this->p2.x) < 0)//По разные стороны
			return this->a * (exp(this->p1.x / CH_Line::a) - exp(-(this->p1.x) / CH_Line::a)) / 2 + this->a * (exp(this->p2.x / CH_Line::a) - exp(-(this->p2.x) / CH_Line::a)) / 2;
		else// По одну сторону
			return abs(this->a * (exp(this->p1.x / CH_Line::a) - exp(-(this->p1.x) / CH_Line::a)) / 2 - this->a * (exp(this->p2.x / CH_Line::a) - exp(-(this->p2.x) / CH_Line::a)) / 2);
	}
	double CH_Line::R(double x)const
	{
		return this->a * (pow(this->a * (exp(this->p2.x / CH_Line::a) - exp(-(this->p2.x) / CH_Line::a)) / 2, 2));
	}
	Point& CH_Line:: Center_Curvature(double x) const
	{
		Point* p;
		p = new Point;
		//Нет проверки, принадленить ли точкам кривой
		p->x = a * (ch(x / a) * sh(x / a) + log(ch(x / a) - sh(x / a)));
		p->y = 2 * a * ch(x / a);
		return *p;
	}
	double CH_Line::Integral(void)const
	{
		return a * a * (sh((p2.x) / a) - sh((p1.x) / a));// a^2(sh(x2/a)- sh(x1/a))
	}

}