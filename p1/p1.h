#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include "Poly.h"
#include "UI.h"
using namespace std;

extern vector<int *> allLines;
extern vector<Poly *> allPoly;

void display();
void readData();
void drawPix(float *PixelBuffer, int *point);
void drawLineDDA(int * p1, int *p2, bool ispoly, int p);
void drawLineBresenham(int * p1, int *p2, bool ispoly, int p);
void drawPolygon(int p);
void translatePolygon(int p, int dx, int dy);
void scalePolygon(int p, float sx, float sy);
void rotatePolygon(int p, int deg);
void rasterizePolygon(int p);
int findABRL(int x, int y, int xmin, int xmax, int ymin, int ymax);
void clipLine(int l, int xmin, int xmax, int ymin, int ymax);
void drawScene();
