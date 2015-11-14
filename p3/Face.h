#ifndef FACE_H
#define FACE_H
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

class Face{
  private:
    //a/b points depends on current drawing axis
    vector<float> apoints;
    vector<float> bpoints;

    //intensity corresponds to a/b point index
    vector<float> IpR;
    vector<float> IpG;
    vector<float> IpB;

    //list of edge points to use for rasturization
    vector<float> edgeapoints;
    vector<float> edgebpoints;
    bool israsterized;
	 // constructor

  public:
    Face();
    Face(vector<float> a, vector<float> b, vector<float> ipr, vector<float> ipg, vector<float> ipb);
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