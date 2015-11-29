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

void Bezier::insertCtrlPoint(int pos, float x, float y){
  ctrlxpoints.insert(ctrlxpoints.begin()+pos, x);
  ctrlypoints.insert(ctrlypoints.begin()+pos, y);
}

void Bezier::deleteCtrlPoint(int pointselection){
  ctrlxpoints.erase(ctrlxpoints.begin()+pointselection);
  ctrlypoints.erase(ctrlypoints.begin()+pointselection);
}

void Bezier::modifyCtrlPoint(int pointselection, float x, float y){
  ctrlxpoints[pointselection] = x;
  ctrlypoints[pointselection] = y;
}


float Bezier::getResolution(){
  return resolution;
}

void Bezier::setResolution(float r){
  resolution = r;
}

