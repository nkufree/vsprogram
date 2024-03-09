#include <iostream>
using namespace std;

class Shape
{
public:
	Shape() {}
	virtual double getArea() { 
		cout << "zhixin";
		return 0;};
};

class Circle :public Shape
{
	double radius;
public:
	Circle(double r):radius(r){}
	double getArea()
	{
		return 3.14 * radius * radius;
	}
};

class Square :public Shape
{
	double width;
public:
	Square(double w):width(w){}
	double getArea()
	{
		return width * width;
	}
};

class Rectangle :public Shape
{
	double width;
	double height;
public:
	Rectangle(double w,double h):width(w),height(h){}
	double getArea()
	{
		return width * height;
	}
};

class Trapezoid :public Shape
{
	double line1;
	double line2;
	double height;
public:
	Trapezoid(double l1, double l2, double h) :line1(l1), line2(l2), height(h){}
	double getArea()
	{
		return (line1 + line2) * height / 2;
	}
};

class Triangle :public Shape
{
	double line;
	double height;
public:
	Triangle(double l, double h):line(l),height(h){}
	double getArea()
	{
		return line * height / 2;
	}
};

int main()
{
	Shape* p[5];
	Circle circle(12.6);
	circle.getArea();
	Square square(3.5);
	Rectangle rectangle(4.5, 8.4);
	Trapezoid trapezoid(2.0, 4.5, 3.2);
	Triangle triangle(4.5, 8.4);
	p[0] = &circle;
	p[1] = &square;
	p[2] = &rectangle;
	p[3] = &trapezoid;
	p[4] = &triangle;
	double sum = 0;
	for (int i = 0; i < 5; i++)
	{
		cout << p[i]->getArea() << endl;
		sum += p[i]->getArea();
	}
	cout << sum << endl;
	return 0;
}