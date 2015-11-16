#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <algorithm>    //iter_swap
#include "Poly.h"
#include "Face.h"
#include "UI.h"
using namespace std;

// extern vector<int *> allLines;
extern vector<Poly *> allPoly;
extern bool isAnimating;
extern bool isHalfTone;
extern float* BufferXY;
extern float* BufferXZ;
extern float* BufferYZ;


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
void drawPolygon(int p, int plane);
void translatePolygon(int p, float dx, float dy, float dz);
void scalePolygon(int p, float sx, float sy, float sz);
void rotatePolygon(int p, float x1, float y1, float z1, float x2, float y2, float z2, float pdeg);
void reSortPolys(int plane);
void updateRotate(int i);
void startAnimation();
void readData();
void calculateC();
void setValues();
void resetValues();
float phongLighting(int i, int j);
void setIpValues();
float gouraudShading(int *p1, int *p2, float *pa, float i1, float i2);
void drawLineFace(float *Buffer, float * fp1, float *fp2, Face* currFace, bool isFace, float ip1, float ip2);
void drawFace(Face* currFace, int plane);
void rasterizeFaces(int p, int plane);
void drawScene();
float getAvgIntensity(float *Buffer, int *a, int *b, int color);
void drawMegapixel(float *Buffer, int *a, int *b, int code);
void halfTone();


