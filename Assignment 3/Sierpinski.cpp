/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include "math.h"
#include "simpio.h"
using namespace std;

/* function prototypes */
void drawFractal(GWindow & gw, int order, double length, GPoint p0);
void drawTriangle(GWindow & gw, GPoint p0, double length);
GPoint getInitialPoint(GWindow & gw, double length);

const double WINDOW_WIDTH = 500;
const double WINDOW_HEIGHT = 500;

int main() {
	GWindow gw(WINDOW_WIDTH, WINDOW_HEIGHT);
	double length = getReal("Base triangle side length: ");
	double order = getInteger("Fractal order: ");
	GPoint p0 = getInitialPoint(gw, length);

	drawFractal(gw, order, length, p0);
    return 0;
}

void drawFractal(GWindow & gw, int order, double length, GPoint p0) {
	drawTriangle(gw, p0, length);
	if (order == 0) return;
	GPoint pLower = gw.drawPolarLine(p0, length/2, 0);
	GPoint pUpper = gw.drawPolarLine(p0, length/2, 60);
	gw.drawLine(pUpper, pLower);
	drawFractal(gw, order - 1, length/2, p0);
	drawFractal(gw, order - 1, length/2, pLower);
	drawFractal(gw, order - 1, length/2, pUpper);
}

void drawTriangle(GWindow & gw, GPoint p0, double length) {
	GPoint p1 = gw.drawPolarLine(p0, length, 60);
	GPoint p2 = gw.drawPolarLine(p1, length, -60);
	GPoint p3 = gw.drawPolarLine(p2, length, 180);
}

GPoint getInitialPoint(GWindow & gw, double length) {
	double x = (gw.getWidth()-length)/2;
	double y = (gw.getHeight()+sqrt(3.0)/2*length/3)/2;
	return GPoint(x, y);
}