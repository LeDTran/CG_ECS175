p1.out: p3.o Poly.o UI.o
	g++ -g -Wall -ansi -o p3.out p3.o Poly.o UI.o -lglut -lGL

UI.o: UI.cpp UI.h p3.h Poly.h
	g++ -g -Wall -ansi -c UI.cpp -lglut -lGL 

Poly.o: Poly.cpp Poly.h
	g++ -g -Wall -ansi -c Poly.cpp -lglut -lGL 

p3.o: p3.cpp p3.h Poly.h UI.h
	g++ -g -Wall -ansi -c p3.cpp -lglut -lGL

clean:
	rm -f *out *o

