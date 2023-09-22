#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <math.h>
class Complex {
public:
    double real;
    double imag;

    Complex();
    Complex(double real_, double imag_);

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(double scalar) const;
    double abs() const;
};

#endif
