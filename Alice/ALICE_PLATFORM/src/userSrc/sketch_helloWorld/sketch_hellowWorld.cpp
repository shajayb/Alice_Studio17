

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

vec myPoints[100];


void setup()
{
	// put all the 100 points on a circle 
	for (int i = 0; i < 100; i++)
	{
		//create empty point - pointOnCircle
		vec pointOnCircle;
		
		// calculate the angle parameter of the point, in radians

		float anglebetweenPoints = 360.0 / 100; // in degrees
		float angleofCurrentPoint = anglebetweenPoints * i;// in degrees
		float angleInRadians = angleofCurrentPoint * DEG_TO_RAD; // convert degrees to radians

		// calculate x coordinate : r * sin(angle)
		pointOnCircle.x = 5.0 * sin(angleInRadians);

		// calculate y coordinate : r * cos(angle)
		pointOnCircle.y = 5.0 * cos(angleInRadians);

		// put the calculated point back into the array ;
		myPoints[i] = pointOnCircle;

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

	// for each point in myPoints , do action
	for (int i = 0; i < 100; i += 1)
	{
		glPointSize(5);
		// make empty vector C
		vec C; 

		// assign random values to x,y,z coordinates of C
		C.x = ofRandom(-0.1, 0.1);
		C.y = ofRandom(-0.1, 0.1);
		C.z = ofRandom(-0.1, 0.1);

		// add C to the current point , store results in vector B ;
		vec B = myPoints[i] + C;

		// put back B in the array

		myPoints[i] = B;

		//draw the updated point ;
		drawPoint(myPoints[i]);

		glPointSize(1);
	}

	
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
