p1.out: p1.o Poly.o UI.o
	g++ -g -Wall -ansi -o p1.out p1.o Poly.o UI.o -lglut -lGL

UI.o: UI.cpp UI.h p1.h Poly.h
	g++ -g -Wall -ansi -c UI.cpp -lglut -lGL 

Poly.o: Poly.cpp Poly.h
	g++ -g -Wall -ansi -c Poly.cpp -lglut -lGL 

p1.o: p1.cpp p1.h Poly.h UI.h
	g++ -g -Wall -ansi -c p1.cpp -lglut -lGL

clean:
	rm -f *out *o

