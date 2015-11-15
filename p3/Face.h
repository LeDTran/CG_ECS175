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

  public:
    Face();
    Face(vector<float> a, vector<float> b, vector<float> ipr, vector<float> ipg, vector<float> ipb);
    void printData();
    float getAPoint(int i);
    float getBPoint(int i);
    int getNumPoints();
    float getLocalMaxB();
    float getLocalMinB();
    void addEdgeA(float a);
    void addEdgeB(float b);
    void resetEdgePoints();
    void sortEdgePoints();
    int getNumEdgePoints();
    float getEdgeAPoint(int i);
	float getEdgeBPoint(int i);
};

#endif