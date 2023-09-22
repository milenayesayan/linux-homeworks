#include "complex.h"
#include <cmath>
#include <iostream>

  Complex::Complex() : real(0.0), imag(0.0) {}
  Complex::Complex(double real_, double imag_) : real(real_), imag(imag_) {}

  Complex Complex:: operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
  }

  Complex Complex::  operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
  }

  Complex Complex:: operator*(double scalar) const {
    return Complex(real * scalar, imag * scalar);
  }

  double Complex:: abs() const { // Removed the parameter
    return std::sqrt(real * real + imag * imag);
  }
