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

    int resolution;

  public:
    BSpline();
    BSpline(vector<float> ctrlxs, vector<float> ctrlys, float k, vector<float> knotvalue);
    void printData();
    float getCtrlXPoint(int i);
    float getCtrlYPoint(int i);
    float getNumCtrlPoints();
};

#endif