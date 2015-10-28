#include "p2.h"
//Sub windows demonstration

//More pixel buffers!!
float *PixelBuffer;
float* BufferXY;
float* BufferXZ;
float* BufferYZ;

float XMIN, XMAX, YMIN, YMAX, ZMIN, ZMAX;
float MASTERMIN, MASTERMAX;

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

  cout << "xmin: " << XMIN << ", xmax: " << XMAX << endl;
  cout << "ymin: " << YMIN << ", ymax: " << YMAX << endl;
  cout << "zmin: " << ZMIN << ", zmax: " << ZMAX << endl;

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

  cout <<"mastermin:  " << MASTERMIN << ", mastermax: " << MASTERMAX << endl;

}

float getRatio(float coord, char axis){
  float ratio, newcoord;
  //only NDC if have polygons out side 200*200 area
  if(axis == 'x'){
    //cout << "coord: " << coord << ", xaxis: " << axis << endl;
    ratio = (float)(coord - XMIN) / (float)(MASTERMAX - MASTERMIN);
    newcoord = 199*ratio;
    //cout << "ratio: " << ratio << ", xnewcoord: " << newcoord << endl;
    return newcoord;
  }
  if(axis == 'y'){
    //cout << "coord: " << coord << ", yaxis: " << axis << endl;
    ratio = (float)(coord - YMIN) / (float)(MASTERMAX - MASTERMIN);
    newcoord = 199*ratio;
    //cout << "ratio: " << ratio << ", ynewcoord: " << newcoord << endl;
    return newcoord;
  }
  if(axis == 'z'){
    //cout << "coord: " << coord << ", zaxis: " << axis << endl;
    ratio = (float)(coord - ZMIN) / (float)(MASTERMAX - MASTERMIN);
    newcoord = 199*ratio;
    //cout << "ratio: " << ratio << ", znewcoord: " << newcoord << endl;
    return newcoord;
  }
  return coord;
}

void drawLineDDA(float *Buffer, float * fp1, float *fp2){//, bool ispoly, int p){

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
      drawPix(Buffer, point[0], point[1], 1, 1, 1);
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
      drawPix(Buffer, point[0], point[1], 1, 1, 1);
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

    //get coords1 xyz
    float lpoint1[3];
    lpoint1[0] = allPoly[p]->getXPoint(linepoint1);
    lpoint1[1] = allPoly[p]->getYPoint(linepoint1);
    lpoint1[2] = allPoly[p]->getZPoint(linepoint1);
    // cout << "x1: " << lpoint1[0];
    // cout << ", y1: " << lpoint1[1]; 
    // cout << ", z1: " << lpoint1[2] << endl;

    //get coords2 xyz
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
    // point1[0] = lpoint1[0];
    // point1[1] = lpoint1[1];
    // point2[0] = lpoint2[0];
    // point2[1] = lpoint2[1];
    // int hey = getRatio(lpoint1[0], 'x');
    // hey = getRatio(lpoint1[1], 'y');
    // hey = getRatio(lpoint2[0], 'x');
    // hey = getRatio(lpoint2[1], 'y');

    point1[0] = getRatio(lpoint1[0], 'x');
    point1[1] = getRatio(lpoint1[1], 'y');
    point2[0] = getRatio(lpoint2[0], 'x');
    point2[1] = getRatio(lpoint2[1], 'y');
    drawLineDDA(BufferXY, point1, point2);

    //plot XZ
    point1[0] = getRatio(lpoint1[0], 'x');
    point1[1] = getRatio(lpoint1[2], 'z');
    point2[0] = getRatio(lpoint2[0], 'x');
    point2[1] = getRatio(lpoint2[2], 'z');   
    drawLineDDA(BufferXZ, point1, point2);

    //plot YZ
    point1[0] = getRatio(lpoint1[1], 'y');
    point1[1] = getRatio(lpoint1[2], 'z');
    point2[0] = getRatio(lpoint2[1], 'y');
    point2[1] = getRatio(lpoint2[2], 'z');
    drawLineDDA(BufferYZ, point1, point2);

    // //get next coord
    // int point2[2];
    // int j;
    // if(i == (allPoly[p]->getNumPoints()) - 1){
    //   j = 0;
    // }
    // else{
    //   j = i + 1;
    // }
    // point2[0] = allPoly[p]->getXPoint(j);
    // point2[1] = allPoly[p]->getYPoint(j);

    // drawLineDDA(point1, point2, true, p);
    // //drawLineBresenham(point1, point2, true, p);
  }
  // int point1[2];
  // int point2[2];

  // point1[0] = 0;
  // point1[1] = 200;
  // point2[0] = 200;
  // point2[1] = 200;
  // drawLineDDA(BufferXY, point1, point2);

  // point1[0] = 0;
  // point1[1] = 200;
  // point2[0] = 200;
  // point2[1] = 200;   
  // drawLineDDA(BufferXZ, point1, point2);

  // point1[0] = 0;
  // point1[1] = 200;
  // point2[0] = 200;
  // point2[1] = 200;
  // drawLineDDA(BufferYZ, point1, point2);
  // cout << "DRAWN" << endl;
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
  //check if rotation axis is one of xyz axis
  //if x axis rotation
  if((y1 == 0 && y2 == 0) && (z1 == 0 && z2 == 0)){
    cout << "X AXIS" << endl;
    allPoly[p]->rotatePolyXAxis(pdeg);
  }
  //if y axis rotation
  else if((x1 == 0 && x2 == 0) && (z1 == 0 && z2 == 0)){
    cout << "Y AXIS" << endl;
    allPoly[p]->rotatePolyYAxis(pdeg);
  }
  else if((x1 == 0 && x2 == 0) && (y1 == 0 && y2 == 0)){
    cout << "Z AXIS" << endl;
    allPoly[p]->rotatePolyZAxis(pdeg);
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
  drawLineDDA(BufferXY, point1, point2);//, true, p);
  drawLineDDA(BufferXZ, point1, point2);
  drawLineDDA(BufferYZ, point1, point2);
  point1[0] = 0;
  point1[1] = 0;
  point2[0] = 199;
  point2[1] = 0;
  drawLineDDA(BufferXY, point1, point2);//, true, p);
  drawLineDDA(BufferXZ, point1, point2);
  drawLineDDA(BufferYZ, point1, point2);
}

int main(int argc, char *argv[]){
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



  vector<float> xs;
  vector<float> ys;
  vector<float> zs;

  xs.push_back(0);
  ys.push_back(0);
  zs.push_back(0);
  xs.push_back(50);
  ys.push_back(0);
  zs.push_back(0);
  xs.push_back(0);
  ys.push_back(50);
  zs.push_back(0);
  xs.push_back(0);
  ys.push_back(0);
  zs.push_back(50);

  vector<int> p1;
  vector<int> p2;
  //point index, not point number
  p1.push_back(0);
  p2.push_back(1);
  p1.push_back(0);
  p2.push_back(2);
  p1.push_back(0);
  p2.push_back(3);
  p1.push_back(1);
  p2.push_back(2);
  p1.push_back(1);
  p2.push_back(3);
  p1.push_back(2);
  p2.push_back(3);
  
  // xs.clear();
  // ys.clear();
  // zs.clear();

  // xs.push_back(50);
  // ys.push_back(0);
  // zs.push_back(0);

  // xs.push_back(50);
  // ys.push_back(50);
  // zs.push_back(0);

  // xs.push_back(50);
  // ys.push_back(0);
  // zs.push_back(50);
  
  // xs.push_back(50);
  // ys.push_back(50);
  // zs.push_back(50);

  // xs.push_back(0);
  // ys.push_back(0);
  // zs.push_back(50);

  // xs.push_back(0);
  // ys.push_back(50);
  // zs.push_back(50);

  // xs.push_back(0);
  // ys.push_back(0);
  // zs.push_back(0);
  
  // xs.push_back(0);
  // ys.push_back(50);
  // zs.push_back(0);

  // p1.clear();
  // p2.clear();

  // p1.push_back(0);
  // p2.push_back(1);
  
  // p1.push_back(0);
  // p2.push_back(2);
  
  // p1.push_back(0);
  // p2.push_back(6);

  // p1.push_back(1);
  // p2.push_back(3);

  // p1.push_back(1);
  // p2.push_back(7);

  // p1.push_back(2);
  // p2.push_back(3);

  // p1.push_back(2);
  // p2.push_back(4);
  
  // p1.push_back(3);
  // p2.push_back(5);
  
  // p1.push_back(4);
  // p2.push_back(5);

  // p1.push_back(4);
  // p2.push_back(6);

  // p1.push_back(5);
  // p2.push_back(7);

  // p1.push_back(6);
  // p2.push_back(7);

  Poly * myPoly = new Poly(xs, ys, zs, p1, p2); 
  allPoly.push_back(myPoly);

  // cout << "HEYO!!!" << endl;
  // cout << "NUM: " << allPoly[0]->getNumPoints() << endl;

  // for(int i = 0; i < (int) allPoly[0]->getNumPoints(); i++){
  //   cout << "x: " << allPoly[0]->getXPoint(i);
  //   cout << ", y: " << allPoly[0]->getYPoint(i);
  //   cout << ", z: " << allPoly[0]->getZPoint(i) << endl;
  // }
  // cout << "1--------" << endl;

  xs.clear();
  ys.clear();
  zs.clear();
  // xs.push_back(120);
  // ys.push_back(120);
  // zs.push_back(120);
  // xs.push_back(170);
  // ys.push_back(120);
  // zs.push_back(120);
  // xs.push_back(120);
  // ys.push_back(170);
  // zs.push_back(120);
  // xs.push_back(120);
  // ys.push_back(120);
  // zs.push_back(170);

  // xs.push_back(0);
  // ys.push_back(0);
  // zs.push_back(0);
  // xs.push_back(50);
  // ys.push_back(0);
  // zs.push_back(0);
  // xs.push_back(0);
  // ys.push_back(50);
  // zs.push_back(0);
  // xs.push_back(0);
  // ys.push_back(0);
  // zs.push_back(50);

  xs.push_back(50);
  ys.push_back(0);
  zs.push_back(0);

  xs.push_back(50);
  ys.push_back(50);
  zs.push_back(0);

  xs.push_back(50);
  ys.push_back(0);
  zs.push_back(50);
  
  xs.push_back(50);
  ys.push_back(50);
  zs.push_back(50);

  xs.push_back(0);
  ys.push_back(0);
  zs.push_back(50);

  xs.push_back(0);
  ys.push_back(50);
  zs.push_back(50);

  xs.push_back(0);
  ys.push_back(0);
  zs.push_back(0);
  
  xs.push_back(0);
  ys.push_back(50);
  zs.push_back(0);

  p1.clear();
  p2.clear();


  p1.push_back(0);
  p2.push_back(1);
  
  p1.push_back(0);
  p2.push_back(2);
  
  p1.push_back(0);
  p2.push_back(6);

  p1.push_back(1);
  p2.push_back(3);

  p1.push_back(1);
  p2.push_back(7);

  p1.push_back(2);
  p2.push_back(3);

  p1.push_back(2);
  p2.push_back(4);
  
  p1.push_back(3);
  p2.push_back(5);
  
  p1.push_back(4);
  p2.push_back(5);

  p1.push_back(4);
  p2.push_back(6);

  p1.push_back(5);
  p2.push_back(7);

  p1.push_back(6);
  p2.push_back(7);

  Poly * myPoly2 = new Poly(xs, ys, zs, p1, p2); 
  allPoly.push_back(myPoly2);

  // for(int i = 0; i < (int) allPoly[1]->getNumPoints(); i++){
  //   cout << "x: " << allPoly[1]->getXPoint(i);
  //   cout << ", y: " << allPoly[1]->getYPoint(i);
  //   cout << ", z: " << allPoly[1]->getZPoint(i) << endl;
  // }
  // cout << "2--------" << endl;


  Poly * myPoly3 = new Poly(xs, ys, zs, p1, p2); 
  allPoly.push_back(myPoly3);
  translatePolygon(1, 100, 100, 100);
  translatePolygon(2, 100, 100, 100);
  //scalePolygon(1, 1.5, 1.5, 1.5);
  rotatePolygon(2, 
  0, 0, 5, 
  0, 0, 10, 
  180);
  //rotatePolygon(1, 5, 0, 0, 10, 0, 0, 180);


  // for(int i = 0; i < (int) allPoly[1]->getNumPoints(); i++){
  //   cout << "x: " << allPoly[1]->getXPoint(i);
  //   cout << ", y: " << allPoly[1]->getYPoint(i);
  //   cout << ", z: " << allPoly[1]->getZPoint(i) << endl;
  // }
  // cout << "3--------" << endl;

  drawScene();

  //create subwindows
  //the 5 parameters are: main window ID, xpos, ypos, width, height
  //[2][3]
  //[1][x]
  int Win1 = glutCreateSubWindow(MainWindow, 0, 200, 200, 200);
  glutDisplayFunc(display1);

  int Win2 = glutCreateSubWindow(MainWindow, 0, 0, 200, 200);
  glutDisplayFunc(display2);

  int Win3 = glutCreateSubWindow(MainWindow, 200, 0, 200, 200);
  glutDisplayFunc(display3);

  glutMainLoop();//main display loop, will display until terminate
  return 0;
}