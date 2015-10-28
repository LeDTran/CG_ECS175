#include "p1.h"

float *PixelBuffer;
//line[5] = [x1|y1|x2|y2|line draw alg]
//line draw alg: 1 = DDA, 2 = Bresenham
//allLines only includes single lines, excludes polygon lines
vector<int *> allLines;
vector<Poly *> allPoly;

vector<int> xs;
vector<int> ys;

int WINDOW_WIDTH;
int WINDOW_HEIGHT;

int main(int argc, char *argv[]){
  cout << "Please enter window width: ";
  cin >> WINDOW_WIDTH;
  cout << "Please enter window height: ";
  cin >> WINDOW_HEIGHT;

  char choice;
  cout << "Would you like to load 'save.dat? (y/n): ";
  cin >> choice;
  if(choice == 'y'){
    cout << "LOADING save.dat" << endl;
    readData();
  }
  cout << "-----Press ""M"" whilst INSIDE the display window to bring up the menu-----" << endl;


  PixelBuffer = new float[WINDOW_WIDTH * WINDOW_HEIGHT * 3];
  for(int i = 0; i < WINDOW_WIDTH*WINDOW_HEIGHT*3; i++){
      PixelBuffer[i] = 0;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  //set window position
  glutInitWindowPosition(100, 100);

  //create and set main window title
  int MainWindow = glutCreateWindow("Hello Graphics!!");
  glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
  //sets display function

  drawScene();
  glutDisplayFunc(display);

  glutKeyboardFunc(callbackFunc);
  glutMainLoop();//main display loop, will display until terminate
  return 0;
}

void readData(){
  string line;
  ifstream myfile ("save.dat");
  if (myfile.is_open()){
    while(getline(myfile, line)){
      //read in line
      if(line[0] == 'L'){
        int * newline = new int [5];

        //get first coord
        getline(myfile, line);
        istringstream iss1(line);
        iss1 >> newline[0] >> newline[1];

        //get second coord
        getline(myfile, line);
        istringstream iss2(line);
        iss2 >> newline[2] >> newline[3];

        //get line drawing algorithm
        getline(myfile, line);
        istringstream iss3(line);
        iss3 >> newline[4];
        allLines.push_back(newline);
      }
      //read in polygon
      if(line[0] == 'P'){
        //read in number of points
        int numpoints;
        getline(myfile, line);
        istringstream iss1(line);
        iss1 >> numpoints;

        //read in points
        int x, y;
        vector<int> xs;
        vector<int> ys;
        xs.clear();
        ys.clear();
        for(int i = 0; i < numpoints; i++){
          getline(myfile, line);
          istringstream iss2(line);
          iss2 >> x >> y;
          xs.push_back(x);
          ys.push_back(y);
        }
        //read in rasterization status
        bool israst;
        getline(myfile, line);
        istringstream iss3(line);
        iss3 >> israst;
        Poly * myPoly = new Poly(xs, ys, israst);
        allPoly.push_back(myPoly);
      }
      //cout << line << endl;
    }
    myfile.close();
  }
}

void drawPix(float *PixelBuffer, int *point){

  //Pixel not drawn if outside viewing window
  if(0 <= point[0] && point[0] <= WINDOW_WIDTH && 0 <= point[1] && point[1] <= WINDOW_HEIGHT){
    int pixnum = point[0] + point[1]*WINDOW_WIDTH;

    //R
    PixelBuffer[0 + pixnum*3] = 0.76;
    //G
    PixelBuffer[1 + pixnum*3] = 0.84;
    //B
    PixelBuffer[2 + pixnum*3] = 0.88;
  }
}

void drawLineDDA(int * p1, int *p2, bool ispoly, int p){
  //reorder as p1 = left point, p2 = right point
  if(p1[0] > p2[0]){
    int temp[2];
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
    for(int i = 0; i <= dx; i++)
    {
      y = round(y0 + (dy/dx)*i); 
      point[0] = x;
      point[1] = y;
      if(ispoly){
        allPoly[p]->addEdgeX(point[0]);
        allPoly[p]->addEdgeY(point[1]);
      }
      drawPix(PixelBuffer, point);
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
      if(ispoly){
        allPoly[p]->addEdgeX(point[0]);
        allPoly[p]->addEdgeY(point[1]);
      }
      drawPix(PixelBuffer, point);
      if(dy > 1){
        y = y + 1;
      }
      else{
        y = y - 1;
      }
    }
  }  
}

void drawLineBresenham(int * p1, int *p2, bool ispoly, int p){
  //reorder as p1 = left point, p2 = right point
  if(p1[0] > p2[0]){
    int temp[2];
    temp[0] = p1[0];
    temp[1] = p1[1];

    p1[0] = p2[0];
    p1[1] = p2[1];

    p2[0] = temp[0];
    p2[1] = temp[1];
  }  

  float dy = p2[1] - p1[1];
  float dx = p2[0] - p1[0]; 

  int point[2];
  int x = p1[0];
  int y = p1[1];
  int xnext  = x;
  int ynext = y;
  int pi;

  if(0 <= dy/dx && dy/dx < 1){
    for(int i = 0; i <= dx; i++){
      //set p1
      if(i == 0){
        pi = 2*dy - dx;
      }
      else{
        pi = pi + 2*dy -  2*dx*(ynext - y);
      }

      point[0] = x;
      point[1] = ynext;
      if(ispoly){
        allPoly[p]->addEdgeX(point[0]);
        allPoly[p]->addEdgeY(point[1]);
      }
      drawPix(PixelBuffer, point);
      x =  x + 1;

      if(pi > 0){
        y = ynext;
        ynext = y + 1;
      }
      else{
        y = ynext;
        ynext = y;
      }
    }  
  }
  else if(-1 < dy/dx && dy/dx < 0){
    for(int i = 0; i <= dx; i++){
      //set p1
      if(i == 0){
        pi = -2*dy - dx;
      }
      else{
        pi = pi + 2*dx*(ynext - y) - 2*dy;
      }

      point[0] = x;
      point[1] = ynext;
      if(ispoly){
        allPoly[p]->addEdgeX(point[0]);
        allPoly[p]->addEdgeY(point[1]);
      }
      drawPix(PixelBuffer, point);
      x =  x + 1;

      if(pi > 0){
        y = ynext;
        ynext = y - 1;
      }
      else{
        y = ynext;
        ynext = y;
      }
    }  
  }
  else if(1 <= dy/dx){
    for(int i = 0; i <= dy; i++){
      //set p1
      if(i == 0){
        pi = 2*dx - dy;
      }
      else{
        pi = pi + 2*dx - 2*dy*(xnext - x);
      }

      point[0] = xnext;
      point[1] = y;
      if(ispoly){
        allPoly[p]->addEdgeX(point[0]);
        allPoly[p]->addEdgeY(point[1]);
      }
      drawPix(PixelBuffer, point);
      y =  y + 1;

      if(pi > 0){
        x = xnext;
        xnext = x + 1;
      }
      else{
        x = xnext;
        xnext = x;
      }
    }  
  }
  else if(dy/dx <= -1){
    for(int i = 0; i <= abs(dy); i++){
      //set p1
      if(i == 0){
        pi = -dy - 2*dx;
      }
      else{
        pi = pi - 2*dx - 2*dy*(xnext - x);
      }

      point[0] = xnext;
      point[1] = y;
      if(ispoly){
        allPoly[p]->addEdgeX(point[0]);
        allPoly[p]->addEdgeY(point[1]);
      }
      drawPix(PixelBuffer, point);
      y =  y - 1;

      if(pi < 0){
        x = xnext;
        xnext = x + 1;
      }
      else{
        x = xnext;
        xnext = x;
      }
    }  
  }
}

//draw polygon given polygon number in vector
void drawPolygon(int p){
  for(int i = 0; i < allPoly[p]->getNumPoints(); i++){
    //get coords
    int point1[2];
    point1[0] = allPoly[p]->getXPoint(i);
    point1[1] = allPoly[p]->getYPoint(i);

    //get next coord
    int point2[2];
    int j;
    if(i == (allPoly[p]->getNumPoints()) - 1){
      j = 0;
    }
    else{
      j = i + 1;
    }
    point2[0] = allPoly[p]->getXPoint(j);
    point2[1] = allPoly[p]->getYPoint(j);

    drawLineDDA(point1, point2, true, p);
    //drawLineBresenham(point1, point2, true, p);
  }
}

//translate poly given change in x and change in y
void translatePolygon(int p, int dx, int dy){
  allPoly[p]->translatePoly(dx, dy);
}

//scale poly given x scalar and y scalar
void scalePolygon(int p, float sx, float sy){
  int cx = allPoly[p]->getCentroidX();
  int cy = allPoly[p]->getCentroidY();
  allPoly[p]->translatePoly(-cx, -cy);
  allPoly[p]->scalePoly(sx, sy);
  allPoly[p]->translatePoly(cx, cy);
}

//rotate poly given angle in degrees
void rotatePolygon(int p, int deg){
  int cx = allPoly[p]->getCentroidX();
  int cy = allPoly[p]->getCentroidY();
  allPoly[p]->translatePoly(-cx, -cy);
  allPoly[p]->rotatePoly(deg);
  allPoly[p]->translatePoly(cx, cy);
}

//draw polygon given polygon number in vector
void rasterizePolygon(int p){
  vector<int> xpoints;
  vector<int> ypoints;
  int point1[2], point2[2];
  for(int i = allPoly[p]->getLocalMinY() + 1; i < allPoly[p]->getLocalMaxY(); i++){
    xpoints.clear();
    ypoints.clear();
    for(int j = 0; j < allPoly[p]->getNumEdgePoints(); j++){
      if(i  == allPoly[p]->getEdgeYPoint(j)){
        xpoints.push_back(allPoly[p]->getEdgeXPoint(j));
        ypoints.push_back(allPoly[p]->getEdgeYPoint(j));
        break;
      }
    }
    for(int j = allPoly[p]->getNumEdgePoints() -1 ; j < allPoly[p]->getNumEdgePoints(); j--){
      if(i  == allPoly[p]->getEdgeYPoint(j)){
        xpoints.push_back(allPoly[p]->getEdgeXPoint(j));
        ypoints.push_back(allPoly[p]->getEdgeYPoint(j));
        break;
      }
    }

    point1[0] = xpoints[0]; 
    point1[1] = ypoints[0];
    point2[0] = xpoints[1];
    point2[1] = ypoints[1];
    drawLineDDA(point1, point2, false, 0);
    //drawLineBresenham(point1, point2, false, 0);
  }
}

int findABRL(int x, int y, int xmin, int xmax, int ymin, int ymax){
  int code = 0;
  if(x < xmin){
    code |= 1; //left:0001
  }
  else if(x > xmax){
    code |= 2; //right:0010
  }
  if(y < ymin){
    code |= 4; //below:0100
  }
  else if(y > ymax){
    //cout << "|= 8"\\ << endl;
    code |= 8; //above:1000
  }
  return code;
}

//find new y
int clipVert(int dy, int dx, int x1, int y1, int x){
  float y = ((float)dy/(float)dx) * ((float)x - (float)x1) + (float)y1;
  return (int)round(y);
}

//find new x
int clipHori(int dy, int dx, int x1, int y1, int y){
  int x = (((float)y - (float)y1) / ((float)dy/(float)dx)) + (float)x1;
  cout << "x: " << x << endl;
  return (int)round(x);
}

//clip line given clip windo dimensions
void clipLine(int l, int xmin, int xmax, int ymin, int ymax){
  int x1 = allLines[l][0];
  int y1 = allLines[l][1];
  int x2 = allLines[l][2];
  int y2 = allLines[l][3];

  int dy = y2 - y1;
  int dx = x2 - x1;

  int code1 = findABRL(x1, y1, xmin, xmax, ymin, ymax);
  int code2 = findABRL(x2, y2, xmin, xmax, ymin, ymax);

  if(code1 == 0 && code2 == 0){
    //the lines lie completely inside window
    //cout << "TRIVIALLY ACCEPT" << endl;
  }
  else if ((code1 & code2) != 0){
    //the lines lie completely outside the window; delete line
    allLines.erase(allLines.begin()+l);
  }
  else{
    while(!(code1 == 0 && code2 == 0)){  //while 
      if((code1 & code2) == 0){ //need to split
        if(code1 != 0 ){ //take first point if not inside
          if(code1 & 8){ //if point is above
            x1 = clipHori(dy, dx, x1, y1, ymax); //gives new x, intercept with ymax
            y1 = ymax;
            code1 = findABRL(x1, y1, xmin, xmax, ymin, ymax);
          }
          else if(code1 & 4){ //if point is below
            x1 = clipHori(dy, dx, x1, y1, ymin); //gives new x, intercept with ymin
            y1 = ymin;
            code1 = findABRL(x1, y1, xmin, xmax, ymin, ymax);
          }
          else if(code1 & 2){ //if point is right
            y1 = clipVert(dy, dx, x1, y1, xmax); //gives new y, intercept with xmax
            x1 = xmax;
            code1 = findABRL(x1, y1, xmin, xmax, ymin, ymax);
          }
          else if(code1 & 1){ //if point is left
            y1 = clipVert(dy, dx, x1, y1, xmin); //gives new y, intercept with xmin
            x1 = xmin;
            code1 = findABRL(x1, y1, xmin, xmax, ymin, ymax);
          }
        }
        else if(code2 != 0){ //take second point if not inside 
          if(code2 & 8){ //if point is above
            x2 = clipHori(dy, dx, x2, y2, ymax); //gives new x, intercept with ymax
            y2 = ymax;
            code2 = findABRL(x2, y2, xmin, xmax, ymin, ymax);
          }
          else if(code2 & 4){ //if point is below
            x2 = clipHori(dy, dx, x2, y2, ymin); //gives new x, intercept with ymin
            y2 = ymin;
            code2 = findABRL(x2, y2, xmin, xmax, ymin, ymax);
          }
          else if(code2 & 2){ //if point is right
            y2 = clipVert(dy, dx, x2, y2, xmax); //gives new y, intercept with xmax
            x2 = xmax;
            code2 = findABRL(x2, y2, xmin, xmax, ymin, ymax);
          }
          else if(code2 & 1){ //if point is left
            y2 = clipVert(dy, dx, x2, y2, xmin); //gives new y, intercept with xmin
            x2 = xmin;
            code2 = findABRL(x2, y2, xmin, xmax, ymin, ymax);
          }
        }
      }
    }
    allLines[l][0] = x1;
    allLines[l][1] = y1;
    allLines[l][2] = x2;
    allLines[l][3] = y2;
  }
}

//used to redraw scene, with updated lines and polygons
void drawScene(){
  //clear window
  for(int i = 0; i < WINDOW_WIDTH*WINDOW_HEIGHT*3; i++){
      PixelBuffer[i] = 0;
  }

  //draw all polygons
  for(int i = 0; i < (int) allPoly.size(); i++){
    //need to reset edge points for rasterization after a transformation
    allPoly[i]->resetEdgePoints();
    drawPolygon(i);
    //sort edges for rasterization
    allPoly[i]->sortEdgePoints();
    //rasterize polygon if done before
    if(allPoly[i]->getIsRasterized()){
      rasterizePolygon(i);
    }
  }

  //draw all lines
  int point1[2], point2[2];
  for(int i = 0; i < (int) allLines.size(); i++){
    point1[0] = allLines[i][0];
    point1[1] = allLines[i][1];
    point2[0] = allLines[i][2];
    point2[1] = allLines[i][3];
    if(allLines[i][4] == 1){
      drawLineDDA(point1, point2, false, 0);
    }
    else if(allLines[i][4] == 2){
      drawLineBresenham(point1, point2, false, 0);
    }
  }
}


//main display loop, this function will be called again and again by OpenGL
void display(){
	//Misc.
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  //draws pixel on screen, width and height must match pixel buffer dimension
  glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_FLOAT, PixelBuffer);

  glEnd();
  glFlush();
}  