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
class dot
{
public:
	//class property
	vec A;


	//class methods / actions
	void display()
	{
		glPointSize(5);
			drawPoint(A);
		glPointSize(1);
	}

};


vec A; // put a point into model
vec allPts[50]; // put 50 points into model

dot C; // put a dot into model
dot allDots[50];// put 50 dots into model

void setup()
{

	
	////////////////////////////////////////////////////////////////////////// points


	A = vec(10, 0, 0); // initialise a point

	//initalise 50 points
	for (int i = 0; i < 50; i++)
	{
		allPts[i] = vec(ofRandom(-10, 10), ofRandom(-10, 10), 0);
	}

	////////////////////////////////////////////////////////////////////////// dots
	

	//initialise a dot
	C = dot();

	//initialise 50 dots 

	for (int i = 0; i < 50; i++)
	{
		allDots[i] = dot();
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
	
	////////////////////////////////////////////////////////////////////////// points 
	glColor3f(1, 0, 0);

	glPointSize(5);

	drawPoint(A); // draw point A
	//draw 50 points 

	for (int i = 0; i < 50; i++)
	{
		drawPoint(allPts[i]);
	}

	////////////////////////////////////////////////////////////////////////// dots
	glColor3f(1, 1, 1);

	// draw dot B
	C.display();


	//draw 50 dots;
	for (int i = 0; i < 50; i++)
	{
		allDots[i].display();
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
