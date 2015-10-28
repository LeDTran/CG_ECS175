Le Tran
998104869
ledtran@ucdavis.edu

How to compile and run the project:
make
./p1.out

____________________________________________

Running the program:
-On start, user will be prompted for window width and height
-After that, user will be prompted on whether or not they want to load a saved scene 
-After that, a display window will pop up
-In order to bring up the menu, press the 'm' key whilst INSIDE the display window, NOT the console
	-It is ******VERY IMPORTANT****** that 'm' is not pressed whilst on the command line, as this will cause problems

-Although both DDA and Bresenham are implemented and can be chosen while creating individual lines
	-When drawing polygons and rasterizing them, the program defaults to using DDA
	-This is hard coded in, but can be easily switched to Bresenham
-Most of the requirements for the program have been met
	-Things that HAVEN'T been implemented:
		-Rasterization of concave and complex polygons (currently only works for concave)
		-Polygon clipping (line clipping IS implemented)

____________________________________________

Saved scene:
-Saved scenes are saved within the file titled 'save.dat' 
-They can be loaded upon startup of the program
-Scenes can be saved upon selecting the '8' option in the main menu
	-Scenes will not be saved automatically after every transformation
	-Scences need to be manually saved
-It is possible to go into 'save.dat' and manually edit it

--------------------

Format:
-Line information will be in this format

L
xx yy
xx yy
1

-The first line identifies the data as a line
-The second line holds the coordinates for the first point
-The third line holds the coordinates for the second point
-The fourth line determines the line drawing algorithm
	- 1 = DDA, 2 = Bresenham

---------------

-Polygon information will be in this format

P
3
xx yy
xx yy
.
.
xx yy
1

-The first line identifies the data as a polygon
-The second line holds the number of points in the polygon
-Subsequent lines hold the coordinates for each successive point
-The final line determins whether or not the polygon has been rasterized
	- 0 = has NOT been rasterized, 1 = HAS been rasterized

____________________________________________

Code lines:
-Window size input: p1.cpp 17-20
-Read from file: p1.cpp 56-114
-Write to file: UI.cpp 185-227

-DDA line drawing: p1.cpp 131-193
-Bresenham line drawing: p1.cpp 195-335

-Line clipping: p1.cpp 417-523
-Polygon clipping: NOT IMPLEMENTED

-Polygon translation: p1.cpp 363-365 -> Poly.cpp 41-46
-Polygon scaling: p1.cpp 368-364 -> Poly.cpp 48-53
-Polygon rotation: p1.cpp 377-383 -> Poly.cpp 55-65
-Polygon rasturization (concave only!): p1.cpp 386-415

-UI: UI.cpp


