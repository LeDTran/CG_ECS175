#ifndef BEZIER_H
#define BEZIER_H
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

class Bezier{
  private:
    vector<float> ctrlxpoints;
    vector<float> ctrlypoints;

  public:
    Bezier();
    Bezier(vector<float> ctrlxs, vector<float> ctrlys);
    void printData();
    float getCtrlXPoint(int i);
    float getCtrlYPoint(int i);
    float getNumCtrlPoints();
};

#endif