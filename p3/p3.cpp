#include "p3.h"
//Sub windows demonstration

//More pixel buffers!!
float *PixelBuffer;
float* BufferXY;
float* BufferXZ;
float* BufferYZ;

float XMIN, XMAX, YMIN, YMAX, ZMIN, ZMAX;
float MASTERMIN, MASTERMAX;

int Win1, Win2, Win3;

vector<Poly *> allPoly;
bool isAnimating;

//light source position xyz
float LightPX, LightPY, LightPZ;
//viewing position xyz
float ViewPX, ViewPY, ViewPZ;
//ambient, diffuse, specular reflection coefficient: [RGB]
//range [0, 1]
float Ka[3], Kd[3], Ks[3];
//ambient light intensity, light source intensity
//range [0,1]
float IA[3], IL[3];
//Phong constant
float PhongConst;
//average distance between scene and light source
float C;

float MAXIp;

void drawPix(float *Buffer, int x, int y, float red, float green, float blue){
  if(0 <= x && x <= 300 && 0 <= y && y <= 300){
    int pixnum = x + y*300;
    //R
    Buffer[0 + pixnum*3] = red;
    //G
    Buffer[1 + pixnum*3] = green;
    //B
    Buffer[2 + pixnum*3] = blue;
  }
}

//main display loop, this function will be called again and again by OpenGL
void display()
{
  //Misc.
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  //draws pixel on screen, width and height must match pixel buffer dimension
  glDrawPixels(300, 300, GL_RGB, GL_FLOAT, PixelBuffer);

  //window refresh
  //glEnd();
  glFlush();
}

//additional display function for subwindows
void display1()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawPixels(300, 300, GL_RGB, GL_FLOAT, BufferXY);
  glFlush();
}

void display2()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawPixels(300, 300, GL_RGB, GL_FLOAT, BufferXZ);
  glFlush();
}

void display3()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawPixels(300, 300, GL_RGB, GL_FLOAT, BufferYZ);
  glFlush();
}

float getXMin(){
  if((int) allPoly.size() > 0){
    float x = allPoly[0]->getXPoint(0);
    //for each poly
    for(int i = 0; i < (int)allPoly.size(); i++){
      //for each point in that poly
      for(int j = 0; j < allPoly[i]->getNumPoints(); j++){
        if(allPoly[i]->getXPoint(j) < x){
          x = allPoly[i]->getXPoint(j);
        }
      }
    }
    return x;
  }
  return 0;
}

float getXMax(){
  if((int) allPoly.size() > 0){
    float x = allPoly[0]->getXPoint(0);
    //for each poly
    for(int i = 0; i < (int)allPoly.size(); i++){
      //for each point in that poly
      for(int j = 0; j < allPoly[i]->getNumPoints(); j++){
        if(allPoly[i]->getXPoint(j) > x){
          x = allPoly[i]->getXPoint(j);
        }
      }
    }
    return x;
  }
  return 0;
}

float getYMin(){
  if((int) allPoly.size() > 0){
    float y = allPoly[0]->getYPoint(0);
    //for each poly
    for(int i = 0; i < (int)allPoly.size(); i++){
      //for each point in that poly
      for(int j = 0; j < allPoly[i]->getNumPoints(); j++){
        if(allPoly[i]->getYPoint(j) < y){
          y = allPoly[i]->getYPoint(j);
        }
      }
    }
    return y;
  }
  return 0;  
}

float getYMax(){
  if((int) allPoly.size() > 0){
    float y = allPoly[0]->getYPoint(0);
    //for each poly
    for(int i = 0; i < (int)allPoly.size(); i++){
      //for each point in that poly
      for(int j = 0; j < allPoly[i]->getNumPoints(); j++){
        if(allPoly[i]->getYPoint(j) > y){
          y = allPoly[i]->getYPoint(j);
        }
      }
    }
    return y;
  }
  return 0;  
}

float getZMin(){
  if((int) allPoly.size() > 0){
    float z = allPoly[0]->getZPoint(0);
    //for each poly
    for(int i = 0; i < (int)allPoly.size(); i++){
      //for each point in that poly
      for(int j = 0; j < allPoly[i]->getNumPoints(); j++){
        if(allPoly[i]->getZPoint(j) < z){
          z = allPoly[i]->getZPoint(j);
        }
      }
    }
    return z;
  }
  return 0;  
}

float getZMax(){
  if((int) allPoly.size() > 0){
    float z = allPoly[0]->getZPoint(0);
    //for each poly
    for(int i = 0; i < (int)allPoly.size(); i++){
      //for each point in that poly
      for(int j = 0; j < allPoly[i]->getNumPoints(); j++){
        if(allPoly[i]->getZPoint(j) > z){
          z = allPoly[i]->getZPoint(j);
        }
      }
    }
    return z;
  }    
  return 0;
}

void updateMinMax(){
  XMIN = getXMin();
  XMAX = getXMax();
  YMIN = getYMin();
  YMAX = getYMax();
  ZMIN = getZMin();
  ZMAX = getZMax();

  float mastermin = XMIN;
  float mastermax = XMAX;

  if(YMIN < mastermin){
    mastermin = YMIN;
  }
  if(ZMIN < mastermin){
    mastermin = ZMIN;
  }

  if(YMAX > mastermax){
    mastermax = YMAX;
  }
  if(ZMAX > mastermax){
    mastermax = ZMAX;
  }

  MASTERMIN = mastermin;
  MASTERMAX = mastermax;
}

float getRatio(float coord, char axis){
  float ratio, newcoord;
  if(axis == 'x'){
    ratio = (coord - XMIN) / (MASTERMAX - MASTERMIN);
    newcoord = 299*ratio;
    return newcoord;
  }
  if(axis == 'y'){
    ratio = (coord - YMIN) / (MASTERMAX - MASTERMIN);
    newcoord = 299*ratio;
    return newcoord;
  }
  if(axis == 'z'){
    ratio = (coord - ZMIN) / (MASTERMAX - MASTERMIN);
    newcoord = 299*ratio;
    return newcoord;
  }
  return coord;
}

void drawLineDDA(float *Buffer, float * fp1, float *fp2, float r, float g, float b){//, bool ispoly, int p){

  //convert float points to int points
  int p1[2], p2[2];
  p1[0] = (int)round(fp1[0]);
  p1[1] = (int)round(fp1[1]);
  p2[0] = (int)round(fp2[0]);
  p2[1] = (int)round(fp2[1]);

  //reorder as p1 = left point, p2 = right point
  if(p1[0] > p2[0]){
    float temp[2];
    temp[0] = p1[0];
    temp[1] = p1[1];

    p1[0] = p2[0];
    p1[1] = p2[1];

    p2[0] = temp[0];
    p2[1] = temp[1];
  }

  float dy = p2[1] - p1[1];
  float dx = p2[0] - p1[0]; 
  int x, y;
  int point[2];

  //0 < slope < 1
  if(0 <= fabs(dy/dx) && fabs(dy/dx) <= 1){
    x = p1[0];
    int y0 = p1[1];
    for(int i = 0; i <= dx; i++){
      y = round(y0 + (dy/dx)*i); 
      point[0] = x;
      point[1] = y;
      drawPix(Buffer, point[0], point[1], r, g, b);
      x = x + 1;
    }
  }
  //slope > 1 
  else if(fabs(dy/dx) > 1 || fabs(dx) == 0){
    int x0 = p1[0];
    y = p1[1];
    for(int i = 0; i <= fabs(dy); i++){
      if(dy > 1){
        x = x0 + (dx/dy)*i;
      }
      if(dy < 1){
        x = x0 - (dx/dy)*i;
      }
      point[0] = x;
      point[1] = y;
      drawPix(Buffer, point[0], point[1], r, g, b);
      if(dy > 1){
        y = y + 1;
      }
      else{
        y = y - 1;
      }
    }
  }  
}

//int plane: 0 = xy, 1 = xz, 2 = yz
void drawPolygon(int p, int plane){
  //need sort faces of poly
  //allPoly[p]->reSortFaces(plane);

  for(int i = 0; i < allPoly[p]->getNumLineP(); i++){
    int linepoint1 = allPoly[p]->getLineP1(i);
    int linepoint2 = allPoly[p]->getLineP2(i);

    //get coords1 xyz1
    float lpoint1[3];
    lpoint1[0] = allPoly[p]->getXPoint(linepoint1);
    lpoint1[1] = allPoly[p]->getYPoint(linepoint1);
    lpoint1[2] = allPoly[p]->getZPoint(linepoint1);

    //get coords2 xyz2
    float lpoint2[3];
    lpoint2[0] = allPoly[p]->getXPoint(linepoint2);
    lpoint2[1] = allPoly[p]->getYPoint(linepoint2);
    lpoint2[2] = allPoly[p]->getZPoint(linepoint2);

    float point1[2];
    float point2[2];

    //plot XY
    if(plane == 0){
      point1[0] = getRatio(lpoint1[0], 'x');
      point1[1] = getRatio(lpoint1[1], 'y');
      point2[0] = getRatio(lpoint2[0], 'x');
      point2[1] = getRatio(lpoint2[1], 'y');
      drawLineDDA(BufferXY, point1, point2, 1, 0, 0);
    }
    //plot XZ
    else if(plane == 1){
      point1[0] = getRatio(lpoint1[0], 'x');
      point1[1] = getRatio(lpoint1[2], 'z');
      point2[0] = getRatio(lpoint2[0], 'x');
      point2[1] = getRatio(lpoint2[2], 'z');   
      drawLineDDA(BufferXZ, point1, point2, 0, 1, 0);
    }
    //plot YZ
    else if(plane == 2){
      point1[0] = getRatio(lpoint1[1], 'y');
      point1[1] = getRatio(lpoint1[2], 'z');
      point2[0] = getRatio(lpoint2[1], 'y');
      point2[1] = getRatio(lpoint2[2], 'z');
      drawLineDDA(BufferYZ, point1, point2, 0, 0, 1);
    }
  }
}

//translate poly given change in x and change in y
void translatePolygon(int p, float dx, float dy, float dz){
  allPoly[p]->translatePoly(dx, dy, dz);
}

//scale poly given x scalar and y scalar
void scalePolygon(int p, float sx, float sy, float sz){
  float cx = allPoly[p]->getCentroidX();
  float cy = allPoly[p]->getCentroidY();
  float cz = allPoly[p]->getCentroidZ();
  allPoly[p]->translatePoly(-cx, -cy, -cz);
  allPoly[p]->scalePoly(sx, sy, sz);
  allPoly[p]->translatePoly(cx, cy, cz);
}

void rotatePolygon(int p, float x1, float y1, float z1, float x2, float y2, float z2, float pdeg){
  //check if rotation axis is one of xyz axis
  //if x axis rotation
  if((y1 == 0 && y2 == 0) && (z1 == 0 && z2 == 0)){
    //cout << "X AXIS" << endl;
    allPoly[p]->rotatePolyXAxis(pdeg);
  }
  //if y axis rotation
  else if((x1 == 0 && x2 == 0) && (z1 == 0 && z2 == 0)){
    //cout << "Y AXIS" << endl;
    allPoly[p]->rotatePolyYAxis(pdeg);
  }
  //if z axis rotation
  else if((x1 == 0 && x2 == 0) && (y1 == 0 && y2 == 0)){
    //cout << "Z AXIS" << endl;
    allPoly[p]->rotatePolyZAxis(pdeg);
  }
  //if axis given is just a single point, then do nothing
  else if((x1 == x2) && (y1 == y2) && (z1 == z2)){
  }
  //if arbitrary axis rotation
  else{
    //translate rotation axis through origin
    x2 = x2 - x1;
    y2 = y2 - y1;
    z2 = z2 - z1;
    allPoly[p]->translatePoly(-x1, -y1, -z1);

    //rotate into xz-plane
    float a = z2;
    float o = y2;
    float hyp = sqrt(pow(z2, 2) + pow(y2, 2));
    allPoly[p]->rotateIntoXYPlane(a, o, hyp);

    float nx2, ny2, nz2;
    nx2 = 1*x2 + 0*y2 + 0*z2;
    ny2 = 0*x2 + (a/hyp)*y2 - (o/hyp)*z2;
    nz2 = 0*x2 + (o/hyp)*y2 + (a/hyp)*z2;

    a = nz2;
    o = nx2;
    hyp = sqrt(pow(nz2, 2) + pow(nx2, 2));
    allPoly[p]->rotateIntoZAxis(a, o, hyp);

    allPoly[p]->rotatePolyZAxis(pdeg);

    a = nz2;
    o = nx2;
    hyp = sqrt(pow(nz2, 2) + pow(nx2, 2));
    allPoly[p]->rotateOutOfZAxis(a, o, hyp);

    a = z2;
    o = y2;    
    hyp = sqrt(pow(z2, 2) + pow(y2, 2));
    allPoly[p]->rotateOutOfXYPlane(a, o, hyp);

    allPoly[p]->translatePoly(x1, y1, z1);
  }
}

//int plane: 0 = xy, 1 = xz, 2 = yz
void reSortPolys(int plane){
  int counter = 0;
  //xy display view
  //sort by z points
  if(plane == 0){
    while(counter != (int)allPoly.size()){
      for(int i = 0; i < (int)allPoly.size()-1; i++){
        if(allPoly[i]->getZPoint(i) > allPoly[i+1]->getZPoint(i+1)){
          iter_swap(allPoly.begin()+i, allPoly.begin()+(i+1));
        }
      }
      counter++;
    }
  }
  //xz display
  //sort by y points
  else if(plane == 1){
    while(counter != (int)allPoly.size()){
      for(int i = 0; i < (int)allPoly.size()-1; i++){
        if(allPoly[i]->getYPoint(i) > allPoly[i+1]->getYPoint(i+1)){
          iter_swap(allPoly.begin()+i, allPoly.begin()+(i+1));
        }
      }
      counter++;
    }
  }
  //yz display
  //sort by x points
  else if(plane == 2){
    while(counter != (int)allPoly.size()){
      for(int i = 0; i < (int)allPoly.size()-1; i++){
        if(allPoly[i]->getSmallestX() > allPoly[i+1]->getSmallestX()){
          iter_swap(allPoly.begin()+i, allPoly.begin()+(i+1));
        }
      }
      counter++;
    }
  }
}



void updateRotate(int i){ 
  if(isAnimating){
    for(int i = 0; i < (int)allPoly.size(); i++){
      rotatePolygon(i, 
      0, 0, 0, 
      100, 100, 100,
      1);
    }
    drawScene();  
    //draw rotation axis
    float point1[2];
    float point2[2];
    //plot XY
    point1[0] = getRatio(-1000, 'x');
    point1[1] = getRatio(-1000, 'y');
    point2[0] = getRatio(1000, 'x');
    point2[1] = getRatio(1000, 'y');
    drawLineDDA(BufferXY, point1, point2, 1, 0, 0);

    //plot XZ
    point1[0] = getRatio(-1000, 'x');
    point1[1] = getRatio(-1000, 'z');
    point2[0] = getRatio(1000, 'x');
    point2[1] = getRatio(1000, 'z');   
    drawLineDDA(BufferXZ, point1, point2, 0, 1, 0);

    //plot YZ
    point1[0] = getRatio(-1000, 'y');
    point1[1] = getRatio(-1000, 'z');
    point2[0] = getRatio(1000, 'y');
    point2[1] = getRatio(1000, 'z');
    drawLineDDA(BufferYZ, point1, point2, 0, 0, 1);

    glutTimerFunc(25, updateRotate, 0);
  }
}

void startAnimation(){
  glutTimerFunc(25, updateRotate, 0);
}



void readData(){
  string line;
  ifstream myfile ("save.dat");
  if (myfile.is_open()){
    while(getline(myfile, line)){
      //read in polygon
      if(line[0] == 'P'){
        //read in number of points
        int numpoints;
        getline(myfile, line);
        istringstream iss1(line);
        iss1 >> numpoints;
        //cout << "numpoints: " << numpoints << endl;

        //read in points
        float x, y, z;
        vector<float> xs;
        vector<float> ys;
        vector<float> zs;
        xs.clear();
        ys.clear();
        zs.clear();
        for(int i = 0; i < numpoints; i++){
          getline(myfile, line);
          istringstream iss2(line);
          iss2 >> x >> y >> z;
          xs.push_back(x);
          ys.push_back(y);
          zs.push_back(z);
        }

        //read in num edges
        int numedges;
        getline(myfile, line);
        istringstream iss3(line);
        iss3 >> numedges;

        //read in edge points
        int pt1, pt2;
        vector<int> lp1;
        vector<int> lp2;
        lp1.clear();
        lp2.clear();
        for(int i = 0; i < numedges; i++){
          getline(myfile, line);
          istringstream iss4(line);
          iss4 >> pt1 >> pt2;
          //edge points read in as number, need to convert to vector index
          pt1 = pt1 - 1;
          pt2 = pt2 - 1;
          lp1.push_back(pt1);
          lp2.push_back(pt2);
        }

        //read in num faces
        int numfaces;
        getline(myfile, line);
        istringstream iss5(line);
        iss5 >> numfaces;

        //read in face points
        int fpt1, fpt2, fpt3;
        vector<int> fp1;
        vector<int> fp2;
        vector<int> fp3;
        fp1.clear();
        fp2.clear();
        fp3.clear();
        for(int i = 0; i < numfaces; i++){
          getline(myfile, line);
          istringstream iss6(line);
          iss6 >> fpt1 >> fpt2 >> fpt3;
          //face points read in as number, need to convert to vector index
          //cout << "fpt1: " << fpt1 << ", fpt2: " << fpt2 << ", fpt3: " << fpt3 << endl;
          fpt1 = fpt1 - 1;
          fpt2 = fpt2 - 1;
          fpt3 = fpt3 - 1;
          fp1.push_back(fpt1);
          fp2.push_back(fpt2);
          fp3.push_back(fpt3);
        }

        float fnptx, fnpty, fnptz;
        vector<float> fnpx;
        vector<float> fnpy;
        vector<float> fnpz;
        fnpx.clear();
        fnpy.clear();
        fnpz.clear();
        //read in surface normal points
        for(int i = 0; i < numfaces; i++){
          getline(myfile, line);
          istringstream iss7(line);
          iss7 >> fnptx >> fnpty >> fnptz;
          //cout << "fnptx: " << fnptx << ", fnpty: " << fnpty << ", fnptz: " << fnptz << endl;
          fnpx.push_back(fnptx);
          fnpy.push_back(fnpty);
          fnpz.push_back(fnptz);
        }

        Poly * myPoly = new Poly(xs, ys, zs, lp1, lp2, fp1, fp2, fp3, fnpx, fnpy, fnpz); 
        allPoly.push_back(myPoly);
      }
    }
    myfile.close();
  }
}

void calculateC(){
  int numpoints = 0;
  int netdistance = 0;
  for(int i = 0; i < (int)allPoly.size(); i++){
    for(int j = 0; j < allPoly[i]->getNumPoints(); j++){
      float x, y, z;
      x = allPoly[i]->getXPoint(j);
      y = allPoly[i]->getYPoint(j);
      z = allPoly[i]->getZPoint(j);
      float magdist = sqrt(pow((LightPX - x), 2) + pow((LightPY - y), 2) + pow((LightPZ - z), 2));
      netdistance = netdistance + magdist;
      numpoints++;
    }
  }
  C = netdistance/numpoints;
}

void setValues(){
  LightPX=3;
  LightPY=3;
  LightPZ=20;

  ViewPX=12;
  ViewPY=12;
  ViewPZ=12;

  Ka[0]=0.1;
  Ka[1]=0.2;
  Ka[2]=0.3;
  Kd[0]=0.4;
  Kd[1]=0.5;
  Kd[2]=0.6;
  Ks[0]=0.7;
  Ks[1]=0.8;
  Ks[2]=0.9;

  IA[0]=0.9;
  IA[1]=0.9;
  IA[2]=0.9;
  IL[0]=0.8;
  IL[1]=0.8;
  IL[2]=0.8;

  PhongConst=3;

  calculateC();
}

//find normal of given vertex point
//i = which poly; j = which point in that poly
float phongLighting(int i, int j, float ka, float kd, float ks, float ia, float il){
  //vertex point
  float px, py, pz;
  px = allPoly[i]->getXPoint(j);
  py = allPoly[i]->getYPoint(j);
  pz = allPoly[i]->getZPoint(j);
  //cout << "px: " << px << ", py: " << py << ", pz: " << pz << endl;

  //avg distance between light source and scene
  //calculateC();

  // || f-p || 
  //f = ViewPXYZ
  //p = vertex point
  float magfp;
  magfp = sqrt(pow((ViewPX - px), 2) + pow((ViewPY - py), 2) + pow((ViewPZ - pz), 2));


  //get vertex normal ->n
  float nx, ny, nz;
  nx = allPoly[i]->getVertexNormalX(j);
  ny = allPoly[i]->getVertexNormalY(j);
  nz = allPoly[i]->getVertexNormalZ(j);
  float magn = sqrt(pow(nx, 2) + pow(ny, 2) + pow(nz, 2));
  //cout << "vnx: " << vnx << ", vny: " << vny << ", vnz: " << vnz << endl;
  nx = nx / magn;
  ny = ny / magn;
  nz = nz / magn;
  //cout << "vnx: " << vnx << ", vny: " << vny << ", vnz: " << vnz << endl;

  //normalize light vector
  float maglight  = sqrt(pow(LightPX - px, 2) + pow(LightPY - py, 2) + pow(LightPZ - pz, 2));
  float lx = LightPX / maglight;
  float ly = LightPY / maglight;
  float lz = LightPZ / maglight;

  // kd*(->l dot* ->n)
  //->l = LightPXYZ
  //->n = vertex normal
  float kdpart;
  float ldotn = lx*nx + ly*ny + lz*nz;
  kdpart = kd*ldotn;

  //get reflection normal ->r
  //->l + 2(->n dot* ->l)*->n
  float rx, ry, rz;
  rx = -lx + 2*(ldotn)*nx;
  ry = -ly + 2*(ldotn)*ny;
  rz = -lz + 2*(ldotn)*nz;
  float magr = sqrt(pow(rx, 2) + pow(ry, 2) + pow(rz, 2));
  rx = rx / magr;
  ry = ry / magr;
  rz = rz / magr;

  //normalize viewing vector
  float magview = sqrt(pow(ViewPX - px, 2) + pow(ViewPY - py, 2) + pow(ViewPZ - pz, 2));
  float vx = ViewPX / magview;
  float vy = ViewPY / magview;
  float vz = ViewPZ / magview;

  // ks*(->r dot* ->v)^n
  //->r = reflection normal
  //->v = ViewPXYZ
  //n = PhongConst
  float kspart;
  float rdotv = rx*vx + ry*vy + rz*vz;
  kspart = ks*pow(rdotv, PhongConst);

  //final calculation
  float IP;
  IP = ka*ia + (il/(magfp + C)) * (kdpart + kspart); 

  return IP;
}

void setIpValues(){
  vector<float> ipr;
  vector<float> ipg;
  vector<float> ipb;
  for(int i = 0; i < (int)allPoly.size(); i++){
    ipr.clear();
    ipg.clear();
    ipb.clear();
    for(int j = 0; j < allPoly[i]->getNumPoints(); j++){
      //phong model for given vertex of polygon
      //red
      float ir = phongLighting(i, j, Ka[0], Kd[0], Ks[0], IA[0], IL[0]);
      //green
      float ig = phongLighting(i, j, Ka[1], Kd[1], Ks[1], IA[1], IL[1]);
      //blue
      float ib = phongLighting(i, j, Ka[2], Kd[2], Ks[2], IA[2], IL[2]);
      ipr.push_back(ir);
      ipg.push_back(ig);
      ipb.push_back(ib);
    }
    allPoly[i]->setIp(ipr, ipg, ipb);
  }

  MAXIp = 0;
  for(int i = 0; i < (int)allPoly.size(); i++){
    float tempMAX = allPoly[i]->getIpMAX();
    if(tempMAX > MAXIp){
      MAXIp = tempMAX;
    }
    //allPoly[i]->printData();
  }
  //cout << "MAXIP: " << MAXIp << endl;;
}

float gouraudShading(int *p1, int *p2, int *pa, float i1, float i2){
  float dy = p2[1] - p1[1];
  float dx = p2[0] - p1[0]; 
  float ia;

  //cout << "dy/dx: " << dy/dx << endl;

  if(fabs(dy/dx) >= 1){
    //cout << "steep!" << endl;
    ia = (i1*(pa[1] - p2[1]) + i2*(p1[1] - pa[1])) / (p1[1] - p2[1]);
  }
  else if(fabs(dy/dx) < 1){
    ia = (i1*(pa[0] - p2[0]) + i2*(p1[0] - pa[0])) / (p1[0] - p2[0]);
  }

  return ia;
}

//bool isface: true = outline, false = rasterize
void drawLineFace(float *Buffer, float * fp1, float *fp2,  
                  Face* currFace, bool isFace, float *ip1, float *ip2){
  //convert float points to int points
  int p1[2], p2[2];
  p1[0] = (int)round(fp1[0]);
  p1[1] = (int)round(fp1[1]);
  p2[0] = (int)round(fp2[0]);
  p2[1] = (int)round(fp2[1]);

  //reorder as p1 = left point, p2 = right point
  if(p1[0] > p2[0]){
    float temp[2];
    temp[0] = p1[0];
    temp[1] = p1[1];

    p1[0] = p2[0];
    p1[1] = p2[1];

    p2[0] = temp[0];
    p2[1] = temp[1];

    float tmpip[3];
    tmpip[0] = ip1[0]; 
    tmpip[1] = ip1[1];
    tmpip[2] = ip1[2];

    ip1[0] = ip2[0];
    ip1[1] = ip2[1];
    ip1[2] = ip2[2];

    ip2[0] = tmpip[0];
    ip2[1] = tmpip[1];
    ip2[2] = tmpip[2];
  }

    // cout << "p1: " << p1[0] << ", " << p1[1] << ", p2: " << p2[0] << "," << p2[1] << endl;
    // cout << "ip1: " << ip1[0] << " " << ip1[1] << " " << ip1[2] << endl; 
    // cout << "ip2: " << ip2[0] << " " << ip2[1] << " " << ip2[2] << endl; 

    // cout <<  "-----------------------------------------------------------------------------" << endl;

  float dy = p2[1] - p1[1];
  float dx = p2[0] - p1[0]; 
  int x, y;
  int point[2];

  //cout << "dy/dx: " << dy/dx;

  //0 < slope < 1
  if(0 <= fabs(dy/dx) && fabs(dy/dx) <= 1){
    x = p1[0];
    int y0 = p1[1];
    for(int i = 0; i <= dx; i++){
      y = round(y0 + (dy/dx)*i); 
      point[0] = x;
      point[1] = y;
      float iar = gouraudShading(p1, p2, point, ip1[0], ip2[0]);
      float iag = gouraudShading(p1, p2, point, ip1[1], ip2[1]);
      float iab = gouraudShading(p1, p2, point, ip1[2], ip2[2]);
      //cout << "gouraud intensity: " << iar << " " <<  iag << " " << iab << endl;

      if(isFace){
        currFace->addEdgeA(point[0]);
        currFace->addEdgeB(point[1]);
        currFace->setEdgeIntensity(iar, iag, iab);
        //cout << "gouraud intensity: " << iar << " " <<  iag << " " << iab << endl;
      } 

      drawPix(Buffer, point[0], point[1], iar/MAXIp, iag/MAXIp, iab/MAXIp);
      //drawPix(Buffer, point[0], point[1], r, g, b);
      x = x + 1;
    }
  }
  //slope > 1 
  else if(fabs(dy/dx) > 1 || fabs(dx) == 0){
    int x0 = p1[0];
    y = p1[1];
    for(int i = 0; i <= fabs(dy); i++){
      if(dy > 1){
        x = x0 + (dx/dy)*i;
      }
      if(dy < 1){
        x = x0 - (dx/dy)*i;
      }
      point[0] = x;
      point[1] = y;
      float iar = gouraudShading(p1, p2, point, ip1[0], ip2[0]);
      float iag = gouraudShading(p1, p2, point, ip1[1], ip2[1]);
      float iab = gouraudShading(p1, p2, point, ip1[2], ip2[2]);
      //cout << "gouraud intensity: " << iar << " " <<  iag << " " << iab << endl;
      if(isFace){
        currFace->addEdgeA(point[0]);
        currFace->addEdgeB(point[1]);
        currFace->setEdgeIntensity(iar, iag, iab);
        //cout << "gouraud intensity: " << iar << " " <<  iag << " " << iab << endl;
      }  

      drawPix(Buffer, point[0], point[1], iar/MAXIp, iag/MAXIp, iab/MAXIp);
      //drawPix(Buffer, point[0], point[1], r, g, b);
      if(dy > 1){
        y = y + 1;
      }
      else{
        y = y - 1;
      }
    }
  }  
}


//int plane: 0=xy, 1=xz, 2=yz
void drawFace(Face* currFace, int plane){
  for(int i = 0; i < currFace->getNumPoints(); i++){
    //cout << "inside FOR" << endl;
    //get coords
    float point1[2];
    point1[0] = currFace->getAPoint(i);
    point1[1] = currFace->getBPoint(i);

    float ip1[3];
    ip1[0] = currFace->getPointIntensity(i, 0);
    ip1[1] = currFace->getPointIntensity(i, 1);
    ip1[2] = currFace->getPointIntensity(i, 2);

    //get next coord
    float point2[2];
    int j;
    if(i == (currFace->getNumPoints()) - 1){
      j = 0;
    }
    else{
      j = i + 1;
    }
    point2[0] = currFace->getAPoint(j);
    point2[1] = currFace->getBPoint(j);

    float ip2[3];
    ip2[0] = currFace->getPointIntensity(j, 0);
    ip2[1] = currFace->getPointIntensity(j, 1);
    ip2[2] = currFace->getPointIntensity(j, 2);

    //cout << point1[0] << ", " << point1[1] << " : "  << point2[0] << ", " << point2[1] << endl;

    if(plane == 0){
      //cout << "draw in XY" << endl;
      point1[0] = getRatio(point1[0], 'x');
      point1[1] = getRatio(point1[1], 'y');
      point2[0] = getRatio(point2[0], 'x');
      point2[1] = getRatio(point2[1], 'y');
      //cout << point1[0] << ", " << point1[1] << " : "  << point2[0] << ", " << point2[1] << endl;
      drawLineFace(BufferXY, point1, point2, currFace, true, ip1, ip2);
    }
    //drawLineDDA(point1, point2, true, p);
    //drawLineBresenham(point1, point2, true, p);
  }
}

//int p = which poly
//int plane: 0=xy, 1=xz, 2=yz
void rasterizeFaces(int p, int plane){
  //allPoly[p]->reMakeFaces(plane);
  //cout << "num faces: " << allPoly[p]->getNumFaces() << ", plane: " << plane << endl;


  for(int a = 0; a < allPoly[p]->getNumFaces(); a++){
    Face * currFace = new Face;
    currFace = allPoly[p]->getFace(a);
    currFace->printData();
    currFace->resetEdgePoints();
    drawFace(currFace, plane);
    currFace->sortEdgePoints();

    vector<float> apoints;
    vector<float> bpoints;
    float point1[2], point2[2];
    float ia1[3], ia2[3];
    // //cout << "front: " << currFace->getLocalMinB() << ", back: " << currFace->getLocalMaxB() << endl;;
    for(int i = (int)currFace->getLocalMinB() + 1; i < (int)currFace->getLocalMaxB(); i++){
      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_-------------------------------------------------------------------
      apoints.clear();
      bpoints.clear();
      for(int j = 0; j < currFace->getNumEdgePoints(); j++){
        if(i  == currFace->getEdgeBPoint(j)){
          apoints.push_back(currFace->getEdgeAPoint(j));
          bpoints.push_back(currFace->getEdgeBPoint(j));

          ia1[0] = currFace->getEdgeIntensity(j, 0);
          ia1[1] = currFace->getEdgeIntensity(j, 1);
          ia1[2] = currFace->getEdgeIntensity(j, 2);

          break;
        }
      }
      for(int j = currFace->getNumEdgePoints() - 1; j < currFace->getNumEdgePoints(); j--){
        if(i  == currFace->getEdgeBPoint(j)){
          apoints.push_back(currFace->getEdgeAPoint(j));
          bpoints.push_back(currFace->getEdgeBPoint(j));

          ia2[0] = currFace->getEdgeIntensity(j, 0);
          ia2[1] = currFace->getEdgeIntensity(j, 1);
          ia2[2] = currFace->getEdgeIntensity(j, 2);

          break;
        }
      }

      point1[0] = apoints[0]; 
      point1[1] = bpoints[0];
      point2[0] = apoints[1];
      point2[1] = bpoints[1];

      drawLineFace(BufferXY, point1, point2, currFace, false, ia1, ia2);      
      //drawLineDDA(point1, point2, false, 0);
      //drawLineBresenham(point1, point2, false, 0);
    }
  }
}

//used to redraw scene, with updated lines and polygons
void drawScene(){
  //clear window
  for (int i = 0; i < 300 * 300 * 3; i++){
    BufferXY[i] = 0;
    BufferXZ[i] = 0;
    BufferYZ[i] = 0;
  }

  updateMinMax();

  //sort polys by z 
  //reSortPolys(0);
  //draw all polys in xy
  for(int i = 0; i < (int) allPoly.size(); i++){
    //sort faces by z
    allPoly[i]->reSortFaces(0);
    //draw in xy
    //drawPolygon(i, 0);
    //establish faces to rasturize
    allPoly[i]->reMakeFaces(0);
    rasterizeFaces(i, 0);
    //drawPolygon(i,0);
    //allPoly[i]->printData();
  }

  // //sort polys by y
  // reSortPolys(1);
  // //draw all polys in xz
  // for(int i = 0; i < (int) allPoly.size(); i++){
  //   //sort faces by y
  //   allPoly[i]->reSortFaces(1);
  //   //draw in xz
  //   drawPolygon(i, 1);
  //   //allPoly[i]->printData();
  // }

  // //sort polys by x
  // reSortPolys(2);
  // //draw all polys in yz
  //for(int i = 0; i < (int) allPoly.size(); i++){
  //   //sort faces by x
  //  allPoly[i]->reSortFaces(2);
  //   //draw in yz
  //   drawPolygon(i, 2);
  //  allPoly[i]->printData();
  //}


  //draw borders  
  float point1[2];
  float point2[2];
  point1[0] = 299;
  point1[1] = 0;
  point2[0] = 299;
  point2[1] = 299;
  drawLineDDA(BufferXY, point1, point2, 1, 1, 1);//, true, p);
  drawLineDDA(BufferXZ, point1, point2, 1, 1, 1);
  drawLineDDA(BufferYZ, point1, point2, 1, 1, 1);
  point1[0] = 0;
  point1[1] = 0;
  point2[0] = 299;
  point2[1] = 0;
  drawLineDDA(BufferXY, point1, point2, 1, 1, 1);//, true, p);
  drawLineDDA(BufferXZ, point1, point2, 1, 1, 1);
  drawLineDDA(BufferYZ, point1, point2, 1, 1, 1);

  glutSetWindow(Win1);
  glutPostRedisplay();
  glutSetWindow(Win2);
  glutPostRedisplay();
  glutSetWindow(Win3);
  glutPostRedisplay();
}


int main(int argc, char *argv[]){

  char choice;
  cout << "Would you like to load 'save.dat? (y/n): ";
  cin >> choice;
  if(choice == 'y'){
    cout << "LOADING save.dat" << endl;
    readData();
  }
  setValues();
  setIpValues();

  //allocate new pixel buffer, need initialization!!
  //main buffer 300*300
  PixelBuffer = new float[600 * 600 * 3];
  for (int i = 0; i < 600 * 600 * 3; i++){
    PixelBuffer[i] = 0;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  //set window size to 300*300
  glutInitWindowSize(600, 600);
  //set window position
  glutInitWindowPosition(100, 100);
  PixelBuffer[0] = 0;
  PixelBuffer[1] = 0;
  PixelBuffer[2] = 0;
  //create and set main window title
  int MainWindow = glutCreateWindow("Hello Windows!!");
  glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
  //sets display function
  glutDisplayFunc(display);

  //allocate and initialize subwindow buffer
  //subwindow size 300*300
  BufferXY = new float[300 * 300 * 3];
  BufferXZ = new float[300 * 300 * 3];
  BufferYZ = new float[300 * 300 * 3];
  for(int i = 0; i < 300 * 300 * 3; i++){
    BufferXY[i] = 0;
    BufferXZ[i] = 0;
    BufferYZ[i] = 0;
  }

  //create subwindows
  //the 5 parameters are: main window ID, xpos, ypos, width, height
  //[2][3]
  //[1][x]
  Win1 = glutCreateSubWindow(MainWindow, 0, 300, 300, 300);
  glutDisplayFunc(display1);
  Win2 = glutCreateSubWindow(MainWindow, 0, 0, 300, 300);
  glutDisplayFunc(display2);
  Win3 = glutCreateSubWindow(MainWindow, 300, 0, 300, 300);
  glutDisplayFunc(display3);

  drawScene();

  createMenu();    

  //print poly data
  // for(int i = 0; i < (int)allPoly.size(); i++){
  //   allPoly[i]->printData();
  // }


  glutMainLoop();//main display loop, will display until terminate
  return 0;
}