DEPENDENCIESMAIN = complex.o fractal.o mandelbrot.o lodepng.o  
MandelbrotGenerator : $(DEPENDENCIESMAIN)
	g++ -Wall -g -o MandelbrotGenerator $(DEPENDENCIESMAIN)

complex.o : complex.cpp complex.hpp
	g++ -Wall -g -c complex.cpp

fractal.o : fractal.cpp mandelbrot.hpp
	g++ -Wall -g -c fractal.cpp

lodepng.o : lodepng.cpp lodepng.h
	g++ -Wall -g -c lodepng.cpp

mandelbrot.o : mandelbrot.cpp mandelbrot.hpp
	g++ -Wall -g -c mandelbrot.cpp
