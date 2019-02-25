#include "mandelbrot.hpp"

int main(int argc, char *argv[])
{
  Mandelbrot m;
  // Mandelbrot m(1020,1020);
  //   m.setRealAxis(-0.1,0.1);
  //   m.setComplexAxis(0.9,1.1);
  // Mandelbrot m(1020,1020);
  // m.setRealAxis(-0.1,0.1);
  // m.setComplexAxis(0.9,1.1);


  // Mandelbrot m(1020,1020);
  // m.setRealAxis(-2,-2.1);
  // m.setComplexAxis(-0.05,0.05);

  m.draw();
}
