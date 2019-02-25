#include <iostream>

#ifndef COMPLEX_H
#define COMPLEX_H
class Complex
{
  private:
    double real;
    double imaginary;
  public:
    Complex();
    Complex(double real, double imaginary);
    double getReal();
    double getImaginary();
    void setReal(double newReal);
    void setImaginary(double newImaginary);
    bool equal(const Complex &rhs) const;
    Complex add(const Complex &rhs) const;
    Complex multiply(const Complex &rhs) const;
    Complex square() const;
    void output(std::ostream &out) const;
};
#endif
