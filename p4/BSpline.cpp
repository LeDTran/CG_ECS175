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

void BSpline::insertCtrlPoint(int pos, float x, float y){
  ctrlxpoints.insert(ctrlxpoints.begin()+pos, x);
  ctrlypoints.insert(ctrlypoints.begin()+pos, y);
}

void BSpline::deleteCtrlPoint(int pointselection){
  ctrlxpoints.erase(ctrlxpoints.begin()+pointselection);
  ctrlypoints.erase(ctrlypoints.begin()+pointselection);
}

void BSpline::modifyCtrlPoint(int pointselection, float x, float y){
  ctrlxpoints[pointselection] = x;
  ctrlypoints[pointselection] = y;
}


float BSpline::getResolution(){
  return resolution;
}

void BSpline::setResolution(float r){
  resolution = r;
}


float BSpline::getKValue(){
  return kvalue;
}

void BSpline::setKValue(float k){
  kvalue = k;
}


float BSpline::getUBar(float k, float n, float a){
  //cout << "first: " << knots[k-1] << ", second: " << knots[n+1] + knots[k-1] << endl;
  float ubar;
  ubar = knots[k-1] + (a/resolution)*(knots[n+1] - knots[k-1]);
  //cout << "ubar: " << ubar << endl;
  return ubar;
}

float BSpline::getI(float ubar){
  for(int i = (int)knots.size()-1; i >= 0; i--){
    //cout << "knots: " << knots[i] << endl;
    if(ubar >= knots[i]){
      //cout <<"equals: " << i << endl;
      return i;
    }
  }
  return 0;
}


vector<float> BSpline::getKnots(){
  return knots;
}

void BSpline::addKnot(){
  float newknot = knots[knots.size()-1];
  knots.push_back(newknot+1);
}

void BSpline::deleteKnot(){
  knots.erase(knots.end()-1);
}

void BSpline::modifyKnot(int pointselection, float knot){
  knots[pointselection] = knot;
}

int BSpline::getNumKnots(){
  return knots.size();
}

float BSpline::getKnotValue(int i){
  return knots[i];
}