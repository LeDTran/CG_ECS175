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

float BSpline::getResolution(){
  return resolution;
}

float BSpline::getKValue(){
  return kvalue;
}

float BSpline::getUBar(float k, float n, float a){
  //cout << "first: " << knots[k-1] << ", second: " << knots[n+1] + knots[k-1] << endl;
  float ubar;
  ubar = knots[k-1] + (a/resolution)*(knots[n+1] - knots[k-1]);
  //cout << "ubar: " << ubar << endl;
  return ubar;
}

float BSpline::getI(float ubar){
  //cout << "-------ubar: " << ubar << endl;
  // for(int i = 0; i < (int)knots.size(); i++){
  //   cout << "knots: " << knots[i] << endl;
  //   if(knots[i] == ubar){
  //     cout <<"equals: " << i << endl;
  //     return i;
  //   }
  //   else if(knots[i] > ubar){
  //     cout <<"greater: " << i-1 << endl;
  //     return i-1;
  //   }
  // }
  for(int i = (int)knots.size()-1; i >= 0; i--){
    //cout << "knots: " << knots[i] << endl;
    if(ubar >= knots[i]){
      //cout <<"equals: " << i << endl;
      return i;
    }
    // else if(knots[i] > ubar){
    //   cout <<"greater: " << i-1 << endl;
    //   return i-1;
    // }
  }
  return 0;
}

vector<float> BSpline::getKnots(){
  return knots;
}