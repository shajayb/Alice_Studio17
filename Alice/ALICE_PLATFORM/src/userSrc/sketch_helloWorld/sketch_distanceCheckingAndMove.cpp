
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
// idea : make 100 points, make them move towards nearest neighbor ;

vec pts[100];
vec A;
vec nearestPoint;

// defining a function 
void moveTowardsNearest( vec &pointToBeMoved , vec *allPts )
{
	float minDistance = 1000000;

	for (int i = 0; i < 100; i++)
	{
		vec B = allPts[i]; // pts
		vec C = B - pointToBeMoved;
		float distance = C.mag();

		if (distance < minDistance && distance > 1)
		{
			minDistance = distance;
			nearestPoint = B;
		}
	}

	//
	vec DirectionToMoveAlong = nearestPoint - pointToBeMoved; // replace A with pointToBeMoved
	DirectionToMoveAlong.normalise();
	DirectionToMoveAlong *= 0.001;
	pointToBeMoved = pointToBeMoved + DirectionToMoveAlong;// replace A with pointToBeMoved

}


void setup()
{
	for (int i = 0; i < 100; i++)
	{
		pts[i] = vec(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10));
	}

	A = vec(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10));
}


void update(int value)
{
	// write CODE here
	// make all 100 points move towards their nearest neighbor ; 

		// ST1;;
		// make 1 of the points move towards its neighbor
			// SST1
			// find the nearest neighbor
					// SSST1
					// check distances to all and find least distance 
					//and the point corresponding to the least distance
		
	// writing a function 
	// a block of code with some inputs (optional)
	// but it does some action
					
	// calling a function ;
	moveTowardsNearest(A, pts);

}

/////////////////////////// view  ///////////////////////////////////////////

void draw()
{


	backGround(0.75);
	drawGrid(20);

	glPointSize(5);
	for (int i = 0; i < 100; i++)
	{
		drawPoint(pts[i]);
	}

	glPointSize(1);

	glColor3f(1, 0, 0);
	drawLine(A, nearestPoint);

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
