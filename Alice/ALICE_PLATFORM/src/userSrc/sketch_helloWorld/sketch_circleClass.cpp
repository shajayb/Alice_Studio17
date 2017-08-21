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



class circle
{
public:
	vec cen;
	vec pts[100];
	bool detectedOrNot[100];

	///////// setup methods 
	void initialisePoints() // out points on a circle 
	{
		for (int i = 0; i < 100; i++)
		{
			pts[i] = vec(
				1.0 * sin(2 * PI * 1 / 100 * i), // x coordinate
				1.0 * cos(2 * PI * 1 / 100 * i), // y coordinate
				0 // z coordinate
			);

			pts[i] = pts[i] + cen; // move points relative to the location of the center
		}
	}
	
	///////// update methods 

	void reset()
	{
		for (int i = 0; i < 100; i++)detectedOrNot[i] = false;
	}
	void detect(circle &other)
	{
		for (int i = 0; i < 100; i++)
		{

			for (int j = 0; j < 100; j++)
			{
				if (pts[i].distanceTo(other.pts[j]) < .5)
				{
					detectedOrNot[i] = true;
					break;
				}
			}
		}
	}
	void expand()
	{
		for (int i = 0; i < 100; i++)
		{
			if (!detectedOrNot[i])
				pts[i] += (pts[i] - cen).normalise() * 0.1;
		}
	}

	///////// display methods 
	void display() // display the center and display the points 
	{
		drawPoint(cen);
		for (int i = 0; i < 100; i++)
		{
			drawPoint(pts[i]);
		}
	}

	///////// export methods
};



///////////////////////////////////////////////////////////// MAIN PROGRAM /////////////////////////////////////////////////////////////


circle allCircles[4];
int numOfCircles = 4;

//API application programming interface

void setup()
{

	for (int i = 0; i < numOfCircles; i++)
	{
		allCircles[i].cen = vec( ofRandom(-10,10), ofRandom(-10, 10),0);// vec(5 * i, 0, 0);
		allCircles[i].initialisePoints();
	}


}


void update(int value)
{

	for (int i = 0; i < numOfCircles; i++)
	{
		allCircles[i].reset();
	}

	for (int i = 0; i < numOfCircles; i++)
	{
		for (int j = 0; j < numOfCircles; j++)
		{
			if (i == j)continue;

			allCircles[i].detect(allCircles[j]);
		}
	}

	for (int i = 0; i < numOfCircles; i++)
	{
		allCircles[i].expand();
	}


}

/////////////////////////// view  ///////////////////////////////////////////

void draw()
{


	backGround(0.75);
	drawGrid(20);

	glPointSize(5);
	for (int i = 0; i < numOfCircles; i++)allCircles[i].display();
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