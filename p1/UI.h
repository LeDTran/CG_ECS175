#ifndef UI_H
#define UI_H
#include <vector>
#include <math.h>
#include <iostream>
#include "p1.h"
#include "Poly.h"
using namespace std;

void UIDrawLine();
void UIClipLine();
void UIDrawPolygon();
void UITranslatePolygon();
void UIScalePolygon();
void UIRotatePolygon();
void UIRasterizePolygon();
void UISaveScene();
void callbackFunc(unsigned char key, int x, int y);

#endif