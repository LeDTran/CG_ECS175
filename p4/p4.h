#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include "Bezier.h"
#include "BSpline.h"
//#include "UI.h"
using namespace std;

// extern vector<int *> allLines;
extern vector<Bezier *> allBezier;
extern vector<BSpline *> allBSpline;

extern bool isAnimating;
extern float *PixelBuffer;

void drawPix(float *PixelBuffer, int x, int y, float red, float green, float blue);
void display();
float getXMin();
float getXMax();
float getYMin();
float getYMax();
void updateMinMax();
float getRatio(float coord, char axis);
void drawLineDDA(float *Buffer, float *fp1, float *fp2, float r, float g, float b);
void drawBSplineControl(int p);
void drawBSpline(int p);
void drawBezierControl(int p);
void drawBezier(int p);
void drawScene();
void readData();