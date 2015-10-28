#include "p2.h"
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

void drawPix(float *Buffer, int x, int y, float red, float green, float blue){
  //Pixel not drawn if outside viewing window
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

  // cout << "xmin: " << XMIN << ", xmax: " << XMAX << endl;
  // cout << "ymin: " << YMIN << ", ymax: " << YMAX << endl;
  // cout << "zmin: " << ZMIN << ", zmax: " << ZMAX << endl;

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

  //cout <<"mastermin:  " << MASTERMIN << ", mastermax: " << MASTERMAX << endl;
}

float getRatio(float coord, char axis){
  float ratio, newcoord;
  if(axis == 'x'){
    //cout << "coord: " << coord << ", xaxis: " << axis << endl;
    ratio = (coord - XMIN) / (MASTERMAX - MASTERMIN);
    newcoord = 199*ratio;
    //cout << "ratio: " << ratio << ", xnewcoord: " << newcoord << endl;
    return newcoord;
  }
  if(axis == 'y'){
    //cout << "coord: " << coord << ", yaxis: " << axis << endl;
    ratio = (coord - YMIN) / (MASTERMAX - MASTERMIN);
    newcoord = 199*ratio;
    //cout << "ratio: " << ratio << ", ynewcoord: " << newcoord << endl;
    return newcoord;
  }
  if(axis == 'z'){
    //cout << "coord: " << coord << ", zaxis: " << axis << endl;
    ratio = (coord - ZMIN) / (MASTERMAX - MASTERMIN);
    newcoord = 199*ratio;
    //cout << "ratio: " << ratio << ", znewcoord: " << newcoord << endl;
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

  // cout << "fx1: " << fp1[0] << ", fy1: " << fp1[1] << endl;
  // cout << "fx2: " << fp2[0] << ", fy2: " << fp2[1] << endl;
  // cout << "ix1: " << p1[0] << ", y1: " << p1[1] << endl;
  // cout << "ix2: " << p2[0] << ", y2: " << p2[1] << endl;
  // cout << "-------------------------" << endl;


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
      // if(ispoly){
      //   allPoly[p]->addEdgeX(point[0]);
      //   allPoly[p]->addEdgeY(point[1]);
      // }
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
      // if(ispoly){
      //   allPoly[p]->addEdgeX(point[0]);
      //   allPoly[p]->addEdgeY(point[1]);
      // }
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
  // cout << "FOR: " << allPoly[p]->getNumLineP() << endl;
  for(int i = 0; i < allPoly[p]->getNumLineP(); i++){
    int linepoint1 = allPoly[p]->getLineP1(i);
    int linepoint2 = allPoly[p]->getLineP2(i);

    // cout << "P1: " << linepoint1 << ", P2: " << linepoint2 << endl;

    //get coords1 xyz1
    float lpoint1[3];
    lpoint1[0] = allPoly[p]->getXPoint(linepoint1);
    lpoint1[1] = allPoly[p]->getYPoint(linepoint1);
    lpoint1[2] = allPoly[p]->getZPoint(linepoint1);
    // cout << "x1: " << lpoint1[0];
    // cout << ", y1: " << lpoint1[1]; 
    // cout << ", z1: " << lpoint1[2] << endl;

    //get coords2 xyz2
    float lpoint2[3];
    lpoint2[0] = allPoly[p]->getXPoint(linepoint2);
    lpoint2[1] = allPoly[p]->getYPoint(linepoint2);
    lpoint2[2] = allPoly[p]->getZPoint(linepoint2);
    // cout << "x2: " << lpoint2[0];
    // cout << ", y2: " << lpoint2[1]; 
    // cout << ", z2: " << lpoint2[2] << endl;

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

    // //plot XY
    // point1[0] = lpoint1[0];
    // point1[1] = lpoint1[1];
    // point2[0] = lpoint2[0];
    // point2[1] = lpoint2[1];
    // drawLineDDA(BufferXY, point1, point2);

    // //plot XZ
    // point1[0] = lpoint1[0];
    // point1[1] = lpoint1[2];
    // point2[0] = lpoint2[0];
    // point2[1] = lpoint2[2];   
    // drawLineDDA(BufferXZ, point1, point2);

    // //plot YZ
    // point1[0] = lpoint1[1];
    // point1[1] = lpoint1[2];
    // point2[0] = lpoint2[1];
    // point2[1] = lpoint2[2];
    // drawLineDDA(BufferYZ, point1, point2);


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
  //cout << "cx: " << cx << ", cy: " << cy << ", cz: " << cz << endl;
  allPoly[p]->translatePoly(-cx, -cy, -cz);
  allPoly[p]->scalePoly(sx, sy, sz);
  allPoly[p]->translatePoly(cx, cy, cz);
}

void rotatePolygon(int p, float x1, float y1, float z1, float x2, float y2, float z2, float pdeg){
  //draw axis
  float point1[2];
  float point2[2];
  //plot XY
  point1[0] = getRatio(x1, 'x');
  point1[1] = getRatio(y1, 'y');
  point2[0] = getRatio(x2, 'x');
  point2[1] = getRatio(y2, 'y');
  drawLineDDA(BufferXY, point1, point2, 1, 0, 0);

  //plot XZ
  point1[0] = getRatio(x1, 'x');
  point1[1] = getRatio(y1, 'z');
  point2[0] = getRatio(x2, 'x');
  point2[1] = getRatio(y2, 'z');   
  drawLineDDA(BufferXZ, point1, point2, 0, 1, 0);

  //plot YZ
  point1[0] = getRatio(y1, 'y');
  point1[1] = getRatio(z1, 'z');
  point2[0] = getRatio(y2, 'y');
  point2[1] = getRatio(z2, 'z');
  drawLineDDA(BufferYZ, point1, point2, 0, 0, 1);

  //check if rotation axis is one of xyz axis
  //if x axis rotation
  if((y1 == 0 && y2 == 0) && (z1 == 0 && z2 == 0)){
    cout << "X AXIS" << endl;
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
    //cout << "a: " << a << ", o: " << o << ", hyp: " << hyp << endl;
    allPoly[p]->rotateIntoXYPlane(a, o, hyp);

    float nx2, ny2, nz2;
    nx2 = 1*x2 + 0*y2 + 0*z2;
    ny2 = 0*x2 + (a/hyp)*y2 - (o/hyp)*z2;
    nz2 = 0*x2 + (o/hyp)*y2 + (a/hyp)*z2;

    a = nz2;
    o = nx2;
    hyp = sqrt(pow(nz2, 2) + pow(nx2, 2));
    //cout << "a2: " << a << ", o2: " << o << ", hyp2: " << hyp << endl;
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

  //XY
  //Red
  drawPix(BufferXY, 100, 100, 1, 0, 0);
  drawPix(BufferXY, 100, 99, 1, 0, 0);
  drawPix(BufferXY, 101, 100, 1, 0, 0);
  drawPix(BufferXY, 101, 99, 1, 0, 0);
  drawPix(BufferXY, 102, 100, 1, 0, 0);
  drawPix(BufferXY, 102, 99, 1, 0, 0);
  
  //XZ
  //Green
  drawPix(BufferXZ, 100, 100, 0, 1, 0);
  drawPix(BufferXZ, 100, 99, 0, 1, 0);
  drawPix(BufferXZ, 101, 100, 0, 1, 0);
  drawPix(BufferXZ, 101, 99, 0, 1, 0);
  drawPix(BufferXZ, 102, 100, 0, 1, 0);
  drawPix(BufferXZ, 102, 99, 0, 1, 0);

  //YZ
  //Blue
  drawPix(BufferYZ, 100, 100, 0, 0, 1);
  drawPix(BufferYZ, 100, 99, 0, 0, 1);
  drawPix(BufferYZ, 101, 100, 0, 0, 1);
  drawPix(BufferYZ, 101, 99, 0, 0, 1);
  drawPix(BufferYZ, 102, 100, 0, 0, 1);
  drawPix(BufferYZ, 102, 99, 0, 0, 1);

  updateMinMax();

  //draw all polygons
  for(int i = 0; i < (int) allPoly.size(); i++){

    // for(int j = 0; j < allPoly[i]->getNumPoints(); j++){
    //   cout << "x: " << allPoly[i]->getXPoint(j) << ", y: " << allPoly[i]->getYPoint(j) << ", z: " << allPoly[i]->getZPoint(j) << endl;
    // }
    // for(int j = 0; j < allPoly[i]->getNumLineP(); j++){
    //   cout << "p1: " << allPoly[i]->getLineP1(j) << ", p2: " << allPoly[i]->getLineP2(j) << endl;
    // }


    //need to reset edge points for rasterization after a transformation
    //allPoly[i]->resetEdgePoints();
    drawPolygon(i);
    //sort edges for rasterization
    //allPoly[i]->sortEdgePoints();
    //rasterize polygon if done before
    // if(allPoly[i]->getIsRasterized()){
    //   rasterizePolygon(i);
    // }
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
  for(int i = 0; i < allPoly.size(); i++){
    rotatePolygon(i, 
    0, 0, 0, 
    100, 100, 100,
    1);
  }
  drawScene();  
  glutTimerFunc(30, updateRotate, 0);
}

void startAnimation(){
  glutTimerFunc(30, updateRotate, 0);
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
          //cout << "x: " << x << ", y: " << y << ", z: " << z << endl;
          xs.push_back(x);
          ys.push_back(y);
          zs.push_back(z);
        }

        //read in num edges
        int numedges;
        getline(myfile, line);
        istringstream iss3(line);
        iss3 >> numedges;
        //cout << "numedges: " << numedges << endl;

        //read in points
        int pt1, pt2;
        vector<int> p1;
        vector<int> p2;
        p1.clear();
        p2.clear();
        for(int i = 0; i < numedges; i++){
          getline(myfile, line);
          istringstream iss4(line);
          iss4 >> pt1 >> pt2;
          //cout << "pt1: " << pt1 << ", pt2: " << pt2 << endl;
          //edge points read in as number, need to convert to vecctor index
          pt1 = pt1 - 1;
          pt2 = pt2 - 1;
          p1.push_back(pt1);
          p2.push_back(pt2);
        }

        Poly * myPoly = new Poly(xs, ys, zs, p1, p2); 
        allPoly.push_back(myPoly);
      }
      //cout << line << endl;
    }
    myfile.close();
  }
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

  // Poly * myPoly = new Poly(xs, ys, zs, p1, p2); 
  // allPoly.push_back(myPoly);

  // cout << "HEYO!!!" << endl;
  // cout << "NUM: " << allPoly[0]->getNumPoints() << endl;

  // for(int i = 0; i < (int) allPoly[0]->getNumPoints(); i++){
  //   cout << "x: " << allPoly[0]->getXPoint(i);
  //   cout << ", y: " << allPoly[0]->getYPoint(i);
  //   cout << ", z: " << allPoly[0]->getZPoint(i) << endl;
  // }
  // cout << "1--------" << endl;

  // for(int i = 0; i < (int) allPoly[1]->getNumPoints(); i++){
  //   cout << "x: " << allPoly[1]->getXPoint(i);
  //   cout << ", y: " << allPoly[1]->getYPoint(i);
  //   cout << ", z: " << allPoly[1]->getZPoint(i) << endl;
  // }
  // cout << "2--------" << endl;


  // Poly * myPoly3 = new Poly(xs, ys, zs, p1, p2); 
  // allPoly.push_back(myPoly3);
  //translatePolygon(0, 100, 100, 100);
  //translatePolygon(2, 100, 100, 100);
  // translatePolygon(1, 100, -200, 100);
  // translatePolygon(2, -200, 100, 100);
  //scalePolygon(1, 1.5, 1.5, 1.5);
  // rotatePolygon(0, 
  // 5, 0, 0, 
  // 10, 0, 0, 
  // 90);
  //rotatePolygon(1, 0, 0, 0, 100, 100, 0, 45);


  // for(int i = 0; i < (int) allPoly[1]->getNumPoints(); i++){
  //   cout << "x: " << allPoly[1]->getXPoint(i);
  //   cout << ", y: " << allPoly[1]->getYPoint(i);
  //   cout << ", z: " << allPoly[1]->getZPoint(i) << endl;
  // }
  // cout << "3--------" << endl;

  //cout << "after initial draw" << endl;

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

  startAnimation();

  glutMainLoop();//main display loop, will display until terminate
  return 0;
}