#include <iostream>
#include <math.h>

#include "lodepng.h"
#include "mandelbrot.hpp"

#define PI 3.14159265

//Default constructor: Initializes variables to prescribed guidelines, and initializes img and c to arrays of size width*height because they hold a value for
//each pixel
Mandelbrot::Mandelbrot() : iterations (100), width (1020), height (680)
{
  realMin = -2;
  realMax = 1;
  complexMin = -1;
  complexMax = 1;
  img = new uint32_t [width*height];
  c = new Complex[width*height];
}
//Parameterized constructor: Takes a value for width and height and checks if the size of the image area is less than 4 (less than 2 by 2), if it is
//the constructor sets the image size to default values and initalizes the rest of the private fields to the prescribed guidelines
Mandelbrot::Mandelbrot(uint16_t w, uint16_t h) : iterations (100), width ((w >= 2) ? (w) : (2)), height((h >= 2) ? (h) : 2)
{
  realMin = -2;
  realMax = 1;
  complexMin = -1;
  complexMax = 1;
  img = new uint32_t [width*height];
  c = new Complex [width*height];
}
//Destructor: Deletes the pointers used throughout the class. zn is deleted in the map coordinates function so not necessary to remove that variable
Mandelbrot::~Mandelbrot()
{
  delete [] img;
  delete [] c;
  img = nullptr;
  c = nullptr;
}
//mapCoordinates: Maps each pixel in the image to complex coordinates. It finds the change in real and complex for each point,
//as well as creates variables for currentReal and currentImaginary (which can be thought of x and y respectively)
//It then starts in the top right corner of the real-imaginary plane and moves down, row by row, to the bottom left corner,
//finding the real and complex parts of each point changing the currentReal and currentImaginary by changing dReal and dImaginary
//values by a factor of row the and column of the pixel to make sure the scale is correct.
void Mandelbrot::mapCoordinates()
{
   //Equations for the "slices" of the graph, to get 10 slices you need 9 cuts, so the denominator is width/height - 1
  double dReal = (realMax - realMin)/(width - 1);
  double dI = (complexMax - complexMin)/(height - 1);
  double currentReal = realMin;
  double currentImaginary = complexMax;
  int index = 0;
  for (int r = 0; r < height; r++)
  {
    for (int x = 0; x < width; x++)
    {
      double real = currentReal + x*dReal;
      double imag = currentImaginary - r*dI;
      Complex add(real,imag);
      c[index] = add;
      index++;
    }
  }
}
//setIterations: Sets the prescribed max iterations for the escape algorithm
void Mandelbrot::setIterations(uint32_t n)
{
  iterations = n;
}
//setRealAxis: Takes a user-defined min and max and checks if they are the same, if the min and max are in the range [-2,1].
//If the min or max triggers these checks, the function sets the range to [-2,1] and returns false. If the values work, the values are
//put in realMin and realMax and the function returns true
bool Mandelbrot::setRealAxis(double min, double max)
{
  if (min == max || min < -2 || max > 1 || min > max) //If constraints are violated, revert range
  {
    realMin = -2;
    realMax = 1;
    return false;
  }
  realMin = min;
  realMax = max;
  return true;
}
//setImaginaryAxis: Takes a user-defined min and max and checks if they are the same, if the min and max are in the range [-1,1].
//If the min or max triggers these checks, the function sets the range to [-1,1] and returns false. If the values work, the values are
//put in complexMin and complexMax and the function returns true
bool Mandelbrot::setImaginaryAxis(double min, double max)
{
  if (min == max || min < -1 || max  > 1 || min > max) //If constraints are violated, revert range
  {
    complexMin = -1;
    complexMax = 1;
    return false;
  }
  complexMin = min;
  complexMax = max;
  return true;
}
//Draw: Conducts the escape algorithm z_n+1 = z_n^2 + c, and places the result in zn. After each iteration of the escape
//algorithm, the function checks if {I}^2 + {R}^2 > 4. If it is greater than 4, the iteration number is added to the img
//array, and the loop breaks. If the function gets all the way through the escape algorithm loop to a maximum number of
//iterations (100 or user-defined), the function puts the max number of iterations into the img array at a certain pixel.
//The function then calls the given writeImg function to create png "fractal.png"
bool Mandelbrot::draw()
{
  mapCoordinates();
  Complex zn1;
  for (int x = 0; x < width*height; x++)
  {
    bool notMax = false;
    zn = new Complex[iterations + 1]; //Must be iterations + 1 because the escape algorithm has values from z_1 to z_101
    Complex start(0.0,0.0);
    zn[0] = start;
    for (int i = 0; i < iterations; i++)
    {
      Complex zn1 = zn[i].multiply(zn[i]).add(c[x]); //Escape algorithm
      zn[i + 1] = zn1;
      double zn1lim = pow(zn[i + 1].getImaginary(), 2) + pow(zn[i + 1].getReal(), 2); //Abs of Complex
      if (zn1lim > 4) //Checking if value escapes
      {
        img[x] = i;
        notMax = true;
        break;
      }
    }
    if (!notMax) //If the value never escapes, must be set to 100, but the loop never does that
    {
      img[x] = iterations;
    }
    delete [] zn;
    zn = nullptr;
  }
  return writeImg(); //Given function to create image "fractal.png", returns it because writeImg returns a boolean
}
//getRealAxis: returns the real axis in a pair (realMin, realMax)
std::pair<double,double> Mandelbrot::getRealAxis()
{
  return std::pair<double,double> (realMin, realMax);
}
//getImaginaryAxis: returns the imaginary/complex axis in a pair(complexMin, complexMax)
std::pair<double,double> Mandelbrot::getImaginaryAxis()
{
  return std::pair<double,double> (complexMin, complexMax);
}
//getImageSize: returns the image size in a pair (width,height)
std::pair<uint16_t,uint16_t> Mandelbrot::getImageSize()
{
  return std::pair<uint16_t,uint16_t> (width, height);
}
bool Mandelbrot::writeImg()
{
  int i; //for iterating over pixels
  std::size_t idx = 0; //for iterating over rgba value per pixel
  uint32_t N = 1; //maximum number of iterations achieved (no division by zero).
  std::vector<double> t(width*height); //normalized color table
  std::vector<unsigned char> raw(4*width*height);; //rgba data for each pixel (each pixel has a byte for each; order is rgba)

  //normalize pixel values
  for(i = 0; i < width*height; i++)
    if(img[i] > N)
      N = img[i];

  for(i = 0; i < width*height; i++)
    t[i] = (double)img[i]/N;

  //assign pixel values according palette
  for(i = 0; i < width*height; i++)
    {
      raw[idx++] = 255*(0.5 + 0.5 * cos(2*PI*(1*t[i] + 0.00))); //r
      raw[idx++] = 255*(0.5 + 0.5 * cos(2*PI*(1*t[i] + 0.33))); //g
      raw[idx++] = 255*(0.5 + 0.5 * cos(2*PI*(1*t[i] + 0.67))); //b
      raw[idx++] = 255; //a
    }

  //write png
  unsigned error = lodepng::encode("fractal.png", raw, width, height);
  return true;
}
