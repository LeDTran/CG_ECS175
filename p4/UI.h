#ifndef UI_H
#define UI_H
#include <vector>
#include <math.h>
#include <iostream>
#include "p4.h"
#include "Poly.h"
using namespace std;

void UIDrawPolygon();
void UITranslatePolygon();
void UIScalePolygon();
void UIRotatePolygon();
void UISaveScene();
void callbackFunc(unsigned char key, int x, int y);
void menu(int num);
void createMenu(void);

#endif