#ifndef FACE_H
#define FACE_H
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

class Face{
  private:
    vector<int> xpoints;
    vector<int> ypoints;
    vector<int> edgexpoints;
    vector<int> edgeypoints;
    bool israsterized;
	 // constructor

  public:
    Face();
    Face(vector<int> x, vector<int> y, bool rasterizationstate);
    int getXPoint(int i);
    int getYPoint(int i);
    int getNumPoints();
    int getCentroidX();
    int getCentroidY();
    void translatePoly(int dx, int dy);
    void scalePoly(float sx, float sy);
    void rotatePoly(int deg);
    int getLocalMaxY();
    int getLocalMinY();
    void addEdgeX(int x);
    void addEdgeY(int y);
    void resetEdgePoints();
    void sortEdgePoints();
    int getNumEdgePoints();
    int getEdgeXPoint(int i);
	int getEdgeYPoint(int i);
    void turnOnRasterization();
    bool getIsRasterized();
};

#endif