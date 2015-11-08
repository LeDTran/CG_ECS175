#include "UI.h"

void UIDrawPolygon(){
  int numpoints;
  //while(numpoints < 3){
  cout << "Enter the number of points for the polygon: "; 
  cin >> numpoints;
  vector<float> xs;
  vector<float> ys;
  vector<float> zs;
  int x, y, z;
  for(int i = 0; i < numpoints; i++){
    cout << "Enter x" << i+1 << ": ";
    cin >> x;
    xs.push_back(x);
    cout << "Enter y" << i+1 << ": ";
    cin >> y;
    ys.push_back(y);
    cout << "Enter z" << i+1 << ": ";
    cin >> z;
    zs.push_back(z);
  }

  int numedges;
  cout << "Enter the number of edges for the polygon: "; 
  cin >> numedges;
  int pt1, pt2;
  vector<int> p1;
  vector<int> p2;
  for(int i = 0; i < numedges; i++){
    cout << "Enter the first point number for edge " << i+1 << ": ";
    cin >> pt1;
    pt1--;
    p1.push_back(pt1);

    cout << "Enter the second point number for edge " << i+1 << ": ";
    cin >> pt2;
    pt2--;
    p2.push_back(pt2);
  }

  // Poly * myPoly = new Poly(xs, ys, zs, p1, p2); 
  // allPoly.push_back(myPoly);
}

void UITranslatePolygon(){
  if(allPoly.size() == 0){
    cout << "There are no shapes to translate" << endl;
  }
  else{
    int selection = -1;
    while(!(1 <= selection && selection <= (int)allPoly.size())){
      cout << "Please select a shape number to translate: " << endl;
      for(int i = 1; i <= (int)allPoly.size(); i++){
        cout << "   " << i << ") Shape " << i << endl;
      }
      cout<< "Selection: ";
      cin >> selection; 
    }
    //turn selection into array index
    selection = selection - 1;

    float dx, dy, dz;
    cout << "Enter the change in x direction: ";
    cin >> dx;
    cout << "Enter the change in y direction: ";
    cin >> dy;
    cout << "Enter the change in z direction: ";
    cin >> dz;

    translatePolygon(selection, dx, dy, dz);
  }
}

void UIScalePolygon(){
  if(allPoly.size() == 0){
    cout << "There are no shapes to scale" << endl;
  }
  else{
    int selection = -1;
    while(!(1 <= selection && selection <= (int)allPoly.size())){
      cout << "Please select a shape number to scale: " << endl;
      for(int i = 1; i <= (int)allPoly.size(); i++){
        cout << "   " << i << ") Shape " << i << endl;
      }
      cout<< "Selection: ";
      cin >> selection; 
    }
    //turn selection into array index
    selection = selection - 1;

    float sx, sy, sz;
    cout << "Enter the magnitude to scale in the x direction: ";
    cin >> sx;
    cout << "Enter the magnitude to scale in the y direction: ";
    cin >> sy;
    cout << "Enter the magnitude to scale in the z direction: ";
    cin >> sz;

    scalePolygon(selection, sx, sy, sz);
  }
}

void UIRotatePolygon(){
  if(allPoly.size() == 0){
    cout << "There are no shape to rotate" << endl;
  }
  else{
    int selection = -1;
    while(!(1 <= selection && selection <= (int)allPoly.size())){
      cout << "Please select a shape number to rotate: " << endl;
      for(int i = 1; i <= (int)allPoly.size(); i++){
        cout << "   " << i << ") Shape " << i << endl;
      }
      cout<< "Selection: ";
      cin >> selection; 
    }
    //turn selection into array index
    selection = selection - 1;
    cout << "selection:  " << selection << endl;

    float x1, y1, z1, x2, y2, z2;
    float deg;
    cout << "Enter the coordinates for the first point of the axis of rotation: " << endl;
    cout << "Enter x1: "; 
    cin >> x1;
    cout << "Enter y1: "; 
    cin >> y1;
    cout << "Enter z1: "; 
    cin >> z1;

    cout << "Enter the coordinates for the second point of the axis of rotation: " << endl;
    cout << "Enter x2: "; 
    cin >> x2;
    cout << "Enter y2: "; 
    cin >> y2;
    cout << "Enter z2: "; 
    cin >> z2;

    cout << "Enter the angle of rotation (in degrees): ";
    cin >> deg;
    rotatePolygon(selection, x1, y1, z1, x2, y2, z2, deg);

    drawScene();

    //draw rotation axis
    float point1[2];
    float point2[2];
    //extend axist
    x1 = x1 * 500;
    y1 = y1 * 500;
    z1 = z1 * 500;
    x2 = x2 * 500;
    y2 = y2 * 500;
    z2 = z2 * 500;
    
    //plot XY
    point1[0] = getRatio(x1, 'x');
    point1[1] = getRatio(y1, 'y');
    point2[0] = getRatio(x2, 'x');
    point2[1] = getRatio(y2, 'y');
    drawLineDDA(BufferXY, point1, point2, 1, 0, 0);

    //plot XZ
    point1[0] = getRatio(x1, 'x');
    point1[1] = getRatio(z1, 'z');
    point2[0] = getRatio(x2, 'x');
    point2[1] = getRatio(z2, 'z');   
    drawLineDDA(BufferXZ, point1, point2, 0, 1, 0);

    //plot YZ
    point1[0] = getRatio(y1, 'y');
    point1[1] = getRatio(z1, 'z');
    point2[0] = getRatio(y2, 'y');
    point2[1] = getRatio(z2, 'z');
    drawLineDDA(BufferYZ, point1, point2, 0, 0, 1);
  }
}

void UISaveScene(){
  char choice;
  cout << "This will overwrite 'save.dat'. Are you sure you want to continue? (y/n): ";
  cin >> choice;
  if(choice == 'y'){
    //if(save.dat exists)
    remove("save.dat");

    ofstream outfile;
    outfile.open("save.dat");

    //write out polygon data
    for(int p = 0; p < (int)allPoly.size(); p++){
      outfile << "P" << endl;
      //output number of points
      outfile << allPoly[p]->getNumPoints() << endl;
      //output coords
      for(int i = 0; i < allPoly[p]->getNumPoints(); i++){
        outfile << allPoly[p]->getXPoint(i) << " " << allPoly[p]->getYPoint(i) << " " << allPoly[p]->getZPoint(i) << endl;
      }
      //output number of edge points
      outfile << allPoly[p]->getNumLineP() << endl;
      for(int i = 0; i < allPoly[p]->getNumLineP(); i++){
        outfile << allPoly[p]->getLineP1(i)+1 << " " << allPoly[p]->getLineP2(i)+1 << endl;
      }
      outfile << endl;
    }
  }
  else if(choice == 'n'){
  }
}

static int window;
static int menu_id;

void menu(int selection){
  if(selection == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
    switch(selection){
      case 1:
        UIDrawPolygon();
        drawScene();
        break;
      case 2:
        UITranslatePolygon();
        drawScene();
        break;
      case 3:
        UIScalePolygon();
        drawScene();
        break;
      case 4:
        UIRotatePolygon();
        break;
      case 5:
        UISaveScene();
        drawScene();
        break;
      case 6:
        isAnimating = true;
        startAnimation();
        break;
      case 7:
        isAnimating = false;
        drawScene();
        break;
      default:
        break;
    }
  }
}  

void createMenu(void){        
    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Draw a Shape", 1);
    glutAddMenuEntry("Translate a Shape", 2);
    glutAddMenuEntry("Scale a Shape", 3);
    glutAddMenuEntry("Rotate a Shape", 4);
    glutAddMenuEntry("Save Scene", 5);
    glutAddMenuEntry("Animate Rotation of Scene", 6);
    glutAddMenuEntry("Stop Animated Rotation of Scene", 7);
    glutAddMenuEntry("Quit", 0);     
    glutAttachMenu(GLUT_RIGHT_BUTTON);
} 
