#include "BSpline.h"

BSpline::BSpline(){
	//ctr
}

BSpline::BSpline(vector<float> ctrlxs, vector<float> ctrlys, float k, char knotchar, float knot){
	ctrlxpoints = ctrlxs;
	ctrlypoints = ctrlys;

  kvalue = k;
  if(knotchar == 'T'){
    haveknot = true;
    knotvalue = knot;
  }
  else if (knotchar == 'F'){
    haveknot = false;
  }
}

void BSpline::printData(){
  cout << "xy" << endl;
  for(int i = 0; i < (int)ctrlxpoints.size(); i++){
    cout << ctrlxpoints[i] << " " << ctrlypoints[i] << endl;
  }

  cout << "k: " << kvalue << ", haveknot: " << haveknot << ", knot: " << knotvalue << endl;

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