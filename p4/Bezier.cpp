#include "Bezier.h"

Bezier::Bezier(){
	//ctr
}

Bezier::Bezier(vector<float> ctrlxs, vector<float> ctrlys){
	ctrlxpoints = ctrlxs;
	ctrlypoints = ctrlys;

  resolution = 10;
}

void Bezier::printData(){
  cout << "xy" << endl;
  for(int i = 0; i < (int)ctrlxpoints.size(); i++){
    cout << ctrlxpoints[i] << " " << ctrlypoints[i] << endl;
  }

  cout << "------------------------------------" << endl;
}

float Bezier::getCtrlXPoint(int i){
  return ctrlxpoints[i];
}

float Bezier::getCtrlYPoint(int i){
  return ctrlypoints[i];
}


float Bezier::getNumCtrlPoints(){
  return ctrlxpoints.size();
}

void Bezier::addCtrlPoint(float x, float y){
  ctrlxpoints.push_back(x);
  ctrlypoints.push_back(y);
}

void Bezier::deleteCtrlPoint(int pointselection){
  ctrlxpoints.erase(ctrlxpoints.begin()+pointselection);
  ctrlypoints.erase(ctrlypoints.begin()+pointselection);
}


float Bezier::getResolution(){
  return resolution;
}

void Bezier::setResolution(float r){
  resolution = r;
}

