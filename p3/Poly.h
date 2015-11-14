#ifndef POLY_H
#define POLY_H
#include <vector>
#include <math.h>
#include <iostream>
#include "Face.h"
using namespace std;

class Poly{
  private:
    //all points of poly
    vector<float> xpoints;
    vector<float> ypoints;
    vector<float> zpoints;

    //used for poly sorting
    float smallestx;
    float smallesty;
    float smallestz;

    //intensity corresponds to repective point index
    vector<float> IpR;
    vector<float> IpG;
    vector<float> IpB;

    //edges of poly
    vector<int> linep1;
    vector<int> linep2;

    //points of faces of poly
    vector<int> facep1; 
    vector<int> facep2; 
    vector<int> facep3;
            
    //normals for corresponding faces        
    vector<float> fnormx; 
    vector<float> fnormy; 
    vector<float> fnormz;
    
    //vector of faces of poly
    vector<Face *> polyFaces;


    vector<int> edgexpoints;
    vector<int> edgeypoints;
    //bool israsterized;
	 // constructor

  public:
    Poly();
    Poly(vector<float> xs, vector<float> ys, vector<float> zs, 
            vector<int> lp1, vector<int> lp2, 
            vector<int> fp1, vector<int> fp2, vector<int> fp3,
            vector<float> fnx, vector<float> fny, vector<float> fnz);
    void printData();
    float getXPoint(int i);
    float getYPoint(int i);
    float getZPoint(int i);
    void determineSmallest();
    float getSmallestX();
    float getSmallestY();
    float getSmallestZ();
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
    float getVertexNormalX(int j);
    float getVertexNormalY(int j);
    float getVertexNormalZ(int j);
    int getNumFaces();
    void reSortFaces(int plane);
    void setIp(vector<float> ipr, vector<float>ipg, vector<float> ipb);
    void reMakeFaces(int plane);
    Face* getFace(int i);
};

#endif