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

class circle
{
public:
	float radius;

	void display()
	{
		for (int i = 0; i < 100; i++)
		{
			vec A = vec(radius * sin(2 * PI / 100 * i), radius * cos(2 * PI / 100 * i), 0);
			vec nextA = vec(radius * sin(2 * PI / 100 * (i+1)), radius * cos(2 * PI / 100 * (i+1)), 0);

			drawPoint(A);

			float r, g, b;
			r = ofMap(A.x, -radius, radius, 0, 1);
			g = ofMap(A.y, -radius, radius, 0, 1);
			b = ofMap(A.z, -radius, radius, 0, 1);
			glColor3f(r, g, b);
			drawLine(A, nextA);
		}
	}
};



// class attributes : radius ;
// class methods or class actions : draw()

//////////////////////////////////////////////////////////////////////////
circle myC;
circle allCircles[100];

void setup()
{

}

void update(int value)
{


}

/////////////////////////// view  ///////////////////////////////////////////

void draw()
{


	backGround(0.75);
	drawGrid(20);

	myC.radius = 10.1;
	myC.display();



	for (int i = 0; i < 100; i++)
	{
		allCircles[i].radius = i; 
		allCircles[i].display();
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
