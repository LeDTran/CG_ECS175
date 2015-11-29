#include "UI.h"

// void UISaveScene(){
//   char choice;
//   cout << "This will overwrite 'save.dat'. Are you sure you want to continue? (y/n): ";
//   cin >> choice;
//   if(choice == 'y'){
//     //if(save.dat exists)
//     remove("save.dat");

//     ofstream outfile;
//     outfile.open("save.dat");

//     //write out polygon data
//     for(int p = 0; p < (int)allPoly.size(); p++){
//       outfile << "P" << endl;
//       //output number of points
//       outfile << allPoly[p]->getNumPoints() << endl;
//       //output coords
//       for(int i = 0; i < allPoly[p]->getNumPoints(); i++){
//         outfile << allPoly[p]->getXPoint(i) << " " << allPoly[p]->getYPoint(i) << " " << allPoly[p]->getZPoint(i) << endl;
//       }
//       //output number of edge points
//       outfile << allPoly[p]->getNumLineP() << endl;
//       for(int i = 0; i < allPoly[p]->getNumLineP(); i++){
//         outfile << allPoly[p]->getLineP1(i)+1 << " " << allPoly[p]->getLineP2(i)+1 << endl;
//       }
//       outfile << endl;
//     }
//   }
//   else if(choice == 'n'){
//   }
// }

void changeBezierReso(){
  if(allBezier.size() == 0){
    cout << "There are no Bezier curves" << endl;
  }
  else{
    int curveselection = -1;
    while(!(1 <= curveselection && curveselection <= (int)allBezier.size())){
      cout << "Please select a Bezier curve: " << endl;
      for(int i = 1; i <= (int)allBezier.size(); i++){
        cout << "   " << i << ") Bezier curve " << i << endl;
      }
      cout<< "Selection: ";
      cin >> curveselection; 
    }
    //turn selection into array index
    curveselection = curveselection - 1;

    float reso;
    cout << "Enter the resolution: ";
    cin >> reso;

    allBezier[curveselection]->setResolution(reso);
  }
}

void changeBSplineReso(){
  if(allBSpline.size() == 0){
    cout << "There are no BSpline curves" << endl;
  }
  else{
    int curveselection = -1;
    while(!(1 <= curveselection && curveselection <= (int)allBSpline.size())){
      cout << "Please select a BSpline curve: " << endl;
      for(int i = 1; i <= (int)allBSpline.size(); i++){
        cout << "   " << i << ") BSpline curve " << i << endl;
      }
      cout<< "Selection: ";
      cin >> curveselection; 
    }
    //turn selection into array index
    curveselection = curveselection - 1;

    float reso;
    cout << "Enter the resolution: ";
    cin >> reso;

    allBSpline[curveselection]->setResolution(reso);
  }
}

void addBezierPoint(){
  if(allBezier.size() == 0){
    cout << "There are no Bezier curves" << endl;
  }
  else{
    int curveselection = -1;
    while(!(1 <= curveselection && curveselection <= (int)allBezier.size())){
      cout << "Please select a Bezier curve: " << endl;
      for(int i = 1; i <= (int)allBezier.size(); i++){
        cout << "   " << i << ") Bezier curve " << i << endl;
      }
      cout<< "Selection: ";
      cin >> curveselection; 
    }
    //turn selection into array index
    curveselection = curveselection - 1;

    float x, y;
    cout << "Enter the x coordinate of the new control point: ";
    cin >> x;
    cout << "Enter the y coordinate of the new control point: ";
    cin >> y;

    allBezier[curveselection]->addCtrlPoint(x, y);
  }
}

void addBSplinePoint(){
  if(allBSpline.size() == 0){
    cout << "There are no BSpline curves" << endl;
  }
  else{
    int curveselection = -1;
    while(!(1 <= curveselection && curveselection <= (int)allBSpline.size())){
      cout << "Please select a BSpline curve: " << endl;
      for(int i = 1; i <= (int)allBSpline.size(); i++){
        cout << "   " << i << ") BSpline curve " << i << endl;
      }
      cout<< "Selection: ";
      cin >> curveselection; 
    }
    //turn selection into array index
    curveselection = curveselection - 1;

    float x, y;
    cout << "Enter the x coordinate of the new control point: ";
    cin >> x;
    cout << "Enter the y coordinate of the new control point: ";
    cin >> y;

    allBSpline[curveselection]->addCtrlPoint(x, y);
    allBSpline[curveselection]->addKnot();
  }
}

void deleteBezierPoint(){
  if(allBezier.size() == 0){
    cout << "There are no Bezier curves" << endl;
  }
  else{
    int curveselection = -1;
    while(!(1 <= curveselection && curveselection <= (int)allBezier.size())){
      cout << "Please select a Bezier curve: " << endl;
      for(int i = 1; i <= (int)allBezier.size(); i++){
        cout << "   " << i << ") Bezier curve " << i << endl;
      }
      cout<< "Selection: ";
      cin >> curveselection; 
    }
    //turn selection into array index
    curveselection = curveselection - 1;


    int pointselection = -1;
    int numpoints = allBezier[curveselection]->getNumCtrlPoints();
    while(!(1 <= pointselection && pointselection <= numpoints)){
      cout << "Please select a point to delete: " << endl;
      for(int i = 1; i <= numpoints; i++){
        cout << "   " << i << ") " << allBezier[curveselection]->getCtrlXPoint(i-1) 
              << ", " <<  allBezier[curveselection]->getCtrlYPoint(i-1) << endl;
      }
      cout<< "Selection: ";
      cin >> pointselection; 
    }
    //turn selection into array index
    pointselection = pointselection - 1;

    allBezier[curveselection]->deleteCtrlPoint(pointselection);
  }
}

void deleteBSplinePoint(){
  if(allBSpline.size() == 0){
    cout << "There are no BSpline curves" << endl;
  }
  else{
    int curveselection = -1;
    while(!(1 <= curveselection && curveselection <= (int)allBSpline.size())){
      cout << "Please select a BSpline curve: " << endl;
      for(int i = 1; i <= (int)allBSpline.size(); i++){
        cout << "   " << i << ") BSpline curve " << i << endl;
      }
      cout<< "Selection: ";
      cin >> curveselection; 
    }
    //turn selection into array index
    curveselection = curveselection - 1;


    int pointselection = -1;
    int numpoints = allBSpline[curveselection]->getNumCtrlPoints();
    while(!(1 <= pointselection && pointselection <= numpoints)){
      cout << "Please select a point to delete: " << endl;
      for(int i = 1; i <= numpoints; i++){
        cout << "   " << i << ") " << allBSpline[curveselection]->getCtrlXPoint(i-1) 
              << ", " <<  allBSpline[curveselection]->getCtrlYPoint(i-1) << endl;
      }
      cout<< "Selection: ";
      cin >> pointselection; 
    }
    //turn selection into array index
    pointselection = pointselection - 1;

    allBSpline[curveselection]->deleteCtrlPoint(pointselection);
    allBSpline[curveselection]->deleteKnot();
  }
}

static int window;
static int menu_id;


void resoMenu(int selection){
  if(selection == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
    switch(selection){
      case 1:
        changeBezierReso();
        drawScene();
        break;
      case 2:
        changeBSplineReso();
        drawScene();
        break;
      default:
        break;
    }
  }
}

void addMenu(int selection){
  if(selection == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
    switch(selection){
      case 1:;
        addBezierPoint();
        drawScene();
        break;
      case 2: 
        addBSplinePoint();
        drawScene();
        break;
      default:
        break;
    }
  }
}

void insertMenu(int selection){
  if(selection == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
    switch(selection){
      case 1:;
        //addBezierPoint();
        drawScene();
        break;
      case 2: 
        //addBSplinePoint();
        drawScene();
        break;
      default:
        break;
    }
  }
}

void deleteMenu(int selection){
  if(selection == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
    switch(selection){
      case 1:;
        deleteBezierPoint();
        drawScene();
        break;
      case 2: 
        deleteBSplinePoint();
        drawScene();
        break;
      default:
        break;
    }
  }
}

void menu(int selection){
  if(selection == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
    switch(selection){
      // case 1:
      //   changeBezierReso();
      //   drawScene();
      //   break;
      // case 2:
      //   changeBSplineReso();
      //   drawScene();
      //   break;
      // case 3:;
      //   addBezierPoint();
      //   drawScene();
      //   break;
      // case 4: 
      //   addBSplinePoint();
      //   drawScene();
      //   break;
      case 5:
        break;
      case 6:
        break;
      case 7:
        break;
      default:
        break;
    }
  }
}  

void createMenu(void){        

  static int resomenu = glutCreateMenu(resoMenu);
  glutAddMenuEntry("Change Bezier Curve Resolution", 1);
  glutAddMenuEntry("Change BSpline Curve Resolution", 2);

  static int addmenu = glutCreateMenu(addMenu);
  glutAddMenuEntry("To Bezier Curve", 1);
  glutAddMenuEntry("To BSpline Curve", 2);

  static int insertmenu = glutCreateMenu(insertMenu);
  glutAddMenuEntry("To Bezier Curve", 1);
  glutAddMenuEntry("To BSpline Curve", 2);

  static int deletemenu = glutCreateMenu(deleteMenu);
  glutAddMenuEntry("From Bezier Curve", 1);
  glutAddMenuEntry("From BSpline Curve", 2);


  menu_id = glutCreateMenu(menu);
  glutAddSubMenu("Change Resolution", resomenu);
  glutAddSubMenu("Add Control Point", addmenu);
  glutAddSubMenu("Insert Control Point", insertmenu);
  glutAddSubMenu("Delete Control Point", deletemenu);

  // glutAddSubMenu("Turn On Half Tone Mode", 11);
  // glutAddMenuEntry("Turn Off Half Tone Mode", 12);
  // glutAddMenuEntry("Animate Rotation of Scene", 13);
  // glutAddMenuEntry("Stop Animated Rotation of Scene", 14);
  // glutAddMenuEntry("Quit", 0);     
  glutAttachMenu(GLUT_RIGHT_BUTTON);
} 
