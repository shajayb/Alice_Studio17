

#define _MAIN_

#ifdef _MAIN_

#include "main.h"
#include "MODEL.h"
#include <array>
#include <memory>
#include<time.h>
#include<experimental/generator> 

using namespace std;
using namespace std::experimental;
#include "sketch_spatialBinning\spatialBin.h"


///////// ----------------------------------------- model - view - controller (MVC) paradigm / pattern / template  ----------------- ////////////////////////////// 
/////////////////////////// model  ///////////////////////////////////////////

vec pts[100];


void setup()
{
	for (int i = 0; i < 100; i++)
	{
		pts[i] = vec(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10));
	}
}

void update(int value)
{


}

/////////////////////////// view  ///////////////////////////////////////////

void draw()
{


	backGround(0.75);
	drawGrid(20);


	glPointSize(5);
	glColor3f(1, 1, 1);
	for (int i = 0; i < 100; i++)
	{
		drawPoint(pts[i]);
	}

	glColor3f(1, 0, 0);
	float minimumdistance = 10000000;
	int idOfNearestPoint;
	vec A = pts[5];
	
	for (int i = 0; i < 100; i++)
	{
		if (i == 5)continue;

		vec B = pts[i];
		vec C = B - A;
		float distance = C.mag();
		
		if (distance < minimumdistance)
		{
			minimumdistance = distance;
			idOfNearestPoint = i;
		}
	}

	glColor3f(1, 0, 0);
	drawCircle(A, 0.3, 32);
	vec nearestPoint = pts[idOfNearestPoint];
	drawLine(A, nearestPoint);

	glPointSize(1);
}

/////////////////////////// control  ///////////////////////////////////////////
void mousePress(int b, int state, int x, int y)
{
}

void mouseMotion(int x, int y)
{
}

void keyPress(unsigned char k, int xm, int ym)
{

	


}





#endif // _MAIN_
