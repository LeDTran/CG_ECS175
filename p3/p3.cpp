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
//ambient, diffuse, specular reflection coefficient 
float ka, kd, ks;
//ambient light intensity, light source intensity
float IA, IL;
//Phong constant
float PhongConst;

void drawPix(float *Buffer, int x, int y, float red, float green, float blue){
  if(0 <= x && x <= 200 && 0 <= y && y <= 200){
    int pixnum = x + y*200;
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
  glDrawPixels(200, 200, GL_RGB, GL_FLOAT, PixelBuffer);

  //window refresh
  //glEnd();
  glFlush();
}

//additional display function for subwindows
void display1()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawPixels(200, 200, GL_RGB, GL_FLOAT, BufferXY);
  glFlush();
}

void display2()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawPixels(200, 200, GL_RGB, GL_FLOAT, BufferXZ);
  glFlush();
}

void display3()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawPixels(200, 200, GL_RGB, GL_FLOAT, BufferYZ);
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
    newcoord = 199*ratio;
    return newcoord;
  }
  if(axis == 'y'){
    ratio = (coord - YMIN) / (MASTERMAX - MASTERMIN);
    newcoord = 199*ratio;
    return newcoord;
  }
  if(axis == 'z'){
    ratio = (coord - ZMIN) / (MASTERMAX - MASTERMIN);
    newcoord = 199*ratio;
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
    for(int i = 0; i <= abs(dy); i++){
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

void drawPolygon(int p){
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
    point1[0] = getRatio(lpoint1[0], 'x');
    point1[1] = getRatio(lpoint1[1], 'y');
    point2[0] = getRatio(lpoint2[0], 'x');
    point2[1] = getRatio(lpoint2[1], 'y');
    drawLineDDA(BufferXY, point1, point2, 1, 0, 0);

    //plot XZ
    point1[0] = getRatio(lpoint1[0], 'x');
    point1[1] = getRatio(lpoint1[2], 'z');
    point2[0] = getRatio(lpoint2[0], 'x');
    point2[1] = getRatio(lpoint2[2], 'z');   
    drawLineDDA(BufferXZ, point1, point2, 0, 1, 0);

    //plot YZ
    point1[0] = getRatio(lpoint1[1], 'y');
    point1[1] = getRatio(lpoint1[2], 'z');
    point2[0] = getRatio(lpoint2[1], 'y');
    point2[1] = getRatio(lpoint2[2], 'z');
    drawLineDDA(BufferYZ, point1, point2, 0, 0, 1);
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

//used to redraw scene, with updated lines and polygons
void drawScene(){
  //clear window
  for (int i = 0; i < 200 * 200 * 3; i++){
    BufferXY[i] = 0;
    BufferXZ[i] = 0;
    BufferYZ[i] = 0;
  }

  updateMinMax();

  //draw all polygons
  for(int i = 0; i < (int) allPoly.size(); i++){
    drawPolygon(i);
  }

  //draw borders  
  float point1[2];
  float point2[2];
  point1[0] = 199;
  point1[1] = 0;
  point2[0] = 199;
  point2[1] = 199;
  drawLineDDA(BufferXY, point1, point2, 1, 1, 1);//, true, p);
  drawLineDDA(BufferXZ, point1, point2, 1, 1, 1);
  drawLineDDA(BufferYZ, point1, point2, 1, 1, 1);
  point1[0] = 0;
  point1[1] = 0;
  point2[0] = 199;
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

//find normal of given vertex point
//i = which poly; j = which point in that poly
void phongLighting(int i, int j){
  //vertex point
  float px, py, pz;
  px = allPoly[i]->getXPoint(j);
  py = allPoly[i]->getYPoint(j);
  pz = allPoly[i]->getZPoint(j);
  cout << "px: " << px << ", py: " << py << ", pz: " << pz << endl;

  //avg distance between light source and scene
  float K;

  // || f-p || 
  //f = ViewPXYZ
  //p = vertex point
  float magfp;
  magfp = sqrt(pow((ViewPX - px), 2) + pow((ViewPY - py), 2) + pow((ViewPZ - pz), 2));


  //get vertex normal ->n
  float vnx, vny, vnz;
  vnx = allPoly[i]->getVertexNormalX(j);
  vny = allPoly[i]->getVertexNormalY(j);
  vnz = allPoly[i]->getVertexNormalZ(j);
  float magvn = sqrt(pow(vnx, 2) + pow(vny, 2) + pow(vnz, 2));
  cout << "vnx: " << vnx << ", vny: " << vny << ", vnz: " << vnz << endl;
  vnx = vnx / magvn;
  vny = vny / magvn;
  vnz = vnz / magvn;
  cout << "vnx: " << vnx << ", vny: " << vny << ", vnz: " << vnz << endl;

  // kd*(->l dot* ->n)
  //->l = LightPXYZ
  //->n = vertex normal
  float kdpart;
  float ldotn = LightPX*vnx + LightPY*vny + LightPZ*vnz;
  kdpart = kd*ldotn;

  //get reflection normal ->r
  //->l + 2(->n dot* ->l)*->n
  float rx, ry, rz;
  rx = LightPX + 2*(ldotn)*vnx;
  ry = LightPY + 2*(ldotn)*vny;
  rz = LightPZ + 2*(ldotn)*vnz;
  float magr = sqrt(pow(rx, 2) + pow(ry, 2) + pow(rz, 2));
  rx = rx / magr;
  ry = ry / magr;
  rz = rz / magr;


  // ks*(->r dot* ->v)^n
  //->r = reflection normal
  //->v = ViewPXYZ
  //n = PhongConst
  float kspart;
  float rdotv = rx*ViewPX + ry*ViewPY + rz*ViewPZ;
  kspart = ks*pow(rdotv, PhongConst);


  float IP;
  IP = ka*IA + (IL/(magfp + K)) * (kdpart + kspart); 
}


int main(int argc, char *argv[]){

  char choice;
  cout << "Would you like to load 'save.dat? (y/n): ";
  cin >> choice;
  if(choice == 'y'){
    cout << "LOADING save.dat" << endl;
    readData();
  }

  //allocate new pixel buffer, need initialization!!
  //main buffer 200*200
  PixelBuffer = new float[400 * 400 * 3];
  for (int i = 0; i < 400 * 400 * 3; i++){
    PixelBuffer[i] = 0;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  //set window size to 200*200
  glutInitWindowSize(400, 400);
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
  //subwindow size 200*200
  BufferXY = new float[200 * 200 * 3];
  BufferXZ = new float[200 * 200 * 3];
  BufferYZ = new float[200 * 200 * 3];
  for(int i = 0; i < 200 * 200 * 3; i++){
    BufferXY[i] = 0;
    BufferXZ[i] = 0;
    BufferYZ[i] = 0;
  }

  //create subwindows
  //the 5 parameters are: main window ID, xpos, ypos, width, height
  //[2][3]
  //[1][x]
  Win1 = glutCreateSubWindow(MainWindow, 0, 200, 200, 200);
  glutDisplayFunc(display1);
  Win2 = glutCreateSubWindow(MainWindow, 0, 0, 200, 200);
  glutDisplayFunc(display2);
  Win3 = glutCreateSubWindow(MainWindow, 200, 0, 200, 200);
  glutDisplayFunc(display3);

  drawScene();

  createMenu();     

  phongLighting(0,0);

  //print poly data
  // for(int i = 0; i < (int)allPoly.size(); i++){
  //   for(int j = 0; j < allPoly[i].getNumPoints(); j++){
  //     phongLighting(i, j);
  //   }
  // }

  //print poly data
  // for(int i = 0; i < (int)allPoly.size(); i++){
  //   allPoly[i]->printData();
  // }

  glutMainLoop();//main display loop, will display until terminate
  return 0;
}