#include "p4.h"
//Sub windows demonstration

//More pixel buffers!!
float *PixelBuffer;

float XMIN, XMAX, YMIN, YMAX;
float MASTERMIN, MASTERMAX;

vector<Bezier *> allBezier;
vector<BSpline *> allBSpline;

bool isAnimating;

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
  glDrawPixels(400, 400, GL_RGB, GL_FLOAT, PixelBuffer);

  //window refresh
  //glEnd();
  glFlush();
}

float getXMin(){
  float x = allBezier[0]->getCtrlXPoint(0);
  //for each Bezier
  for(int i = 0; i < (int)allBezier.size(); i++){
    //for each point in that Bezier
    for(int j = 0; j < allBezier[i]->getNumCtrlPoints(); j++){
      if(allBezier[i]->getCtrlXPoint(j) < x){
        x = allBezier[i]->getCtrlXPoint(j);
      }
    }
  }

  //for each BSpline
  for(int i = 0; i < (int)allBSpline.size(); i++){
    //for each point in that BSpline
    for(int j = 0; j < allBSpline[i]->getNumCtrlPoints(); j++){
      if(allBSpline[i]->getCtrlXPoint(j) < x){
        x = allBSpline[i]->getCtrlXPoint(j);
      }
    }
  }

  return x;
}

float getXMax(){
  float x = allBezier[0]->getCtrlXPoint(0);
  //for each Bezier
  for(int i = 0; i < (int)allBezier.size(); i++){
    //for each point in that Bezier
    for(int j = 0; j < allBezier[i]->getNumCtrlPoints(); j++){
      if(allBezier[i]->getCtrlXPoint(j) > x){
        x = allBezier[i]->getCtrlXPoint(j);
      }
    }
  }
  //for each BSpline
  for(int i = 0; i < (int)allBSpline.size(); i++){
    //for each point in that BSpline
    for(int j = 0; j < allBSpline[i]->getNumCtrlPoints(); j++){
      if(allBSpline[i]->getCtrlXPoint(j) > x){
        x = allBSpline[i]->getCtrlXPoint(j);
      }
    }
  }
  return x;
}

float getYMin(){
  float y = allBezier[0]->getCtrlYPoint(0);
  //for each Bezier
  for(int i = 0; i < (int)allBezier.size(); i++){
    //for each point in that Bezier
    for(int j = 0; j < allBezier[i]->getNumCtrlPoints(); j++){
      if(allBezier[i]->getCtrlYPoint(j) < y){
        y = allBezier[i]->getCtrlYPoint(j);
      }
    }
  }
  //for each BSpline
  for(int i = 0; i < (int)allBSpline.size(); i++){
    //for each point in that BSpline
    for(int j = 0; j < allBSpline[i]->getNumCtrlPoints(); j++){
      if(allBSpline[i]->getCtrlYPoint(j) < y){
        y = allBSpline[i]->getCtrlYPoint(j);
      }
    }
  }
  return y;
}

float getYMax(){
  float y = allBezier[0]->getCtrlYPoint(0);
  //for each Bezier
  for(int i = 0; i < (int)allBezier.size(); i++){
    //for each point in that Bezier
    for(int j = 0; j < allBezier[i]->getNumCtrlPoints(); j++){
      if(allBezier[i]->getCtrlYPoint(j) > y){
        y = allBezier[i]->getCtrlYPoint(j);
      }
    }
  }
  //for each BSpline
  for(int i = 0; i < (int)allBSpline.size(); i++){
    //for each point in that BSpline
    for(int j = 0; j < allBSpline[i]->getNumCtrlPoints(); j++){
      if(allBSpline[i]->getCtrlYPoint(j) > y){
        y = allBSpline[i]->getCtrlYPoint(j);
      }
    }
  }
  return y;
}

void updateMinMax(){
  XMIN = getXMin();
  XMAX = getXMax();
  YMIN = getYMin();
  YMAX = getYMax();

  float mastermin = XMIN;
  float mastermax = XMAX;

  if(YMIN < mastermin){
    mastermin = YMIN;
  }

  if(YMAX > mastermax){
    mastermax = YMAX;
  }

  MASTERMIN = mastermin;
  MASTERMAX = mastermax;
}

float getRatio(float coord, char axis){
  float ratio, newcoord;
  if(axis == 'x'){
    ratio = (coord - XMIN) / (MASTERMAX - MASTERMIN);
    newcoord = 399*ratio;
    return newcoord;
  }
  if(axis == 'y'){
    ratio = (coord - YMIN) / (MASTERMAX - MASTERMIN);
    newcoord = 399*ratio;
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

// void drawPolygon(int p){
//   for(int i = 0; i < allPoly[p]->getNumLineP(); i++){
//     int linepoint1 = allPoly[p]->getLineP1(i);
//     int linepoint2 = allPoly[p]->getLineP2(i);

//     //get coords1 xyz1
//     float lpoint1[3];
//     lpoint1[0] = allPoly[p]->getXPoint(linepoint1);
//     lpoint1[1] = allPoly[p]->getYPoint(linepoint1);
//     lpoint1[2] = allPoly[p]->getZPoint(linepoint1);

//     //get coords2 xyz2
//     float lpoint2[3];
//     lpoint2[0] = allPoly[p]->getXPoint(linepoint2);
//     lpoint2[1] = allPoly[p]->getYPoint(linepoint2);
//     lpoint2[2] = allPoly[p]->getZPoint(linepoint2);

//     float point1[2];
//     float point2[2];

//     //plot XY
//     point1[0] = getRatio(lpoint1[0], 'x');
//     point1[1] = getRatio(lpoint1[1], 'y');
//     point2[0] = getRatio(lpoint2[0], 'x');
//     point2[1] = getRatio(lpoint2[1], 'y');
//     drawLineDDA(BufferXY, point1, point2, 1, 0, 0);
//   }
// }


//used to redraw scene, with updated lines and polygons
void drawScene(){
  //clear window
  for(int i = 0; i < 400*400*3; i++){
      PixelBuffer[i] = 0;
  }
  //updateMinMax();

  //draw all Bezier curves
  for(int i = 0; i < (int) allBezier.size(); i++){
    //drawPolygon(i);
    allBezier[i]->printData();
  }

  //draw all BSpline curves
  for(int i = 0; i < (int) allBSpline.size(); i++){
    allBSpline[i]->printData()  ;
  }

  // //draw borders  
  // float point1[2];
  // float point2[2];
  // point1[0] = 199;
  // point1[1] = 0;
  // point2[0] = 199;
  // point2[1] = 199;
  // drawLineDDA(BufferXY, point1, point2, 1, 1, 1);//, true, p);
  // drawLineDDA(BufferXZ, point1, point2, 1, 1, 1);
  // drawLineDDA(BufferYZ, point1, point2, 1, 1, 1);
  // point1[0] = 0;
  // point1[1] = 0;
  // point2[0] = 199;
  // point2[1] = 0;
  // drawLineDDA(BufferXY, point1, point2, 1, 1, 1);//, true, p);
  // drawLineDDA(BufferXZ, point1, point2, 1, 1, 1);
  // drawLineDDA(BufferYZ, point1, point2, 1, 1, 1);

  glutPostRedisplay();
}

void readData(){
  string line;
  ifstream myfile ("save.dat");
  if (myfile.is_open()){
    while(getline(myfile, line)){
      //read in bezier curve
      if(line[0] == 'b' && line[1] == 'z'){
        //read in number of points
        int numpoints;
        getline(myfile, line);
        istringstream iss1(line);
        iss1 >> numpoints;
        //cout << "numpoints: " << numpoints << endl;

        //read in control points
        float ctrlx, ctrly;
        vector<float> ctrlxs;
        vector<float> ctrlys;
        ctrlxs.clear();
        ctrlys.clear();
        for(int i = 0; i < numpoints; i++){
          getline(myfile, line);
          istringstream iss2(line);
          iss2 >> ctrlx >> ctrly;
          ctrlxs.push_back(ctrlx);
          ctrlys.push_back(ctrly);
        }

        Bezier * myBezier = new Bezier(ctrlxs, ctrlys); 
        allBezier.push_back(myBezier);
      }

      //read in bspline curve
      if(line[0] == 'b' && line[1] == 's'){
        //read in number of points
        int numpoints;
        getline(myfile, line);
        istringstream iss1(line);
        iss1 >> numpoints;
        //cout << "numpoints: " << numpoints << endl;

        //read in k value
        float k;
        getline(myfile, line);
        istringstream iss2(line);
        iss2 >> k;

        //read in if knots are specified
        char knotchar;
        getline(myfile, line);
        istringstream iss3(line);
        iss3 >> knotchar;

        //read in control points
        float ctrlx, ctrly;
        vector<float> ctrlxs;
        vector<float> ctrlys;
        ctrlxs.clear();
        ctrlys.clear();
        for(int i = 0; i < numpoints; i++){
          getline(myfile, line);
          istringstream iss4(line);
          iss4 >> ctrlx >> ctrly;
          ctrlxs.push_back(ctrlx);
          ctrlys.push_back(ctrly);
        }

        //read in knot value if there is one
        //then create bspline object
        if(knotchar == 'T'){
          float knot;
          getline(myfile, line);
          istringstream iss5(line);
          iss5 >> knot;
     
          BSpline * myBSpline = new BSpline(ctrlxs, ctrlys, k, knotchar, knot); 
          allBSpline.push_back(myBSpline);
        }
        else if (knotchar == 'F'){
          BSpline * myBSpline = new BSpline(ctrlxs, ctrlys, k, knotchar, 0); 
          allBSpline.push_back(myBSpline);
        }
      }
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
  //set window size to 400*400
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
  // BufferXY = new float[200 * 200 * 3];
  // BufferXZ = new float[200 * 200 * 3];
  // BufferYZ = new float[200 * 200 * 3];
  // for(int i = 0; i < 200 * 200 * 3; i++){
  //   BufferXY[i] = 0;
  //   BufferXZ[i] = 0;
  //   BufferYZ[i] = 0;
  // }

  // //create subwindows
  // //the 5 parameters are: main window ID, xpos, ypos, width, height
  // //[2][3]
  // //[1][x]
  // Win1 = glutCreateSubWindow(MainWindow, 0, 200, 200, 200);
  // glutDisplayFunc(display1);
  // Win2 = glutCreateSubWindow(MainWindow, 0, 0, 200, 200);
  // glutDisplayFunc(display2);
  // Win3 = glutCreateSubWindow(MainWindow, 200, 0, 200, 200);
  // glutDisplayFunc(display3);

  drawScene();

  //createMenu();     

  glutMainLoop();//main display loop, will display until terminate
  return 0;
}