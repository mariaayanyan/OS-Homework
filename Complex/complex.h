#pragma once
#include <iostream>
struct Complex
{
	double real, img;
	Complex() = default;
	Complex(double, double); 
	double cAbs() const;
	bool operator<(const Complex&) const;
	Complex operator+(const Complex&);
	Complex operator-(const Complex&);
	Complex operator*(int);
	friend std::istream& operator>>(std::istream&, Complex&);
	friend std::ostream& operator<<(std::ostream&, const Complex&);
};
