#include "Poly.h"

Poly::Poly(){
	//ctr
}

Poly::Poly(vector<int> xs, vector<int> ys, bool rasterizationstate){
	xpoints = xs;
	ypoints = ys;
  israsterized = rasterizationstate;
}

int Poly::getXPoint(int i){
  return xpoints[i];
}

int Poly::getYPoint(int i){
  return ypoints[i];
}

int Poly::getNumPoints(){
  return xpoints.size();
}

int Poly::getCentroidX(){
  int x = 0;
  for(int i = 0; i < getNumPoints(); i++){
    x = x + xpoints[i];
  }
  return round(x/getNumPoints());
}

int Poly::getCentroidY(){
  int y = 0;
  for(int i = 0; i < getNumPoints(); i++){
    y = y + ypoints[i];
  }
  return round(y/getNumPoints());
}

void Poly::translatePoly(int dx, int dy){
  for(int i = 0; i < getNumPoints(); i++){
    xpoints[i] = xpoints[i] + dx;
    ypoints[i] = ypoints[i] + dy;
  }
}

void Poly::scalePoly(float sx, float sy){
  for(int i = 0; i < getNumPoints(); i++){
    xpoints[i] = round((float)xpoints[i] * sx);
    ypoints[i] = round((float)ypoints[i] * sy);
  }
}

void Poly::rotatePoly(int deg){
  float xNew;
  float yNew;
  //float radian =  deg * M_PI  / 180.0;
  for(int i = 0; i < getNumPoints(); i++){
    xNew = round(cos(deg * M_PI  / 180.0)*(float)xpoints[i] - sin(deg * M_PI  / 180.0)*(float)ypoints[i]);
    yNew = round(sin(deg * M_PI  / 180.0)*(float)xpoints[i] + cos(deg * M_PI  / 180.0)*(float)ypoints[i]);
    xpoints[i] = (int)xNew;
    ypoints[i] = (int)yNew;
  }
}

int Poly::getLocalMaxY(){
  int max = ypoints[0];
  for(int i = 0; i < (int)ypoints.size(); i++){
    if(ypoints[i] > max){
      max = ypoints[i];
    }
  }
  return max;
}

int Poly::getLocalMinY(){
  int min = ypoints[0];
  for(int i = 0; i < (int)ypoints.size(); i++){
    if(ypoints[i] < min){
      min = ypoints[i];
    }
  }
  return min;
}

void Poly::addEdgeX(int x){
  edgexpoints.push_back(x);
}

void Poly::addEdgeY(int y){
  edgeypoints.push_back(y);
}

void Poly::resetEdgePoints(){
  edgexpoints.clear();
  edgeypoints.clear();
}

void Poly::sortEdgePoints(){
  int i, j, tmpx, tmpy;
  for (i = 1; i < getNumEdgePoints(); i++){
    j = i; 
    while(j > 0 && edgeypoints[j - 1] > edgeypoints[j]){
      tmpx = edgexpoints[j];
      tmpy = edgeypoints[j];
      edgexpoints[j] = edgexpoints[j - 1];
      edgeypoints[j] = edgeypoints[j - 1];
      edgexpoints[j - 1] = tmpx;
      edgeypoints[j - 1] = tmpy;
      j--;
    }
  }

  int low = 0, high = 0;
  while(low < getNumEdgePoints()){
    high++;
    if(edgeypoints[high] != edgeypoints[high -1]){
      for (i = low; i < high; i++){
        j = i; 
        while(j > low && edgexpoints[j - 1] > edgexpoints[j]){
          tmpx = edgexpoints[j];
          tmpy = edgeypoints[j];
          edgexpoints[j] = edgexpoints[j - 1];
          edgeypoints[j] = edgeypoints[j - 1];
          edgexpoints[j - 1] = tmpx;
          edgeypoints[j - 1] = tmpy;
          j--;
        }
      }
      low = high;
    }
  }
}

int Poly::getNumEdgePoints(){
  return edgexpoints.size();
}

int Poly::getEdgeXPoint(int i){
  return edgexpoints[i];
}

int Poly::getEdgeYPoint(int i){
  return edgeypoints[i];
}

void Poly::turnOnRasterization(){
  israsterized = true;
}

bool Poly::getIsRasterized(){
  return israsterized;
}

