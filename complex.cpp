#include "complex.hpp"
//Default constructor
Complex::Complex()
{
  real = 1;
  imaginary = 1;
}
//Parameterized Constructor: no constraints
Complex::Complex(double real, double imaginary)
{
  this->real = real;
  this->imaginary = imaginary;
}
//Getters and setters: There are no real constraints on any of these so they are very simple methods
double Complex::getReal()
{
  return this->real;
}
double Complex::getImaginary()
{
  return this->imaginary;
}
void Complex::setReal(double newReal)
{
  real = newReal;
}
void Complex::setImaginary(double newImaginary)
{
  imaginary = newImaginary;
}
//Mathematical Operations
bool Complex::equal(const Complex &rhs) const
{
  if (real == rhs.real && imaginary == rhs.imaginary) //Makes sure each part (real and imaginary are equal)
  {
    return true;
  }
  return false;
}
Complex Complex::add(const Complex &rhs) const
{
  //Adds real and imaginary parts and puts them in a new complex
  Complex c;
  c.setReal(real + rhs.real);
  c.setImaginary(imaginary + rhs.imaginary);
  return c;
}
Complex Complex::multiply(const Complex &rhs) const
{
  //Conducts foil to multiply the imaginary. Subtracting imaginary*rhs.imaginary because i^2 = -1
  Complex c;
  c.setReal(real*rhs.real - imaginary*rhs.imaginary);
  c.setImaginary(real*rhs.imaginary + imaginary*rhs.real);
  return c;
}
Complex Complex::square() const
{
  //Squares the complex, similar to multiply
  Complex c;
  c.setReal(real*real - imaginary*imaginary);
  c.setImaginary(2*real*imaginary);
  return c;
}
//Outputs complex in the form "a + bi"
void Complex::output(std::ostream &out) const
{
  out << real << " + " << imaginary << 'i' << '\n';
}
