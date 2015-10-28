#include "UI.h"

void UIDrawLine(){
  int selection = -1;
  int * line = new int [5];
  while(!(selection == 1 || selection == 2)){
    cout << "Please select a line drawing algorithm between 1-2: " << endl;
    cout << "   1) DDA" << endl;
    cout << "   2) Bresenham" << endl;
    cout << "Selection: ";
    cin >> selection;

    switch(selection){
      case 1:
        //set line drawing alg as 5th element in line array
        line[4] = selection;
        break;
      case 2:
        line[4] = selection;
        break;
      default:
        break;
    }
  }

  cout << "Enter x1: ";
  cin >> line[0];
  cout << "Enter y1: ";
  cin >> line[1];
  cout << "Enter x2: ";
  cin >> line[2];
  cout << "Enter y2: ";
  cin >> line[3];
  allLines.push_back(line);
}

void UIClipLine(){
  if(allLines.size() == 0){
    cout << "There are no lines to clip" << endl;
  }
  else{
    int selection = -1;
    while(!(1 <= selection && selection <= (int)allLines.size())){
      cout << "Please select a line number to clip: " << endl;
      for(int i = 1; i <= (int)allLines.size(); i++){
        cout << "   " << i << ") Line " << i << endl;
      }
      cout<< "Selection: ";
      cin >> selection; 
    }
    //turn selection into array index
    selection = selection - 1;

    int xmin, xmax, ymin, ymax;
    cout << "Enter the clipping window dimensions:" << endl;
    cout << "Enter xmin: ";
    cin >> xmin;
    cout << "Enter xmax: ";
    cin >> xmax;
    cout << "Enter ymin: ";
    cin >> ymin;
    cout << "Enter ymax: ";
    cin >> ymax;
    clipLine(selection, xmin, xmax, ymin, ymax);;
  }
}

void UIDrawPolygon(){
  int numpoints = -1;
  while(numpoints < 3){
    cout << "Enter the number of points for the polygon (needs at least 3): "; 
    cin >> numpoints;
  }

  vector<int> xs;
  vector<int> ys;
  int x, y;
  for(int i = 0; i < numpoints; i++){
    cout << "Enter x" << i+1 << ": ";
    cin >> x;
    xs.push_back(x);
    cout << "Enter y" << i+1 << ": ";
    cin >> y;
    ys.push_back(y);
  }
  Poly * myPoly = new Poly(xs, ys, false); 
  allPoly.push_back(myPoly);
}

void UITranslatePolygon(){
  if(allPoly.size() == 0){
    cout << "There are no polygons to translate" << endl;
  }
  else{
    int selection = -1;
    while(!(1 <= selection && selection <= (int)allPoly.size())){
      cout << "Please select a polygon number to translate: " << endl;
      for(int i = 1; i <= (int)allPoly.size(); i++){
        cout << "   " << i << ") Polygon " << i << endl;
      }
      cout<< "Selection: ";
      cin >> selection; 
    }
    //turn selection into array index
    selection = selection - 1;
    int dx, dy;
    cout << "Enter the change in x direction: ";
    cin >> dx;
    cout << "Enter the change in y direction: ";
    cin >> dy;
    translatePolygon(selection, dx, dy);
  }
}

void UIScalePolygon(){
  if(allPoly.size() == 0){
    cout << "There are no polygons to scale" << endl;
  }
  else{
    int selection = -1;
    while(!(1 <= selection && selection <= (int)allPoly.size())){
      cout << "Please select a polygon number to scale: " << endl;
      for(int i = 1; i <= (int)allPoly.size(); i++){
        cout << "   " << i << ") Polygon " << i << endl;
      }
      cout<< "Selection: ";
      cin >> selection; 
    }
    //turn selection into array index
    selection = selection - 1;
    float sx, sy;
    cout << "Enter the magnitude to scale in the x direction: ";
    cin >> sx;
    cout << "Enter the magnitude to scale in the y direction: ";
    cin >> sy;
    scalePolygon(selection, sx, sy);
  }
}

void UIRotatePolygon(){
  if(allPoly.size() == 0){
    cout << "There are no polygons to rotate" << endl;
  }
  else{
    int selection = -1;
    while(!(1 <= selection && selection <= (int)allPoly.size())){
      cout << "Please select a polygon number to rotate: " << endl;
      for(int i = 1; i <= (int)allPoly.size(); i++){
        cout << "   " << i << ") Polygon " << i << endl;
      }
      cout<< "Selection: ";
      cin >> selection; 
    }
    //turn selection into array index
    selection = selection - 1;
    cout << "selection:  " << selection << endl;
    int deg;
    cout << "Enter the angle of rotation (in degrees): ";
    cin >> deg;
    rotatePolygon(selection, deg);
  }
}

void UIRasterizePolygon(){
  if(allPoly.size() == 0){
    cout << "There are no polygons to rasterize" << endl;
  }
  else{
    int selection = -1;
    while(!(1 <= selection && selection <= (int)allPoly.size())){
      cout << "Please select a polygon number to rasterize: " << endl;
      for(int i = 1; i <= (int)allPoly.size(); i++){
        cout << "   " << i << ") Polygon " << i << endl;
      }
      cout<< "Selection: ";
      cin >> selection; 
    }
    //turn selection into array index
    selection = selection - 1;

    allPoly[selection]->turnOnRasterization();
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

    //write out line data
    for(int i = 0; i < (int)allLines.size(); i++){
      outfile << "L" << endl;
      //output first line coord
      outfile << allLines[i][0] << " " << allLines[i][1] << endl;
      //output second line coord
      outfile << allLines[i][2] << " " << allLines[i][3] << endl;
      //output line drawing algorithm
      outfile << allLines[i][4] << endl << endl;
    }

    //write out polygon data
    for(int p = 0; p < (int)allPoly.size(); p++){
      outfile << "P" << endl;
      //output number of points
      outfile << allPoly[p]->getNumPoints() << endl;
      //output coords
      for(int i = 0; i < allPoly[p]->getNumPoints(); i++){
        outfile << allPoly[p]->getXPoint(i) << " " << allPoly[p]->getYPoint(i) << endl;
      }
      //output rasterization state
      if(allPoly[p]->getIsRasterized()){
        outfile << 1 << endl << endl;
      }
      else{
        outfile << 0 << endl << endl;
      }
    }
  }
  else if(choice == 'n'){
  }
}

void callbackFunc(unsigned char key, int x, int y){
  //only bring up menu if "M" or m" key is pressed
  if(key == 77 || key == 109){
    int selection = -1;
    while(!(1 <= selection && selection <=8)){
      cout << "Please select an option between 1-8: " << endl;
      cout << "   1) Draw a line" << endl;
      cout << "   2) Clip a line" << endl << endl;

      cout << "   3) Draw a polygon" << endl;
      cout << "   4) Translate a polygon" << endl;
      cout << "   5) Scale a polygon" << endl;
      cout << "   6) Rotate a polygon" << endl;
      cout << "   7) Rasterize a polygon" << endl << endl;

      cout << "   8) Save scene to 'save.dat'" << endl;
      cout<< "Selection: ";
      cin >> selection;

      switch(selection){
        case 1:
          UIDrawLine();
          break;
        case 2:
          UIClipLine();
          break;
        case 3:
          UIDrawPolygon();
          break;
        case 4:
          UITranslatePolygon();
          break;
        case 5:
          UIScalePolygon();
          break;
        case 6:
          UIRotatePolygon();
          break;
        case 7:
          UIRasterizePolygon();
          break;
        case 8:
          UISaveScene();
        default:
          break;
      } 
    } 

    drawScene();
    glutPostRedisplay();
    cout << "-----Press ""M"" whilst INSIDE the display window to bring up the menu-----" << endl;
  }
}
