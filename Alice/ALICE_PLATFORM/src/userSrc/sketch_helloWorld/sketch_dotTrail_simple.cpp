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
	//class properties
	vec position;
	vec velocity;
	
	vec previousPositions[50];
	int counter = 0;
	//class methods
	void move()
	{

		velocity.x = ofRandom(-1.1, 1.1);
		velocity.y = ofRandom(-1.1, 1.1);
		velocity.z = ofRandom(-1.1, 1.1);

		position = position + velocity;
		
		//store current location in previousPositions array
		previousPositions[ counter ] = position;
		
		//increase counter 
		counter = counter + 1;

		//check if counter > 50, then reset counter to 0 ;
		if (counter >= 50)
		{
			counter = 0;
		}
	}

	void display()
	{
		//draw current location
		glPointSize(5);
			drawPoint(position);
		glPointSize(1);

		//draw velocity direction as a line
		vec B = position + velocity ;
		drawLine(position, B);

		//draw previous locations 
		for (int i = 0; i < 50; i++)
		{
			drawPoint( previousPositions[i] );
		}
	}
};



dot C;
dot allDots[50];

void setup()
{
	//initialise
	C = dot();
	C.position = vec(10, 10, 0);

	//initialise
	for (int i = 0; i < 50; i++)
	{
		allDots[i] = dot();
		allDots[i].position = vec( ofRandom(-10,10), ofRandom(-10, 10), 0);
	}
}

void update(int value)
{
	//update
	//object.method()
	C.move();

	//update
	for (int i = 0; i < 50; i++)
	{
		allDots[i].move();
	}
}

/////////////////////////// view  ///////////////////////////////////////////

void draw()
{


	backGround(0.75);
	drawGrid(20);
	
	//draw
	C.display();

	//draw
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
