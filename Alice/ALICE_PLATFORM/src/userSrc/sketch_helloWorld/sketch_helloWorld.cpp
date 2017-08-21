#define  _MAIN_

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
vec A(5, 0, 0);
list<vec> A_pts;
float inc = 0.005;

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

	glPointSize(1);

	// update rule for a circle
	vec tangent;
	tangent.x = (A.y) * 0.01;
	tangent.y = (A.x) * -0.01;
	/*tangent.x = ofRandom(-0.1, 0.1);
	tangent.y = ofRandom(-0.1, 0.1);*/

	vec Anew = A + tangent;
	A = Anew;

	int numberofPts = A_pts.size();
	int remainder = numberofPts % 10;

	if (remainder == 0) // every 1000 points
	{
		inc = inc * -1;
		//A = A * (1.0 + inc); // 1.0005 --> 1.0 + 0.0005
	}

	A = A * (1.0 + inc);

	drawPoint(A);

	A_pts.push_back(A);
	// principle of differential curves
	// --> find the tangent of the curve  

	// draw all the points in A_pts ;
	for (auto pt : A_pts)
	{
		drawPoint(pt);
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



	// update rule for some other curve


}





#endif // _MAIN_