
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

vec allPoints[1000];

//class -> template
// instance -> specific copies or versions of the template / class 

void setup()
{
	for (int i = 0; i < 1000; i++)
	{
		allPoints[i] = vec( 10 * sin( 2 * PI / 100 * i  ) , 10 * cos(2 * PI / 100 * i), ofRandom(-1,1)) ;
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

	glPointSize(10) ; // change point size to 10
	
	for (int i = 0; i < 1000; i++)
	{
		vec A = allPoints[i];// vec(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10));
		

		float r, g, b; // empty floats r,g, and b;

		/// r = scale current X coordinate, which is i nthe range -10 to 10, into a new range from 0 to 1;
		//r = ofMap( current X, old range min, old range max, new range min, new range max );
		r = ofMap(A.x,-10, 10, 0, 1);
		g = ofMap(A.y, -10, 10, 0, 1);
		b = ofMap(A.z, -1, 1, 0, 1);

		glColor3f(r, g, b); /// r ,g ,& b, need to be in range 0,1 ;
		drawPoint(A);

		// make colored points move randomly
		vec C;
		C.x = ofRandom(-1, 1) * 0.1;
		C.y = ofRandom(-1, 1) * 0.1;
		C.z = ofRandom(-1, 1) * 0.1;

		vec B = allPoints[i] + C;
		allPoints[i] = B;
	}

	glPointSize(1); // reset point size to 1
	
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
