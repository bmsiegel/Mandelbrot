#ifndef _MANDELBROT_HPP_
#define _MANDELBROT_HPP_

#include <utility>

#include "complex.hpp"

/*
 * A C++ class for calculating the Mandelbrot set using the escape algorithm
 */
class Mandelbrot
{
private:
  uint16_t width; //width of image
  uint16_t height; //height of image
  double realMin; //left bound of real axis
  double realMax; //right bound of real axis
  double complexMin; //left bound of complex axis
  double complexMax; //right bound of complex axis
  int iterations; //Number of iterations of the escape algorithm, more iterations means more accuracy
  uint32_t* img; //pointer to array of size width-times-height to hold iteration number at which pixel (point) escaped
  Complex* c; //pointer to array of complex numbers that represent complex coordinate of each pixel
  Complex* zn; //pointer to array of complex numbers that represents the value of the escape algorithm (z_{n+1} = z_n + c) after the n-th iteration
  // feel free to define additional variables

  // feel free to define additional helper functions...maybe one that maps pixel values to coordinates?
  bool writeImg(); //write img to disk as "fractal.png"
  void mapCoordinates(); //Maps pixels to complex coordinates in pointer c
public:
  /*
   * Default constructor: image size 1020-by-680 pixels (width-by-height), real min/max: -2/1, imaginary min/max: -1/1, 100 iterations
   */
  Mandelbrot();

  /*
   * Constructor to allow user to specify image of lower/higher resolution.  Minimum resolution is 2-by-2 pixels.  Same default values for axes and iterations as previous constructor
   * @param width - number of horizontal pixels for image of Mandelbrot set
   * @param height - number of vertical pixels for image of Mandelbrot set
   */
  Mandelbrot( uint16_t w, uint16_t h);

  /*
   * Destructor: clean-up dynamically allocated memory
   */
  ~Mandelbrot();

  /*
   * Set the number of iterations for the escape time algorithm
   */
  void setIterations(uint32_t n);

  /*
   * Set the minimum and maximum value of the real axis.  These must lie between [-2,1] and they cannot be the same.  Use default values if constraints violated.
   * @return if true then user values accepted, if false then default values used.
   */
  bool setRealAxis(double min, double max);

  /*
   * Set the minimum and maximum value of the real axis.  These must lie between [-1,1] and they cannot be the same.  Use default values if constraints violated.
   * @return if true then user values accepted, if false then default values used.
   */
  bool setImaginaryAxis(double min, double max);

  /*
   * run escape time algorithm on the axes specified by the user and write result to file
   * @return true if the fractal was successfully written as a PNG
   */
  bool draw();

  /*
   * return real axis values
   * @return pair containing minimum (first) and maximum (second) value of real axis
   */
  std::pair<double,double> getRealAxis();

  /*
   * return imaginary axis values
   * @return pair containing minimum (first) and maximum (second) value of imaginary axis
   */
  std::pair<double,double> getImaginaryAxis();

  /*
   * return image size
   * @return pair containing width (first) and height (second) value of image
   */
  std::pair<uint16_t,uint16_t> getImageSize();
};

#endif //_MANDELBROT_HPP_
