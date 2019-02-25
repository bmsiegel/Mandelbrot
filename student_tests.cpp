#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "mandelbrot.hpp"
#include "image.h"

TEST_CASE("Tests default constructor")
{
  //Checks that the default values are used
  Mandelbrot m;
  REQUIRE(m.getImageSize() == std::pair<uint16_t,uint16_t> (1020, 680));
  REQUIRE(m.getRealAxis() == std::pair<double,double> (-2,1));
  REQUIRE(m.getImaginaryAxis() == std::pair<double,double> (-1,1));
}
TEST_CASE("Tests getters and setters for good values")
{
  //Makes sure the getters return values that were given in they work in the project requirements
  Mandelbrot m;
  m.setRealAxis(-0.5,0.5);
  m.setImaginaryAxis(-0.5,0.5);
  REQUIRE(m.getRealAxis() == std::pair<double,double> (-0.5,0.5));
  REQUIRE(m.getImaginaryAxis() == std::pair<double,double> (-0.5,0.5));
}
TEST_CASE("Tests getters and setters for bad values")
{
  //Makes sure for variables that break constraints, the getters return default values
  Mandelbrot m;
  m.setRealAxis(0.5,0.5);
  m.setImaginaryAxis(0.5,0.5);
  REQUIRE(m.getRealAxis() == std::pair<double,double> (-2,1));
  REQUIRE(m.getImaginaryAxis() == std::pair<double,double> (-1,1));
  m.setRealAxis(0.5,-0.5);
  m.setImaginaryAxis(0.5,-0.5);
  REQUIRE(m.getRealAxis() == std::pair<double,double> (-2,1));
  REQUIRE(m.getImaginaryAxis() == std::pair<double,double> (-1,1));

}
TEST_CASE("Tests setters boolean values")
{
  //Values outside the range or equal should be false, good values should be true
  Mandelbrot m;
  REQUIRE(m.setRealAxis(0.5,0.5) == false);
  REQUIRE(m.setImaginaryAxis(0.5,0.5) == false);
  REQUIRE(m.setRealAxis(-2,2) == false);
  REQUIRE(m.setImaginaryAxis(-2,2) == false);
  REQUIRE(m.setRealAxis(-0.5,0.5) == true);
  REQUIRE(m.setImaginaryAxis(-0.5,0.5) == true);
  REQUIRE(m.setImaginaryAxis(0.5, -0.5) == false);
  REQUIRE(m.setRealAxis(0.5, -0.5) == false);
}
TEST_CASE("Tests image size constraints")
{
  //Makes sure each parameter changes when outside range, as well as both
  Mandelbrot m(1,1);
  Mandelbrot n(3,1);
  Mandelbrot o(1,3);
  REQUIRE(m.getImageSize() == std::pair<uint16_t,uint16_t> (2, 2));
  REQUIRE(n.getImageSize() == std::pair<uint16_t,uint16_t> (3, 2));
  REQUIRE(o.getImageSize() == std::pair<uint16_t,uint16_t> (2, 3));
}
// TEST_CASE( "Image compare", "[mandelbrot]" )
// {
//   //this is probably a bad idea...use compare.cpp instead.
//   Mandelbrot m(1020,680);
//
//   m.draw();
//
//   Image<Pixel> test1 = readFromFile("fractal.png");
//   Image<Pixel> ref1 = readFromFile("tests/fractal01.png");
//
//   REQUIRE(test1.width() == ref1.width());
//   REQUIRE(test1.height() == ref1.height());
//
//   for (intmax_t i = 0; i < test1.width(); ++i)
//     for (intmax_t j = 0; j < test1.height(); ++j)
//       REQUIRE( test1(i,j) == ref1(i,j));
//
// }
// TEST_CASE( "Tests setIterations", "[mandelbrot]" )
// {
//   //Tests set iterations by drawing an image with 10 iterations over the same range, then running the
//   //compare algorithm to check if the images are in fact different
//   Mandelbrot m(1020,680);
//
//   m.setIterations(10);
//   m.draw();
//
//   Image<Pixel> test1 = readFromFile("fractal.png");
//   Image<Pixel> ref1 = readFromFile("tests/fractal01.png");
//
//   REQUIRE(test1.width() == ref1.width());
//   REQUIRE(test1.height() == ref1.height());
//   bool different = false;
//   for (intmax_t i = 0; i < test1.width(); ++i)
//     for (intmax_t j = 0; j < test1.height(); ++j)
//       if (test1(i, j) != ref1(i, j))
//       {
//         different = true;
//       }
//   REQUIRE(different);
// }
TEST_CASE( "Makes sure draw returns true")
{
  //If image is created, function should return true
  Mandelbrot m(1020,680);
  REQUIRE(m.draw());
}
