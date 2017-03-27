#include "main.h"
#include "ALICE_ROBOT_DLL.h"
using namespace ROBOTICS;

double zTol = 0.1;
bool run = false; 

void setup()
{

	S.addSlider(&zTol, "zTol");
	B.addButton(&run, "run");
}

void update(int value)
{
	if(run)
	cout << zTol << endl;
}

void draw()
{

	backGround(0.75);
	drawGrid(20.0);

}

void keyPress(unsigned char k, int xm, int ym)
{

	
}

void mousePress(int b, int state, int x, int y)
{

}

void mouseMotion(int x, int y)
{
	
}



