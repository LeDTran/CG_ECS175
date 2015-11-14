p3.out: p3.o Poly.o Face.o UI.o
	g++ -g -Wall -ansi -o p3.out p3.o Poly.o Face.o UI.o -lglut -lGL

UI.o: UI.cpp UI.h p3.h Poly.h Face.h
	g++ -g -Wall -ansi -c UI.cpp -lglut -lGL 

Face.o: Face.cpp Face.h
	g++ -g -Wall -ansi -c Face.cpp -lglut -lGL 

Poly.o: Poly.cpp Poly.h Face.h
	g++ -g -Wall -ansi -c Poly.cpp -lglut -lGL 

p3.o: p3.cpp p3.h Poly.h Face.h UI.h
	g++ -g -Wall -ansi -c p3.cpp -lglut -lGL

clean:
	rm -f *out *o

