#include "complex.h"
#include <cmath>
#define sq(x) (x)*(x)

Complex::Complex (double r, double i) : real(r), img(i)
{
	
}

double Complex::cAbs() const 
{
	return sqrt(sq(real) + sq(img));
}

bool Complex::operator<(const Complex& c) const 
{
	return cAbs() < c.cAbs();
}

Complex Complex::operator+(const Complex& a)
{
	return Complex(real + a.real, img + a.img);
}

Complex Complex::operator-(const Complex& a)
{
	return Complex(real - a.real, img - a.img);
}

Complex Complex::operator*(int num)
{
	return Complex(real*num, img*num);
}

std::istream& operator>>(std::istream& in, Complex& c)
{
	in >> c.real >> c.img;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Complex& c)
{
	if(!c.real && !c.img)
	{
		out << 0;
		return out;
	}	 

	if(c.real) out << c.real;
	if(c.img > 0 && c.real) out << "+";
	if(c.img)
	{
		
		if(c.img != 1 && c.img != -1) out << c.img;
		if(c.img == -1) out << "-";
		out << "i";
	}
	return out; 
}
