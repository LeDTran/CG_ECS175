Le Tran
998104869
ledtran@ucdavis.edu

How to compile and run the project:
	make
	./p3.out
Optional
	make clean

____________________________________________

Running the program:
-On start, user will be prompted on whether or not they want to load a saved scene 
-After that, a display window will pop up
-In order to bring up the menu, right click on the display window.
-After selecting a menu option, you can input the values in the console

-All requirements for the assignment have been met.
	-Bezier curve drawing:
		-Set resolution
		-Add/Insert new control points at any position of curve
		-Delete any existing control point
		-Modify any existing control point
	-BSpline curve drawing:
		-Set resolution
		-Add/Insert new control points at any position of curve
		-Delete any control point
		-Modify any control point
		-Change order k
		-Modify knot values
	-The control curve is drawn in a dimmer color. The bezier/bspline curve is draw in a brighter color.
		-Bezier curves are red. BSpline curves are green.
		-Resolution is defaulted to 10, but can be modified during runtime
	-UI
	-Manual
-Extra credit:
	-The UI is preeeeeeeeeeeeeetty slick
____________________________________________

Saved scene:
-Saved scenes are saved within the file titled 'save.dat' 
-They can be loaded upon startup of the program
-It is possible to go into 'save.dat' and manually edit it

--------------------

-Curve information will be in this format

bz 				- 'bz' identifies the object as a Bezier curve
3 				- # of control points
0 6 			- control point 1
4 1
8 6

--------

bs 				- 'bs' identifies the object as a B-Spline curve
4 				- # control points
3 				- k value
T 				- are knots specified? (T/F)
1 7 			- control point 1
2 10
5 10
6 7
0 				- knot values
1 				
2 
3 
4 
5 
6 
7

bs
4
3
F 				- If F, knot values default to 0,1,2... when creating object at runtime
-1 7
-2 5
-5 10
-6 3
				-If F, knot values are not listed in save.dat
				-When saving scene, 0,1,2... knot values will be saved to file and F is turned to T

____________________________________________

Code lines:
-Bezier curve drawing: 			p4.cpp 343-437
	-Set resolution: 			UI.cpp 3-26
	-Add/Insert ctrl point: 	UI.cpp 53-104
	-Delete ctrl point: 		UI.cpp 160-194
	-Modify ctrl point: 		UI.cpp 233-273

-BSpline curve drawing: 		p4.cpp 238-340
	-Set resolution: 			UI.cpp 28-51
	-Add/Insert ctrl points: 	UI.cpp 106-158
	-Delete ctrl point: 		UI.cpp 196-231
	-Modify ctrl point: 		UI.cpp 275-315
	-Change order k: 			UI.cpp 317-340
	-Modify knot values: 		UI.cpp 342-379
-UI: UI.cpp