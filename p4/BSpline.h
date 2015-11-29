#ifndef BSPLINE_H
#define BSPLINE_H
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

class BSpline{
  private:
    vector<float> ctrlxpoints;
    vector<float> ctrlypoints;

   	float kvalue;

   	vector<float> knots;

    float resolution;

  public:
    BSpline();
    BSpline(vector<float> ctrlxs, vector<float> ctrlys, float k, vector<float> knotvalue);
    void printData();
    float getCtrlXPoint(int i);
    float getCtrlYPoint(int i);
    float getNumCtrlPoints();
    void insertCtrlPoint(int pos, float x, float y);
    void deleteCtrlPoint(int pointselection);
    void modifyCtrlPoint(int pointselection, float x, float y);

    float getResolution();
    void setResolution(float r);

    float getKValue();
    void setKValue(float k);


    float getUBar(float k, float n, float a);
    float getI(float ubar);

    vector<float> getKnots();
    void addKnot();
    void deleteKnot();
    void modifyKnot(int pointselection, float knot);
    int getNumKnots();
    float getKnotValue(int i);
};

#endif