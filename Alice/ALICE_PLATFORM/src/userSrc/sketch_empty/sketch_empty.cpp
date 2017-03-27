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


// model - view - controller (MVC) paradigm / pattern / template 

//////////////////////////////////////////////////////////////////////////

void setup()
{

}

void draw()
{

	double ht = 350;
	double ht_plus = 20;

	backGround(0.75);
	drawGrid(20);


}



void mousePress(int b, int state, int x, int y)
{
}


///////////////////////////////////////////////////////////////////////////////////////////////
void update(int value)
{
}

void mouseMotion(int x, int y)
{
}

void keyPress(unsigned char k, int xm, int ym)
{

}





#endif // _MAIN_
