p1.out: p2.o Poly.o UI.o
	g++ -g -Wall -ansi -o p2.out p2.o Poly.o UI.o -lglut -lGL

UI.o: UI.cpp UI.h p2.h Poly.h
	g++ -g -Wall -ansi -c UI.cpp -lglut -lGL 

Poly.o: Poly.cpp Poly.h
	g++ -g -Wall -ansi -c Poly.cpp -lglut -lGL 

p2.o: p2.cpp p2.h Poly.h UI.h
	g++ -g -Wall -ansi -c p2.cpp -lglut -lGL

clean:
	rm -f *out *o

