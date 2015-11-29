p4.out: p4.o Bezier.o BSpline.o UI.o
	g++ -g -Wall -ansi -o p4.out p4.o Bezier.o BSpline.o UI.o -lglut -lGL

UI.o: UI.cpp UI.h p4.h Bezier.h BSpline.h
	g++ -g -Wall -ansi -c UI.cpp -lglut -lGL 

BSpline.o: BSpline.cpp BSpline.h
	g++ -g -Wall -ansi -c BSpline.cpp -lglut -lGL 

Bezier.o: Bezier.cpp Bezier.h
	g++ -g -Wall -ansi -c Bezier.cpp -lglut -lGL 

p4.o: p4.cpp p4.h Bezier.h BSpline.h
	g++ -g -Wall -ansi -c p4.cpp -lglut -lGL

clean:
	rm -f *out *o

