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

static int window;
static int menu_id;

void menu(int selection){
  if(selection == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
    switch(selection){
      case 1:
        resetValues();
        setIpValues();
        drawScene();
        break;
      case 2:
        isHalfTone = true;
        halfTone();
        break;
      case 3:
        isHalfTone = false;
        drawScene();
        break;
      case 4:
        isAnimating = true;
        startAnimation();
        break;
      case 5:
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
    // glutAddMenuEntry("Draw a Shape", 1);
    // glutAddMenuEntry("Translate a Shape", 2);
    // glutAddMenuEntry("Scale a Shape", 3);
    // glutAddMenuEntry("Rotate a Shape", 4);
    // glutAddMenuEntry("Save Scene", 5);
    glutAddMenuEntry("Reassign Values", 1);
    glutAddMenuEntry("Turn On Half Tone Mode", 2);
    glutAddMenuEntry("Turn Off Half Tone Mode", 3);
    glutAddMenuEntry("Animate Rotation of Scene", 4);
    glutAddMenuEntry("Stop Animated Rotation of Scene", 5);
    glutAddMenuEntry("Quit", 0);     
    glutAttachMenu(GLUT_RIGHT_BUTTON);
} 
