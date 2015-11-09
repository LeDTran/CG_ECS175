#include "Face.h"

Face::Face(){
	//ctr
}

Face::Face(vector<int> xs, vector<int> ys, bool rasterizationstate){
	xpoints = xs;
	ypoints = ys;
  israsterized = rasterizationstate;
}

int Face::getXPoint(int i){
  return xpoints[i];
}

int Face::getYPoint(int i){
  return ypoints[i];
}

int Face::getNumPoints(){
  return xpoints.size();
}

int Face::getCentroidX(){
  int x = 0;
  for(int i = 0; i < getNumPoints(); i++){
    x = x + xpoints[i];
  }
  return round(x/getNumPoints());
}

int Face::getCentroidY(){
  int y = 0;
  for(int i = 0; i < getNumPoints(); i++){
    y = y + ypoints[i];
  }
  return round(y/getNumPoints());
}

void Face::translatePoly(int dx, int dy){
  for(int i = 0; i < getNumPoints(); i++){
    xpoints[i] = xpoints[i] + dx;
    ypoints[i] = ypoints[i] + dy;
  }
}

void Face::scalePoly(float sx, float sy){
  for(int i = 0; i < getNumPoints(); i++){
    xpoints[i] = round((float)xpoints[i] * sx);
    ypoints[i] = round((float)ypoints[i] * sy);
  }
}

void Face::rotatePoly(int deg){
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

int Face::getLocalMaxY(){
  int max = ypoints[0];
  for(int i = 0; i < (int)ypoints.size(); i++){
    if(ypoints[i] > max){
      max = ypoints[i];
    }
  }
  return max;
}

int Face::getLocalMinY(){
  int min = ypoints[0];
  for(int i = 0; i < (int)ypoints.size(); i++){
    if(ypoints[i] < min){
      min = ypoints[i];
    }
  }
  return min;
}

void Face::addEdgeX(int x){
  edgexpoints.push_back(x);
}

void Face::addEdgeY(int y){
  edgeypoints.push_back(y);
}

void Face::resetEdgePoints(){
  edgexpoints.clear();
  edgeypoints.clear();
}

void Face::sortEdgePoints(){
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

int Face::getNumEdgePoints(){
  return edgexpoints.size();
}

int Face::getEdgeXPoint(int i){
  return edgexpoints[i];
}

int Face::getEdgeYPoint(int i){
  return edgeypoints[i];
}

void Face::turnOnRasterization(){
  israsterized = true;
}

bool Face::getIsRasterized(){
  return israsterized;
}

