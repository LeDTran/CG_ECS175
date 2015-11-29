#include "UI.h"

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
    cout << "Enter the new resolution: ";
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
    cout << "Enter the new resolution: ";
    cin >> reso;

    allBSpline[curveselection]->setResolution(reso);
  }
}

void insertBezierPoint(){
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

    int pos = -1;
    int numpoints = allBezier[curveselection]->getNumCtrlPoints();
    while(!(1 <= pos && pos <= numpoints+1)){
      //cout << "Please select a point to delete: " << endl;
      for(int i = 1; i <= numpoints; i++){
        cout << "(" << allBezier[curveselection]->getCtrlXPoint(i-1) << ", " 
              <<  allBezier[curveselection]->getCtrlYPoint(i-1) << ") ";
      }
      cout << endl;

      cout << "Select where to to insert a new control point: " << endl;
      for(int i = 0; i <= numpoints; i++){
        if(i == 0){
          cout << "   1) At the beginning" << endl;
        }
        else{
          cout << "   " << i+1 << ") After " << allBezier[curveselection]->getCtrlXPoint(i-1) 
              << ", " <<  allBezier[curveselection]->getCtrlYPoint(i-1) << endl;
        }
      }
      cout<< "Selection: ";
      cin >> pos; 
    }
    //turn selection into array index
    pos = pos - 1;

    float x, y;
    cout << "Enter the x coordinate of the new control point: ";
    cin >> x;
    cout << "Enter the y coordinate of the new control point: ";
    cin >> y;

    allBezier[curveselection]->insertCtrlPoint(pos, x, y);
  }
}

void insertBSplinePoint(){
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

    int pos = -1;
    int numpoints = allBSpline[curveselection]->getNumCtrlPoints();
    while(!(1 <= pos && pos <= numpoints+1)){
      //cout << "Please select a point to delete: " << endl;
      for(int i = 1; i <= numpoints; i++){
        cout << "(" << allBSpline[curveselection]->getCtrlXPoint(i-1) << ", " 
              <<  allBSpline[curveselection]->getCtrlYPoint(i-1) << ") ";
      }
      cout << endl;

      cout << "Select where to to insert a new control point: " << endl;
      for(int i = 0; i <= numpoints; i++){
        if(i == 0){
          cout << "   1) At the beginning" << endl;
        }
        else{
          cout << "   " << i+1 << ") After " << allBSpline[curveselection]->getCtrlXPoint(i-1) 
              << ", " <<  allBSpline[curveselection]->getCtrlYPoint(i-1) << endl;
        }
      }
      cout<< "Selection: ";
      cin >> pos; 
    }
    //turn selection into array index
    pos = pos - 1;

    float x, y;
    cout << "Enter the x coordinate of the new control point: ";
    cin >> x;
    cout << "Enter the y coordinate of the new control point: ";
    cin >> y;

    allBSpline[curveselection]->insertCtrlPoint(pos, x, y);
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

void modifyBezierPoint(){
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
      cout << "Please select a point to modify: " << endl;
      for(int i = 1; i <= numpoints; i++){
        cout << "   " << i << ") " << allBezier[curveselection]->getCtrlXPoint(i-1) 
              << ", " <<  allBezier[curveselection]->getCtrlYPoint(i-1) << endl;
      }
      cout<< "Selection: ";
      cin >> pointselection; 
    }
    //turn selection into array index
    pointselection = pointselection - 1;

    float x, y;
    cout << "Enter the new x coordinate for this control point: ";
    cin >> x;
    cout << "Enter the new y coordinate for this control point: ";
    cin >> y;

    allBezier[curveselection]->modifyCtrlPoint(pointselection, x, y); 
  }
}

void modifyBSplinePoint(){
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
      cout << "Please select a point to modify: " << endl;
      for(int i = 1; i <= numpoints; i++){
        cout << "   " << i << ") " << allBSpline[curveselection]->getCtrlXPoint(i-1) 
              << ", " <<  allBSpline[curveselection]->getCtrlYPoint(i-1) << endl;
      }
      cout<< "Selection: ";
      cin >> pointselection; 
    }
    //turn selection into array index
    pointselection = pointselection - 1;

    float x, y;
    cout << "Enter the new x coordinate for this control point: ";
    cin >> x;
    cout << "Enter the new y coordinate for this control point: ";
    cin >> y;

    allBSpline[curveselection]->modifyCtrlPoint(pointselection, x, y); 
  }
}

void changeOrderk(){
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

    float k;
    cout << "Enter the new order k: ";
    cin >> k;

    allBSpline[curveselection]->setKValue(k); 
  }
}

void modifyKnots(){
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


    vector<float> u = allBSpline[curveselection]->getKnots();
    int pointselection = -1;
    while(!(1 <= pointselection && pointselection <= (int)u.size())){
      cout << "Please select a knot value to modify: " << endl;
      for(int i = 1; i <= (int)u.size(); i++){
        cout << "   " << i << ") " << u[i-1] << endl;
      }
      cout<< "Selection: ";
      cin >> pointselection; 
    }
    //turn selection into array index
    pointselection = pointselection - 1;

    float knot;
    cout << "Enter the new knot value: ";
    cin >> knot;

    allBSpline[curveselection]->modifyKnot(pointselection, knot); 
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

    //write out bezier data
    for(int i = 0; i < (int)allBezier.size(); i++){
      outfile << "bz" << endl;
      //output num control points
      outfile << allBezier[i]->getNumCtrlPoints() << endl;
      //output control points
      for(int j = 0; j < (int)allBezier[i]->getNumCtrlPoints(); j++){
        outfile << allBezier[i]->getCtrlXPoint(j) << " " << allBezier[i]->getCtrlYPoint(j) << endl;
      }
      outfile << endl;
    }

    //write out bspline data
    for(int i = 0; i < (int)allBSpline.size(); i++){
      //allBSpline[i]->printData();
      outfile << "bs" << endl;
      //output num control points
      outfile << allBSpline[i]->getNumCtrlPoints() << endl;
      //output k value
      outfile << allBSpline[i]->getKValue() << endl;
      //output knot existence specification (default to true)
      outfile << "T" << endl;
      //output control points
      for(int j = 0; j < (int)allBSpline[i]->getNumCtrlPoints(); j++){
        outfile << allBSpline[i]->getCtrlXPoint(j) << " " << allBSpline[i]->getCtrlYPoint(j) << endl;
      }
      //output knot values
      vector<float> u = allBSpline[i]->getKnots();
      for(int j = 0; j < (int)u.size(); j++){
        outfile << u[j] << endl;
      }
      outfile << endl; 
    }
  }
  else if(choice == 'n'){
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

void insertMenu(int selection){
  if(selection == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
    switch(selection){
      case 1:;
        insertBezierPoint();
        drawScene();
        break;
      case 2: 
        insertBSplinePoint();
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

void modifyMenu(int selection){
  if(selection == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
    switch(selection){
      case 1:;
        modifyBezierPoint();
        drawScene();
        break;
      case 2: 
        modifyBSplinePoint();
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
      case 1:
        changeOrderk();
        drawScene();
        break;
      case 2:
        modifyKnots();
        drawScene();
        break;
      case 3:;
        UISaveScene();
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

  static int insertmenu = glutCreateMenu(insertMenu);
  glutAddMenuEntry("To Bezier Curve", 1);
  glutAddMenuEntry("To BSpline Curve", 2);

  static int deletemenu = glutCreateMenu(deleteMenu);
  glutAddMenuEntry("From Bezier Curve", 1);
  glutAddMenuEntry("From BSpline Curve", 2);

  static int modifymenu = glutCreateMenu(modifyMenu);
  glutAddMenuEntry("Of Bezier Curve", 1);
  glutAddMenuEntry("Of BSpline Curve", 2);

  menu_id = glutCreateMenu(menu);
  glutAddSubMenu("Change Resolution", resomenu);
  glutAddSubMenu("Insert Control Point", insertmenu);
  glutAddSubMenu("Delete Control Point", deletemenu);
  glutAddSubMenu("Modify Control Point", modifymenu);
  glutAddMenuEntry("Change BSpline Order k", 1);
  glutAddMenuEntry("Modify BSpline Knot Values", 2);
  glutAddMenuEntry("Save Scene", 3);
  glutAddMenuEntry("Quit", 0);     
  glutAttachMenu(GLUT_RIGHT_BUTTON);
} 
