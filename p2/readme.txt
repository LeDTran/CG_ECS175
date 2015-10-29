Le Tran
998104869
ledtran@ucdavis.edu

How to compile and run the project:
	make
	./p2.out
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
	-General Functions
		-Save/Load data
	-Scaling, Translation, and Rotation of shapes
		-Rotation should display the axis of rotation
	-Orthogonal Projections
	-UI
	-Manual
-Extra credit:
	-There is an animation option in the menu, that continuously 
	rotates all object in the scene over the axis (0,0,0)-(1, 1, 1)
	-The UI is pretty sick
____________________________________________

Saved scene:
-Saved scenes are saved within the file titled 'save.dat' 
-They can be loaded upon startup of the program
-Scenes can be saved upon selecting the option in the main menu
	-Scenes will not be saved automatically after every transformation
	-Scences need to be manually saved
-It is possible to go into 'save.dat' and manually edit it

--------------------

-Shape information will be in this format

P
3
xx yy zz
xx yy zz
.
.
xx yy zz
3
p1 p2
p2 p2
.
.
p1 p2

-The first line identifies the data as a shape
-The second line holds the number of points in the shape
-Subsequent lines hold the coordinates for each successive point
-After reading in the points, then the next number will be the number of edges
-Subsequent lines hold the point numbers that make up each edge

