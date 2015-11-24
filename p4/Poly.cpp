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

//rotate into xy plane using x axis rotation
void Poly::rotateIntoXYPlane(float adj, float opp, float hyp){
  float xNew;
  float yNew;
  float zNew;
  //float radian =  deg * M_PI  / 180.0;
  for(int i = 0; i < getNumPoints(); i++){
    xNew = 1*xpoints[i] + 0*ypoints[i] + 0*zpoints[i];
    yNew = 0*xpoints[i] + (adj/hyp)*ypoints[i] - (opp/hyp)*zpoints[i];
    zNew = 0*xpoints[i] + (opp/hyp)*ypoints[i] + (adj/hyp)*zpoints[i];

    xpoints[i] = xNew;
    ypoints[i] = yNew;
    zpoints[i] = zNew;
  }
}

void Poly::rotateOutOfXYPlane(float adj, float opp, float hyp){
  float xNew;
  float yNew;
  float zNew;
  //float radian =  deg * M_PI  / 180.0;
  for(int i = 0; i < getNumPoints(); i++){
    xNew = 1*xpoints[i] + 0*ypoints[i] + 0*zpoints[i];
    yNew = 0*xpoints[i] + (adj/hyp)*ypoints[i] + (opp/hyp)*zpoints[i];
    zNew = 0*xpoints[i] - (opp/hyp)*ypoints[i] + (adj/hyp)*zpoints[i];

    xpoints[i] = xNew;
    ypoints[i] = yNew;
    zpoints[i] = zNew;
  }
}

//rotate into z axis using y axis rotation; into needs a negative rotation, bc rhr for y axis
void Poly::rotateIntoZAxis(float adj, float opp, float hyp){
  float xNew;
  float yNew;
  float zNew;
  //float radian =  deg * M_PI  / 180.0;
  for(int i = 0; i < getNumPoints(); i++){
    xNew = (adj/hyp)*xpoints[i] + 0*ypoints[i] - (opp/hyp)*zpoints[i];
    yNew = 0*xpoints[i] + 1*ypoints[i] + 0*zpoints[i];
    zNew = (opp/hyp)*xpoints[i] + 0*ypoints[i] + (adj/hyp)*zpoints[i];

    xpoints[i] = xNew;
    ypoints[i] = yNew;
    zpoints[i] = zNew;
  }
} 

void Poly::rotateOutOfZAxis(float adj, float opp, float hyp){
  float xNew;
  float yNew;
  float zNew;
  //float radian =  deg * M_PI  / 180.0;
  for(int i = 0; i < getNumPoints(); i++){
    xNew = (adj/hyp)*xpoints[i] + 0*ypoints[i] + (opp/hyp)*zpoints[i];
    yNew = 0*xpoints[i] + 1*ypoints[i] + 0*zpoints[i];
    zNew = -(opp/hyp)*xpoints[i] + 0*ypoints[i] + (adj/hyp)*zpoints[i];

    xpoints[i] = xNew;
    ypoints[i] = yNew;
    zpoints[i] = zNew;
  }
}