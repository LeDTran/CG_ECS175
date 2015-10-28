#include "Poly.h"

Poly::Poly(){
	//ctr
}

Poly::Poly(vector<float> xs, vector<float> ys, vector<float> zs, vector<int> p1, vector<int> p2){
	xpoints = xs;
	ypoints = ys;
  zpoints = zs;

  linep1 = p1;
  linep2 = p2;
  //israsterized = rasterizationstate;
}

float Poly::getXPoint(int i){
  return xpoints[i];
}

float Poly::getYPoint(int i){
  return ypoints[i];
}

float Poly::getZPoint(int i){
  return zpoints[i];
}

float Poly::getNumPoints(){
  // cout << "INSIDE NUM POINTS" << endl;
  // cout << "size: " << xpoints.size() << endl;
  return xpoints.size();
}

int Poly::getLineP1(int i){
  return linep1[i];
}

int Poly::getLineP2(int i){
  return linep2[i];
}

int Poly::getNumLineP(){
  return linep1.size();
}

float Poly::getCentroidX(){
  float x = 0;
  for(int i = 0; i < getNumPoints(); i++){
    x = x + xpoints[i];
  }
  return x/getNumPoints();
}

float Poly::getCentroidY(){
  float y = 0;
  for(int i = 0; i < getNumPoints(); i++){
    y = y + ypoints[i];
  }
  return y/getNumPoints();
}

float Poly::getCentroidZ(){
  float z = 0;
  for(int i = 0; i < getNumPoints(); i++){
    z = z + zpoints[i];
  }
  return z/getNumPoints();
}

void Poly::translatePoly(float dx, float dy, float dz){
  for(int i = 0; i < getNumPoints(); i++){
    xpoints[i] = xpoints[i] + dx;
    ypoints[i] = ypoints[i] + dy;
    zpoints[i] = zpoints[i] + dz;
  }
}

void Poly::scalePoly(float sx, float sy, float sz){
  for(int i = 0; i < getNumPoints(); i++){
    xpoints[i] = xpoints[i] * sx;
    ypoints[i] = ypoints[i] * sy;
    zpoints[i] = zpoints[i] * sz;
  }
}

void Poly::rotatePolyXAxis(float deg){
  float xNew;
  float yNew;
  float zNew;
  //float radian =  deg * M_PI  / 180.0;
  for(int i = 0; i < getNumPoints(); i++){
    xNew = 1*xpoints[i] + 0*ypoints[i] + 0*zpoints[i];
    yNew = 0*xpoints[i] + cos(deg*M_PI/180.0)*ypoints[i] - sin(deg*M_PI/180.0)*zpoints[i];
    zNew = 0*xpoints[i] + sin(deg*M_PI/180.0)*ypoints[i] + cos(deg*M_PI/180.0)*zpoints[i];

    xpoints[i] = xNew;
    ypoints[i] = yNew;
    zpoints[i] = zNew;
  }
}

void Poly::rotatePolyYAxis(float deg){
  cout << "ROTATING Y BY " << deg << " DEGREES" << endl;;
  float xNew;
  float yNew;
  float zNew;
  //float radian =  deg * M_PI  / 180.0;
  for(int i = 0; i < getNumPoints(); i++){
    xNew = cos(deg*M_PI/180.0)*xpoints[i] + 0*ypoints[i] + sin(deg*M_PI/180.0)*zpoints[i];
    yNew = 0*xpoints[i] + 1*ypoints[i] + 0*zpoints[i];
    zNew = -sin(deg*M_PI/180.0)*xpoints[i] + 0*ypoints[i] + cos(deg*M_PI/180.0)*zpoints[i];

    xpoints[i] = xNew;
    ypoints[i] = yNew;
    zpoints[i] = zNew;
  }
}

void Poly::rotatePolyZAxis(float deg){
  float xNew;
  float yNew;
  float zNew;
  //float radian =  deg * M_PI  / 180.0;
  for(int i = 0; i < getNumPoints(); i++){
    xNew = cos(deg*M_PI/180.0)*xpoints[i] - sin(deg*M_PI/180.0)*ypoints[i] + 0*zpoints[i];
    yNew = sin(deg*M_PI/180.0)*xpoints[i] + cos(deg*M_PI/180.0)*ypoints[i] + 0*zpoints[i];
    zNew = 0*xpoints[i] + 0*ypoints[i] + 1*zpoints[i];

    xpoints[i] = xNew;
    ypoints[i] = yNew;
    zpoints[i] = zNew;
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

// void Poly::turnOnRasterization(){
//   israsterized = true;
// }

// bool Poly::getIsRasterized(){
//   return israsterized;
// }

