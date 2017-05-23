
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
	bool interescting[100];

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
	
	void reset()
	{
		for (int i = 0; i < 100; i++)interescting[i] = false;
	}
	void checkIfIntersecting( circle &other)
	{
		for (int i = 0; i < 100; i++)
		{

			for (int j = 0; j < 100; j++)
			{
				if (pts[i].distanceTo(other.pts[j]) < .5)
				{
					interescting[i] = true;
					break;
				}
			}
		}
	}

	void moveOutward()
	{
		for (int i = 0; i < 100; i++)
		{
			if( ! interescting[i])
			pts[i] += (pts[i] - cen).normalise() * 0.1;
		}
	}

	void display() // display the center and display the points 
	{
		drawPoint(cen);
		for (int i = 0; i < 100; i++)
		{
			drawPoint(pts[i]);
		}
	}
};


circle circles[5];


//////////////////////////////////////////////////////////////////////////



void setup()
{
	

	for (int i = 0; i < 5 ; i++)
	{
		circles[i].cen = vec( ofRandom(-5,5), ofRandom(-5, 5), 0);
		circles[i].initialisePoints();
	}
}


void update(int value)
{
	for (int i = 0; i < 5; i++)
	{
		circles[i].reset();
	}

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			if (i == j)continue;
			circles[i].checkIfIntersecting(circles[j]);
		}

	for (int i = 0; i < 5; i++)
	{
		circles[i].moveOutward();
	}


}

/////////////////////////// view  ///////////////////////////////////////////

void draw()
{


	backGround(0.75);
	drawGrid(20);

	glPointSize(5);

	for (int i = 0; i < 5; i++)
	{
		circles[i].display();
	}

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
