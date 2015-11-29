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
    void addCtrlPoint(float x, float y);
    void deleteCtrlPoint(int pointselection);

    float getResolution();
    void setResolution(float r);
    float getKValue();
    float getUBar(float k, float n, float a);
    float getI(float ubar);

    vector<float> getKnots();
    void addKnot();
    void deleteKnot();
};

#endif