
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
	
	void display() // display the center and display the points 
	{
		drawPoint(cen);
		for (int i = 0; i < 100; i++)
		{
			drawPoint(pts[i]);
		}
	}
};


circle cir;
circle cir2;

void setup()
{
	cir.cen = vec(5, 5, 0);
	cir.initialisePoints();

	cir2.cen = vec(15, 5, 0);
	cir2.initialisePoints();
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
	cir.display();
	cir2.display();

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
