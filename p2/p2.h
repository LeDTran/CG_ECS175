#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include "Poly.h"
using namespace std;

// extern vector<int *> allLines;
extern vector<Poly *> allPoly;

void drawPix(float *PixelBuffer, int x, int y, float red, float green, float blue);
void display();
void display1();
void display2();
void display3();
float getXMin();
float getXMax();
float getYMin();
float getYMax();
float getZMin();
float getZMax();
void updateMinMax();
float getRatio(float coord, char axis);
void drawLineDDA(float *Buffer, float *fp1, float *fp2, float r, float g, float b);
void drawPolygon(int p);
void translatePolygon(int p, float dx, float dy, float dz);
void scalePolygon(int p, float sx, float sy, float sz);


void drawScene();

// void display();
// void readData();
// void drawPix(float *PixelBuffer, int *point);
// void drawLineDDA(int * p1, int *p2, bool ispoly, int p);
// void drawLineBresenham(int * p1, int *p2, bool ispoly, int p);
// void drawPolygon(int p);
// void translatePolygon(int p, int dx, int dy);
// void scalePolygon(int p, float sx, float sy);
// void rotatePolygon(int p, int deg);
// void rasterizePolygon(int p);
// int findABRL(int x, int y, int xmin, int xmax, int ymin, int ymax);
// void clipLine(int l, int xmin, int xmax, int ymin, int ymax);
// void drawScene();
