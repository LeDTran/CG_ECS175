p1.out: p2.o Poly.o
	g++ -g -Wall -ansi -o p2.out p2.o Poly.o -lglut -lGL

Poly.o: Poly.cpp Poly.h
	g++ -g -Wall -ansi -c Poly.cpp -lglut -lGL 

p2.o: p2.cpp p2.h Poly.h
	g++ -g -Wall -ansi -c p2.cpp -lglut -lGL

clean:
	rm -f *out *o

