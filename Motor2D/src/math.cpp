﻿#include "math.h"
#include <math.h>

#define DEG2RAD 0.0174532925
#define RAD2DEG 57.2957795

double Log2(double x) {
	return log(x) / log(2.0);
}

double DegSin(double degrees) {
	return sin(DEG2RAD * degrees * -1);
}

double DegCos(double degrees) {
	return cos(DEG2RAD * degrees);
}

double DegTan(double degrees) {
	return tan(DEG2RAD * degrees);
}

double DegASin(double sin) {
	return asin(sin) * RAD2DEG;
}

double DegACos(double cos) {
	return acos(cos) * RAD2DEG;
}

double DegATan(double tan) {
	return atan(tan) * RAD2DEG;
}

double DegATan2(double y, double x) {
	return atan2(y, x) * RAD2DEG;
}

double WrapValue(double val, double mod) {
    if (mod == 0) return val;
    return val - mod*floor(val/mod);
}


double Angle(double x1, double y1, double x2, double y2) {
  double tang = DegATan2(y1-y2, x2-x1);
	return WrapValue(tang, 360);
}

double Distance(double x1, double y1, double x2, double y2) {
  double xe2 = (x2 - x1) * (x2 - x1);
  double ye2 = (y2 - y1) * (y2 - y1);
	return sqrt(xe2 + ye2);
}

bool ValueInRange(double value, double min, double max) {
	return (value >= min) && (value <= max);
}

bool PointInRect(double x, double y, double rectx, double recty, double width, double height) {
	return ValueInRange(x,rectx,rectx + width) && ValueInRange(y,recty,recty + height);
}

void ClosestPointToRect(double x, double y, double rectx, double recty, double width, double height, double* outx, double* outy) {
	*outx = (x < rectx) ? rectx : (x > rectx+width) ? rectx+width : x;
	*outy = (y < recty) ? recty : (y > recty+height) ? recty+height : y;
}

bool RectsOverlap(double x1, double y1, double width1, double height1, double x2, double y2, double width2, double height2) {
  return (y1 <= y2 + height2 && x1 <= x2 + width2) && (y1 + height1 >= y2 && x1 + width1 >= x2);
}

void OverlappingRect(double x1, double y1, double width1, double height1, double x2, double y2, double width2, double height2, double* outx, double* outy, double* outwidth, double* outheight) {
  *outx = (x1 >= x2 && x1 <= x2 + width2) ? x1 : x2;
  *outy = (y1 >= y2 && y1 <= y2 + width2) ? y1 : y2;
  *outwidth = (x1 + width1 >= x2 && x1 + width1 <= x2 + width2) ? (x1 + width1) - *outx : (x2 + width2) - *outx;
  *outheight = (y1 + height1 >= y2 && y1 + height1 <= y2 + height2) ? (y1 + height1) - *outy : (y2 + height2) - *outy;
}

void TransformIsoCoords(double isoX, double isoY, double isoZ, double* screenX, double* screenY) {
  *screenX = (isoX - isoY) * 0.89415423683;
  *screenY = isoZ + (isoX + isoY) * 0.44775908783;
}
