
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
	float radius;
	vec pts[20];
	bool detectedOrNot[20];

	void initialisePoints()
	{
		radius = 1.0;
		for (int i = 0; i < 20; i++)
		{
			pts[i] = vec(
					1.0 * sin(2 * PI * 1 / 20.0 * i), 
					1.0 * cos(2 * PI * 1 / 20.0 * i), 
					0);

			pts[i] += cen;
		}
	}

	void detect( circle &otherCircle )
	{
		for (int i = 0; i < 20; i++) // looping through all 20 of my points
		{
			// looping through all 20 of the points of other circle
			for (int j = 0; j < 20; j++)
			{
				float distance = pts[i].distanceTo( otherCircle.pts[j] );
				//calculate distance between
				// Point i of my circle with point j of the other circle
				// and store the distance in a variable called distance
				if (distance < 1.0 )
				{
					detectedOrNot[i] = true;
					break;
				}
				else
				{
					detectedOrNot[i] = false;
				}
			}
		}

	}

	void move()
	{
		cen += vec(0.1, 0.1, 0);
	}

	void expand()
	{
		for (int i = 0; i < 20; i++)
		{
			if (detectedOrNot[i] == false)
			{
				pts[i] += (pts[i] - cen).normalise() * 0.1;
			}
			
		}
	}

	void display()
	{
		drawPoint(cen);
		for (int i = 0; i < 20; i++)
		{
			if (detectedOrNot[i] == true)
			{
				glColor3f(1, 0, 0);
			}
			else
			{
				glColor3f(1, 1, 1);
			}

			drawPoint(pts[i]);
		}
	}

};

circle cir1;
circle cir2;

void setup()
{

	cir1.cen = vec(5, 5, 0);
	cir1.initialisePoints();

	cir2.cen = vec(10, 10, 0);
	cir2.initialisePoints();
}


void update(int value)
{
	
	cir1.detect(cir2);
	cir1.expand();

	cir2.detect(cir1);
	cir2.expand();
}

/////////////////////////// view  ///////////////////////////////////////////

void draw()
{


	backGround(0.75);
	drawGrid(20);

	glPointSize(5);
		cir1.display();	
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
