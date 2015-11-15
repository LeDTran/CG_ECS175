#include "Poly.h"

Poly::Poly(){
	//ctr
}

//Polyhedron
Poly::Poly(vector<float> xs, vector<float> ys, vector<float> zs, 
            vector<int> lp1, vector<int> lp2, 
            vector<int> fp1, vector<int> fp2, vector<int> fp3,
            vector<float> fnx, vector<float> fny, vector<float> fnz){
  

  //THESE ARE NOT TOUCHED ONCE FED IN
  //all points of poly
	xpoints = xs;
	ypoints = ys;
  zpoints = zs;
  //edges of poly 
  linep1 = lp1;
  linep2 = lp2;

  //THESE ARE SUBJECT TO SORTING LATER
  //*triangular* faces of poly point1, point2, point3
  facep1 = fp1;
  facep2 = fp2;
  facep3 = fp3;
  //normal for each surface
  fnormx = fnx;
  fnormy = fny;
  fnormz = fnz;

  //get smallest x, y, z, for later poly sorting
  determineSmallest();

  //israsterized = rasterizationstate;
}


void Poly::printData(){
  // cout << "xyz" << endl;
  // for(int i = 0; i < (int)xpoints.size(); i++){
  //   cout << xpoints[i] << " " << ypoints[i] << " " << zpoints[i] << endl;
  // }

  // cout << "line points" << endl;
  // for(int i = 0; i < (int)linep1.size(); i++){
  //   cout << linep1[i] + 1 << " " << linep2[i] + 1 << endl;
  // }

  // cout << "face points" << endl;
  // for(int i = 0; i < (int)facep1.size(); i++){
  //   cout << facep1[i] + 1 << " " << facep2[i] + 1 << " " << facep3[i] + 1 << endl;
  // }

  // cout << "normal points" << endl;
  // for(int i = 0; i < (int)facep1.size(); i++){
  //   cout << fnormx[i] << " " << fnormy[i] << " " << fnormz[i] << " " << endl;
  // }

  // cout << "Ip" << endl;
  // for(int i = 0; i < (int)IpR.size(); i++){
  //       cout << IpR[i] << " " << IpG[i] << " " << IpB[i] << " " << endl;
  // }

  cout << "------------------------------------" << endl;
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

void Poly::determineSmallest(){
  float smallx = xpoints[0];
  for(int i = 0; i < (int)xpoints.size(); i++){
    if(xpoints[i] < smallx){
      smallx = xpoints[i];
    }
  }
  smallestx =  smallx;

  float smally = ypoints[0];
  for(int i = 0; i < (int)ypoints.size(); i++){
    if(ypoints[i] < smally){
      smally = ypoints[i];
    }
  }
  smallesty =  smally;

  float smallz = zpoints[0];
  for(int i = 0; i < (int)zpoints.size(); i++){
    if(zpoints[i] < smallz){
      smallz = zpoints[i];
    }
  }
  smallestz =  smallz;
}

float Poly::getSmallestX(){
  return smallestx;
}

float Poly::getSmallestY(){
  return smallesty;
}

float Poly::getSmallestZ(){
  return smallestz;
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

float Poly::getVertexNormalX(int j){
  //cout << "vertex num: " << j+1 << endl;
  float numadjfaces = 0;
  float normx = 0;
  for(int i = 0; i < (int)facep1.size(); i++){
    //cout << "fp1: " << facep1[i] << ", fp2: " << facep2[i] << ", fp3: " << facep3[i] << endl;
    if(facep1[i] == j || facep2[i] == j || facep3[i] == j){
      //cout << facep1[i] + 1 << " " << facep2[i] + 1 << " " << facep3[i] + 1 << endl;
      normx = normx + fnormx[i];
      numadjfaces++;
    }
  }
  //cout << "normx: " << normx << endl;
  return normx/numadjfaces;
}

float Poly::getVertexNormalY(int j){
  //cout << "vertex num: " << j+1 << endl;
  float numadjfaces = 0;
  float normy = 0;
  for(int i = 0; i < (int)facep1.size(); i++){
    //cout << "fp1: " << facep1[i] << ", fp2: " << facep2[i] << ", fp3: " << facep3[i] << endl;
    if(facep1[i] == j || facep2[i] == j || facep3[i] == j){
      //cout << facep1[i] + 1 << " " << facep2[i] + 1 << " " << facep3[i] + 1 << endl;
      normy = normy + fnormy[i];
      numadjfaces++;
    }
  }
  //cout << "normy: " << normy << endl;
  return normy/numadjfaces;
}
float Poly::getVertexNormalZ(int j){
  //cout << "vertex num: " << j+1 << endl;
  float numadjfaces = 0;
  float normz = 0;
  for(int i = 0; i < (int)facep1.size(); i++){
    //cout << "fp1: " << facep1[i] << ", fp2: " << facep2[i] << ", fp3: " << facep3[i] << endl;
    if(facep1[i] == j || facep2[i] == j || facep3[i] == j){
      //cout << facep1[i] + 1 << " " << facep2[i] + 1 << " " << facep3[i] + 1 << endl;
      //cout << "fnormz[i]: " << fnormz[i] << endl;
      normz = normz + fnormz[i];
      numadjfaces++;
    }
  }
  //cout << "normz: " << normz << endl;
  return normz/numadjfaces;
}

int Poly::getNumFaces(){
  return facep1.size();
}

//int plane: 0 = xy, 1 = xz, 2 = yz
void Poly::reSortFaces(int plane){
  int counter = 0;
  //xy display view
  //sort by z points
  if(plane == 0){
    while(counter < (int)facep1.size()){
      for(int i = 0; i < (int)facep1.size()-1; i++){
        //compare avg x values of face
        float avg1, avg2;
        avg1 = (zpoints[facep1[i]] + zpoints[facep2[i]] + zpoints[facep3[i]]) / 3;
        avg2 = (zpoints[facep1[i+1]] + zpoints[facep2[i+1]] + zpoints[facep3[i+1]]) / 3;
        if(avg1 > avg2){
          //swap faces by avg depth
          iter_swap(facep1.begin()+i, facep1.begin()+(i+1));
          iter_swap(facep2.begin()+i, facep2.begin()+(i+1));
          iter_swap(facep3.begin()+i, facep3.begin()+(i+1));

          //swap face normals accordingly
          iter_swap(fnormx.begin()+i, fnormx.begin()+(i+1));
          iter_swap(fnormy.begin()+i, fnormy.begin()+(i+1));
          iter_swap(fnormz.begin()+i, fnormz.begin()+(i+1));
        }
      }
      counter++; 
    }
  }
  //xz display
  //sort by y points
  else if(plane == 1){
    while(counter < (int)facep1.size()){
      for(int i = 0; i < (int)facep1.size()-1; i++){
        //compare avg y values of face
        float avg1, avg2;
        avg1 = (ypoints[facep1[i]] + ypoints[facep2[i]] + ypoints[facep3[i]]) / 3;
        avg2 = (ypoints[facep1[i+1]] + ypoints[facep2[i+1]] + ypoints[facep3[i+1]]) / 3;
        if(avg1 > avg2){
          //swap faces by avg depth
          iter_swap(facep1.begin()+i, facep1.begin()+(i+1));
          iter_swap(facep2.begin()+i, facep2.begin()+(i+1));
          iter_swap(facep3.begin()+i, facep3.begin()+(i+1));

          //swap face normals accordingly
          iter_swap(fnormx.begin()+i, fnormx.begin()+(i+1));
          iter_swap(fnormy.begin()+i, fnormy.begin()+(i+1));
          iter_swap(fnormz.begin()+i, fnormz.begin()+(i+1));
        }
      }
      counter++; 
    }
  }
  //yz display
  //sort by x points
  else if(plane == 2){
    while(counter < (int)facep1.size()){
      for(int i = 0; i < (int)facep1.size()-1; i++){
        //compare avg x values of face
        float avg1, avg2;
        avg1 = (xpoints[facep1[i]] + xpoints[facep2[i]] + xpoints[facep3[i]]) / 3;
        avg2 = (xpoints[facep1[i+1]] + xpoints[facep2[i+1]] + xpoints[facep3[i+1]]) / 3;
        if(avg1 > avg2){
          //swap faces by avg depth
          iter_swap(facep1.begin()+i, facep1.begin()+(i+1));
          iter_swap(facep2.begin()+i, facep2.begin()+(i+1));
          iter_swap(facep3.begin()+i, facep3.begin()+(i+1));

          //swap face normals accordingly
          iter_swap(fnormx.begin()+i, fnormx.begin()+(i+1));
          iter_swap(fnormy.begin()+i, fnormy.begin()+(i+1));
          iter_swap(fnormz.begin()+i, fnormz.begin()+(i+1));
        }
      }
      counter++; 
    }
  }
}

void Poly::setIp(vector<float> ipr, vector<float>ipg, vector<float> ipb){
  IpR.clear();
  IpG.clear();
  IpB.clear();
  IpR = ipr;
  IpG = ipg;
  IpB = ipb;
}

//int plane: 0=xy, 1=xz, 2=yz
void Poly::reMakeFaces(int plane){
  //cout << "MAKING FACES" << endl;
  polyFaces.clear();
  //need pass in ab points, face p1, point intensities
  if(plane == 0){
    //need to load in face points in terms of xy
      vector<float> xs;
      vector<float> ys;

      vector<float> ipr;
      vector<float> ipg;
      vector<float> ipb;

    for(int i = 0; i < (int)facep1.size(); i++){
      xs.clear();
      ys.clear();
      ipr.clear();
      ipg.clear();
      ipb.clear();

      //load in points of each face
      xs.push_back(xpoints[facep1[i]]);
      ys.push_back(ypoints[facep1[i]]);
      xs.push_back(xpoints[facep2[i]]);
      ys.push_back(ypoints[facep2[i]]);
      xs.push_back(xpoints[facep3[i]]);
      ys.push_back(ypoints[facep3[i]]);

      //load in intensity values of face points
      ipr.push_back(IpR[facep1[i]]);
      ipg.push_back(IpG[facep1[i]]);
      ipb.push_back(IpB[facep1[i]]);


      Face * myFace = new Face(xs, ys, ipr, ipg, ipb); 
      polyFaces.push_back(myFace);
    }
  }
  else if (plane == 1){
  }
  else if (plane == 2){
  }
}

Face* Poly::getFace(int i){
    return polyFaces[i];
}