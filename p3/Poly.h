#ifndef POLY_H
#define POLY_H
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

class Poly{
  private:
    vector<float> xpoints;
    vector<float> ypoints;
    vector<float> zpoints;

    vector<int> linep1;
    vector<int> linep2;

    vector<int> facep1; 
    vector<int> facep2; 
    vector<int> facep3;
            
    vector<float> fnormp1; 
    vector<float> fnormp2; 
    vector<float> fnormp3;
 
    vector<int> edgexpoints;
    vector<int> edgeypoints;
    //bool israsterized;
	 // constructor

  public:
    Poly();
    Poly(vector<float> xs, vector<float> ys, vector<float> zs, 
            vector<int> lp1, vector<int> lp2, 
            vector<int> fp1, vector<int> fp2, vector<int> fp3,
            vector<float> fnp1, vector<float> fnp2, vector<float> fnp3);
    void printData();
    float getXPoint(int i);
    float getYPoint(int i);
    float getZPoint(int i);
    float getNumPoints();
    int getLineP1(int i);
    int getLineP2(int i);
    int getNumLineP();
    float getCentroidX();
    float getCentroidY();
    float getCentroidZ();
    void translatePoly(float dx, float dy, float dz);
    void scalePoly(float sx, float sy, float sz);
    void rotatePolyXAxis(float deg);
    void rotatePolyYAxis(float deg);
    void rotatePolyZAxis(float deg);
    void rotateIntoXYPlane(float adj, float opp, float hyp);
    void rotateOutOfXYPlane(float adj, float opp, float hyp);
    void rotateIntoZAxis(float adj, float opp, float hyp);
    void rotateOutOfZAxis(float adj, float opp, float hyp);
};

#endif