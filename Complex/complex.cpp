#include "complex.h"
#include <cmath>

#define square(x) (x)*(x)

Complex::Complex (double real, double imaginary) : mReal(real), mImaginary(imaginary)
{
	
}

double Complex::cAbs() const 
{
	return sqrt(square(mReal) + square(mImaginary));
}

bool Complex::operator<(const Complex& rhs) const 
{
	return cAbs() < rhs.cAbs();
}

Complex Complex::operator+(const Complex& rhs) const
{
	return Complex(mReal + rhs.mReal, mImaginary + rhs.mImaginary);
}

Complex Complex::operator-(const Complex& rhs) const
{
	return Complex(mReal - rhs.mReal, mImaginary - rhs.mImaginary);
}

Complex Complex::operator*(double rhs) const
{
	return Complex(mReal*rhs, mImaginary*rhs);
}

std::istream& operator>>(std::istream& in, Complex& complexNum)
{
	in >> complexNum.mReal >> complexNum.mImaginary;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Complex& complexNum)
{
	if(complexNum.mReal == 0 && complexNum.mImaginary == 0)
	{
		out << 0;
		return out;
	}

	if(complexNum.mReal) 
		out << complexNum.mReal;
	
	if (complexNum.mImaginary == 0)
		return out;

	if(complexNum.mImaginary > 0 && complexNum.mReal) 
		out << "+";
	
	//print the imaginary coefficient if it's not 1 or -1 
	if(abs(complexNum.mImaginary) != 1) 
		out << complexNum.mImaginary;
		
	if(complexNum.mImaginary == -1) 
		out << "-";

	out << "i";
	
	return out; 
}