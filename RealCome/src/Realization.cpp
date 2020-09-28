//
// Created by DenGer on 22.09.2020.
//

#include "Chain.h"
#include <math.h>
#include <iostream>

namespace Chain_Line {
    CH_Line::CH_Line(double ad)
    {
        if (ad <= 0)
            std::cerr << ("Invalid height");
        a = ad;
        CH_Line::p1.x = -1, CH_Line::p1.y = f(-1);
        CH_Line::p2.x = 1, CH_Line::p2.y = f(1);
    }
    CH_Line::CH_Line(const double x1, const double x2, double ad)
    {
        if (ad <= 0)
            std::cerr << ("Invalid height");
        a = ad;
        CH_Line::p1.x = -x1, CH_Line::p1.y = f(x1);
        CH_Line::p2.x = x2, CH_Line::p2.y = f(x2);
        correct(CH_Line::p1, CH_Line::p2);
    }
//Русский
    CH_Line& CH_Line::setPoints(const double x1, const double x2)
    {
        Point p1, p2;
        p1.x = -x1, p1.y = f(x1);
        p2.x = x2, p2.y = f(x2);
        correct(p1,p2);
    }

    void CH_Line::correct(const Point& p1, const Point& p2)
    {
        if(p1.y  <0)
            std::cerr << "Invalid coordinae y for Point \"p1\"";
        if (p2.y < 0)
            std::cerr << "Invalid coordinae y for Point \"p2\"";
        //���� ���������� � 1 � 2-�� ���������, �� ��������� �� ����������, ����� p1 ������
        if (p1.x > p2.x)
        {
            Point tmp;
            tmp = CH_Line::p1, CH_Line::p1 = p2, CH_Line::p2 = tmp;
        }
    }
    //������ �� ������ � ��������
    double CH_Line::f(double x) const
    {
        //Y(x) = a *cosh( x/a)
        return  CH_Line::a * (exp(x / CH_Line::a) + exp(-x / CH_Line::a)) / 2;
    }
    CH_Line& CH_Line::setHeight(double a)
    {
        if (a <= 0)
            std::cerr << ("Invalid height");
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
    double CH_Line::L2()const
    {
        if ((this->p1.x * this->p2.x) < 0)//�� ������ �������
            return this->a * (exp(this->p1.x / CH_Line::a) - exp(-(this->p1.x) / CH_Line::a)) / 2 + this->a * (exp(this->p2.x / CH_Line::a) - exp(-(this->p2.x) / CH_Line::a)) / 2;
        else// �� ���� �������
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
        p->x = this->a * ();
    }
}