

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
	//class attributes / properties 
	vec position; 
	vec vel;
	vec trail[100];
	int cnt = 0;

	void move()
	{
		vel.x += ofRandom(-0.1, 0.1);
		vel.y += ofRandom(-0.1, 0.1);
		vel.z += ofRandom(-0.1, 0.1);
		
		trail[cnt++] = position;
		if (cnt >= 100)cnt = 0;

		position += vel * 0.1;
	}
	//class methods
	void display()
	{
		glPointSize(5);
			drawPoint(position);
			drawLine(position, position + vel.normalise());
		glPointSize(1);

		for (int i = 1; i < 100; i++)
		{
			float r = ofMap(i, 0, 100, 0, 1);
			glColor3f(r, 0, 0);
			drawPoint(trail[i]);
		}
	}
};


// class attributes : radius ;
// class methods or class actions : draw()
// instances 

 // OBJECT-ORIENTED PROGAMMING 
//
//////////////////////////////////////////////////////////////////////////
dot allDots[10000]; // 1000 empty dots, with inital position at 0,0,0

void setup()
{
	for (int i = 0; i < 1000; i++)allDots[i].position = vec(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10)).normalise();

}

void update(int value)
{

	for (int i = 0; i < 100; i++)
	{
		allDots[i].move();
	}

}

/////////////////////////// view  ///////////////////////////////////////////

void draw()
{


	backGround(0.75);
	drawGrid(20);


	for (int i = 0; i < 1000; i++)
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
