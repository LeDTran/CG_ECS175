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
  if(0 <= x && x <= 400 && 0 <= y && y <= 400){
    int pixnum = x + y*400;
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
  cout << "MASTERMIN: " << mastermin << ", MASTERMAX: " << MASTERMAX << endl;
}

float getRatio(float coord, char axis){
  float ratio, newcoord;
  if(axis == 'x'){
    ratio = (coord - XMIN) / (MASTERMAX - MASTERMIN);
    newcoord = 399*ratio;
    //cout << "newcoord: " << newcoord << endl;; 
    return newcoord;
  }
  if(axis == 'y'){
    ratio = (coord - YMIN) / (MASTERMAX - MASTERMIN);
    newcoord = 399*ratio;
    //cout << "newcoord: " << newcoord << endl; 
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

void drawBSpline(int p){
  //cout << "drawing bspline" << endl;
  for(int i = 0; i < (int) allBSpline[p]->getNumCtrlPoints()-1; i++){
    //get coords
    float point1[2];
    point1[0] = allBSpline[p]->getCtrlXPoint(i);
    point1[1] = allBSpline[p]->getCtrlYPoint(i);

    //get next coord
    float point2[2];
    int j = i + 1;
    // if(i == (allBezier[p]->getNumCtrlPoints()) - 1){
    //   j = 0;
    // }
    // else{
    //   j = i + 1;
    // }
    point2[0] = allBSpline[p]->getCtrlXPoint(j);
    point2[1] = allBSpline[p]->getCtrlYPoint(j);

    point1[0] = getRatio(point1[0], 'x');
    point1[1] = getRatio(point1[1], 'y');
    point2[0] = getRatio(point2[0], 'x');
    point2[1] = getRatio(point2[1], 'y');
    drawLineDDA(PixelBuffer, point1, point2, 0, 1 , 0);
  }
}

void drawBezierControl(int p){
  for(int i = 0; i < (int) allBezier[p]->getNumCtrlPoints()-1; i++){
    //get coords
    float point1[2];
    point1[0] = allBezier[p]->getCtrlXPoint(i);
    point1[1] = allBezier[p]->getCtrlYPoint(i);

    //get next coord
    float point2[2];
    int j = i + 1;
    // if(i == (allBezier[p]->getNumCtrlPoints()) - 1){
    //   j = 0;
    // }
    // else{
    //   j = i + 1;
    // }
    point2[0] = allBezier[p]->getCtrlXPoint(j);
    point2[1] = allBezier[p]->getCtrlYPoint(j);

    point1[0] = getRatio(point1[0], 'x');
    point1[1] = getRatio(point1[1], 'y');
    point2[0] = getRatio(point2[0], 'x');
    point2[1] = getRatio(point2[1], 'y');
    drawLineDDA(PixelBuffer, point1, point2, 0.5, 0 , 0);
  }
}

//p = which bezier curve
void drawBezier(int p){
  //cout << "drawing bezier" << endl;
  float reso = allBezier[p]->getResolution();
  float n = allBezier[p]->getNumCtrlPoints();

  vector<float> curvebx;
  vector<float> curveby;

  //num of points on curve dependent on resolution
  for(int k = 0; k <= reso; k++){
  //for(int k = reso/2; k < (reso/2)+1; k++){
    float t = k/reso;

    float bx[100][100];
    float by[100][100];
    //load in control points
    for(int a = 0; a < n; a++){
      bx[0][a] = getRatio(allBezier[p]->getCtrlXPoint(a), 'x');
      by[0][a] = getRatio(allBezier[p]->getCtrlYPoint(a), 'y');
      //bx[0][a] = allBezier[p]->getCtrlXPoint(a);
      //by[0][a] = allBezier[p]->getCtrlYPoint(a);
      //cout << "bx: " << allBezier[p]->getCtrlXPoint(a) << ", by: " << allBezier[p]->getCtrlYPoint(a) << endl;
      //cout << "bx: " << bx[0][a] << ", by: " << by[0][a] << endl;
    }
    //cout << "------------" << endl;

    for(int j = 1; j < n; j++){
      for(int i = 0; i < (n-j); i++){
        bx[j][i] = ((1-t)*bx[j-1][i]) + (t*bx[j-1][i+1]);
        by[j][i] = ((1-t)*by[j-1][i]) + (t*by[j-1][i+1]);
        //cout << "j: " << j << ", i:" << i << endl;
        //cout << "bx: " << bx[j][i] << ", by: " << by[j][i] << endl;
      }
      //cout << "----" << endl;
    }

    //cout << "n: " << n << endl;
    //float x = bx[(int)(n-1)][0];
    // float y = by[(int)n-1][0];
    // cout << "x: " << x << ", y: " << y << endl;
    curvebx.push_back(bx[(int)(n-1)][0]);
    curveby.push_back(by[(int)(n-1)][0]);
    cout << "k: " << k << ", t: " << t << ", x: " << curvebx[k] << ", y: " << curveby[k] << endl;
  }

  //draw curve
  for(int i = 0; i < (int) curvebx.size()-1; i++){
    //get coords
    float point1[2];
    point1[0] = curvebx[i];
    point1[1] = curveby[i];

    //cout << "x: " << curvebx[i] << ", y: " << curveby[i] << endl;
    //get next coord
    float point2[2];
    int j = i + 1;
    // if(i == (allBezier[p]->getNumCtrlPoints()) - 1){
    //   j = 0;
    // }
    // else{
    //   j = i + 1;
    // }
    point2[0] = curvebx[j];
    point2[1] = curveby[j];

    // point1[0] = getRatio(point1[0], 'x');
    // point1[1] = getRatio(point1[1], 'y');
    // point2[0] = getRatio(point2[0], 'x');
    // point2[1] = getRatio(point2[1], 'y');
    drawLineDDA(PixelBuffer, point1, point2, 1, 0 , 0);
  }
}


//used to redraw scene, with updated lines and polygons
void drawScene(){
  //clear window
  for(int i = 0; i < 400*400*3; i++){
      PixelBuffer[i] = 0;
  }
  updateMinMax();

  //draw all Bezier curves
  for(int i = 0; i < (int) allBezier.size(); i++){
    //drawPolygon(i);
    drawBezierControl(i);
    drawBezier(i);
    //allBezier[i]->printData();
  }

  //draw all BSpline curves
  for(int i = 0; i < (int) allBSpline.size(); i++){
    drawBSpline(i);
    //allBSpline[i]->printData();
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
        float numknots = numpoints + k + 1;
        vector<float> knotvalues;
        float currknot;
        if(knotchar == 'T'){
          for(int i = 0; i < numknots; i++){
            getline(myfile, line);
            istringstream iss5(line);
            iss5 >> currknot;
            knotvalues.push_back(currknot);
          }
          BSpline * myBSpline = new BSpline(ctrlxs, ctrlys, k, knotvalues); 
          allBSpline.push_back(myBSpline);
        }
        //if not knot values, need to generate some
        else if (knotchar == 'F'){
            for(int i = 0; i < numknots; i++){
            knotvalues.push_back((float)i);
          }
          BSpline * myBSpline = new BSpline(ctrlxs, ctrlys, k, knotvalues); 
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