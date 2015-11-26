#include "BSpline.h"

BSpline::BSpline(){
	//ctr
}

BSpline::BSpline(vector<float> ctrlxs, vector<float> ctrlys, float k, vector<float> knotvalues){
	ctrlxpoints = ctrlxs;
	ctrlypoints = ctrlys;

  kvalue = k;
  knots = knotvalues;

  resolution = 10;
}

void BSpline::printData(){
  cout << "xy" << endl;
  for(int i = 0; i < (int)ctrlxpoints.size(); i++){
    cout << ctrlxpoints[i] << " " << ctrlypoints[i] << endl;
  }

  cout << "k: " << kvalue << endl;

  for(int i = 0; i < (int)knots.size(); i++){
    cout << knots[i] << endl;
  }

  cout << "------------------------------------" << endl;
}

float BSpline::getCtrlXPoint(int i){
  return ctrlxpoints[i];
}

float BSpline::getCtrlYPoint(int i){
  return ctrlypoints[i];
}


float BSpline::getNumCtrlPoints(){
  return ctrlxpoints.size();
}