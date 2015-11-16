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
	-IMPORTANT: Only right clicking on the upper right window will bring up the window
	-I don't why it works like this, but it just does.
-After selecting a menu option, you can input the values in the console

Interpreting the display window:
-The three windows correspond to the xyz planes as so:
	[XZ][YZ]
	[XY][  ]

-All requirements for the assignment have been met.
	-Phong Lighting model for polyhedron points
		-Changing of constants/coefficients using command line
	-Gouraud Shading to rasturize and shade faces
	-Half Toning
	-Painter's algorithm so only the neccesariy faces are showing
	-UI
	-Manual
-Extra credit:
	-There is an animation option in the menu, that continuously 
	rotates all object in the scene over the axis (0,0,0)-(1, 1, 1)
		-This works with the rasturized objects, and even halftoned ones
		-That way, you can see the shading algo on the faces
		-You can even switch between shading and halftone whilst *mid rotation!!*
	-The UI is preeeeeeeeeeeeeetty sick
____________________________________________

Saved scene:
-Saved scenes are saved within the file titled 'save.dat' 
-They can be loaded upon startup of the program
-It is possible to go into 'save.dat' and manually edit it

--------------------

-Shape information will be in this format

P 					-'P' identifies the data as an object
4					-Number of points in the object
5.0 4.0 0.0			-Coordinates for each successive point
4.0 5.0 0.0
6.0 6.0 0.0
5.0 5.0 2.0
6					-Number of edges
1 2					-Point numbers that make up each edge
1 3
1 4
2 3
2 4
3 4
4					-Number of faces
1 2 3				-Point numbers that make up each face
1 2 4
1 3 4
2 3 4
4.0 4.0 -3.0		-Normals for corresponding face
2.0 2.0 1.0
8.0 2.0 1.0
2.0 8.0 1.0

____________________________________________

Code lines:
-Phong Lighting Model: p3.cpp 675-782
-Gouraud Shading: p3.cpp 784-1047
-Half Toning: p3.cpp 1129-1313 
-Painter's algorithm: poly.cpp 343-417

-UI: UI.cpp