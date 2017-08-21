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

void setup()
{
	
}

void update(int value)
{


}

/////////////////////////// view  ///////////////////////////////////////////

void draw()
{


	backGround(0.75) ;
	drawGrid(20) ;

	glPointSize(5) ;

	float R = 10 ;

	// for( initial value ; till value ; increment)
	// for loop
	for( float parameter = 0.0 ; parameter < 2.0 ; parameter += 0.1 )
	{
		float x = R * cos(PI * parameter);
		float y = R * sin(PI * parameter);

		x += 10;
		y += 10; 

		drawPoint(vec(x, y, 0));
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
