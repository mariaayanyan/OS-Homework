//This header file contains a struct defining complex numbers 
//supporting basic operations(+, -, multiply by constant, absolute value)

#pragma once
#include <iostream>
struct Complex
{
	double mReal, mImaginary;

	//defualt constructor
	Complex() = default;

	//constructs a complex number from real and imaginary parts
	Complex(double, double); 

	//returns the absolute value of the complex number
	double cAbs() const;

	//compares two complex numbers by their absolute value
	bool operator<(const Complex&) const;
	
	//adds the real and imaginary parts respectively
	Complex operator+(const Complex&) const;
	
	//subtracts the real and imaginary parts respectively
	Complex operator-(const Complex&) const;

	//multiplies the real and imaginary parts of the complex number by a constant
	Complex operator*(double) const;

	//reads the complex number, the real and imaginary parts should be given separately
	friend std::istream& operator>>(std::istream&, Complex&);
	
	//outputs the complex number in the following way: mReal + mImaginary*i 
	//example: 3 + 4i, 9 - i, 0, 2.4i, 
	friend std::ostream& operator<<(std::ostream&, const Complex&);
};