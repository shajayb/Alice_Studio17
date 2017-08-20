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
#include "nachi.h"

///////// ----------------------------------------- model - view - controller (MVC) paradigm / pattern / template  ----------------- ////////////////////////////// 
/////////////////////////// model  ///////////////////////////////////////////
/// ----- variables
pathImporter path;
EndEffector EE;


void setup()
{
	path.readPath("data/path_tmp.txt", ",", 0.0);

	EE = *new EndEffector("data/EE_disp.obj");
}

void update(int value)
{
	path.updateForwardKinematics();

}


Matrix4 ToolTip, J5;

/////////////////////////// view  ///////////////////////////////////////////

void draw()
{


	backGround(0.75);
	drawGrid(20);

	drawCircle(vec(0, 0, 0), 2, 64);

	path.draw();

	//EE.draw();
	//path.drawFrame(ToolTip, 3);
	//path.drawFrame(J5, 3);
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

	///// ROBOT PROGRAM / PATH CHECKING 

	if (k == 'n')path.goToNextPoint();
	if (k == 'b')
	{
		path.currentPointId -= 2;;
		path.goToNextPoint();
	}
	if (k == 'N')path.currentPointId = 0;
	if (k == 'q')path.checkPathForReachability();
	if (k == 'w')path.exportGCode();
	if (k == 'r')setup();

	if (k == 'h')
	{
		for (int i = 0; i < DOF; i++)path.Nachi_tester.rot[i] = 0.;
		path.Nachi_tester.rot[1] = 90.0;
		path.Nachi_tester.ForwardKineMatics(path.Nachi_tester.rot);
	}

	if (k == 'i')
	{
		//vec p;
		///*Matrix4 transJ5toToolTip;
		//transJ5toToolTip.setColumn(3, EE.cen);
		//transJ5toToolTip.setColumn(0, vec(EE.XA * EE.XA_f, EE.XA * EE.YA_f, EE.XA * EE.ZA_f));
		//transJ5toToolTip.setColumn(1, vec(EE.YA * EE.XA_f, EE.YA * EE.YA_f, EE.YA * EE.ZA_f));
		//transJ5toToolTip.setColumn(2, vec(EE.ZA * EE.XA_f, EE.ZA * EE.YA_f, EE.ZA * EE.ZA_f));*/



		ToolTip.setColumn(0, EE.XA);
		ToolTip.setColumn(1, EE.YA);
		ToolTip.setColumn(2, EE.ZA);
		ToolTip.setColumn(3, EE.cen);

		
		J5.setColumn(0, EE.XA_f);
		J5.setColumn(1, EE.YA_f);
		J5.setColumn(2, EE.ZA_f);
		J5.setColumn(3, EE.cen_f);

		Matrix4 invertJ5andToolTip;
		invertJ5andToolTip = ToolTip;

		////

		invertJ5andToolTip.invert();

		transformFrame(invertJ5andToolTip, ToolTip);
		transformFrame(invertJ5andToolTip, J5 );

		for (int i = 0; i < EE.M.n_v; i++)EE.M.positions[i] = invertJ5andToolTip * EE.M.positions[i];
		
	}

	if (k == 'I')
	{
#define rx ofRandom(-1,1)
		


		//////////////////////////////////////////////////////////////////////////

		Matrix4 forwardJ5andToolTip;
		
		vec cen(20,20,0);
		/*cen.normalise();
		cen *= 10;*/
		vec x(rx, rx, rx);
		vec y = x.cross(vec(0, 1, 0));
		vec z = x.cross(y);
		x.normalise(); y.normalise(); z.normalise();
		
		forwardJ5andToolTip.setColumn(3, cen);
		forwardJ5andToolTip.setColumn(0, x);
		forwardJ5andToolTip.setColumn(1, y);
		forwardJ5andToolTip.setColumn(2, z);

		
		transformFrame(forwardJ5andToolTip, ToolTip);
		transformFrame(forwardJ5andToolTip, J5);

		for (int i = 0; i < EE.M.n_v; i++)EE.M.positions[i] = forwardJ5andToolTip * EE.M.positions[i];
	}
}





#endif // _MAIN_
