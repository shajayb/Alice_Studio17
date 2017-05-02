

#ifdef _MAIN_



#include "main.h"
#include "ALICE_ROBOT_DLL.h"
using namespace ROBOTICS;
#include <thread>
#include <mutex>
//#include <iostream>

#include "sketch_spatialBinning\spatialBin.h"

#define rx ofRandom(-1,1)
#define NUMBER_OF_POINTS 5000
vec pos[NUMBER_OF_POINTS];

spaceGrid grd;
//SliderGroup S;
double avgElapsed;
int cnt;
bool sb = true;
bool mt = true;
bool drawVoxels = true;


struct integer2
{
	int str_id;
	int end_id;

	integer2()
	{

	}
	integer2(int a1, int a2)
	{
		str_id = a1;
		end_id = a2;
	}
};


//vector<int2> threadEdges;
std::vector<std::thread> th;
mutex mu;
integer2 threadEdges[MAX_EDGES];
int e_cnt = 0;

void setup()
{
	//glDisable(GL_LINE_SMOOTH);
	for (int i = 0; i < NUMBER_OF_POINTS; i++)pos[i] = vec(rx, rx, rx).normalise() * 50;
	
	// pass the pointer (by reference) to the vec array (pos) to the connstructor of grd class ;
	// thus when locations of the vectors in the pos array changes, the vec array inside grd is automatically updated
	// downside : you have to destruct grd when pos goes out of scope or is invalid;

	// CONSTRUCT A UNIFORM SPATIAL GRID-BIN , DEFAULT RESOLUTION IN 30 X 30 X 30 ;
	// grid resolution is a parameter that needs to be tuned to specific point distributions, for best performance
	// for highly uneven distribution of points, consider other spatial bins such as octree, kdtree etc.

	grd = *new spaceGrid(pos, NUMBER_OF_POINTS); 
	avgElapsed = 0;
	cnt = 1;
	e_cnt = 0;

}

void update(int value)
{

	// update locations of points in pos array
	for (int i = 0; i < NUMBER_OF_POINTS; i++)pos[i] += vec(rx, rx, rx).normalise() * 0.1;
	// re-compute the spatial binning
	// notice the grd.positions array doesn't need to be updated;
	grd.PartitionParticlesToBuckets();
}





void drawLine_parallel( int &a,int &b)
{
//	std::lock_guard<std::mutex> lock(mu);
		if (e_cnt >= MAX_EDGES)e_cnt = 0;
	//threadEdges.push_back(int2(a,b));
	threadEdges[e_cnt] = integer2(a, b);
	e_cnt++;
}

void updateKernel(int L, int R)
{
	
	for (int i = L; i < R; i++)
	{
		int *nbors;
		
		int n = grd.getNeighBors(nbors, pos[i], 3);
		for (int j = 0; j < n; j++)drawLine_parallel(i, nbors[j]);
	}
}

void draw()
{
	backGround(0.95);

	S.draw();

	////////////////////////////////////////////////////////////////////////// DRAW STATS

	wireFrameOn();

		if (drawVoxels)grd.drawBuckets();
		grd.drawParticlesInBuckets();

	wireFrameOff();

	////////////////////////////////////////////////////////////////////////// COMPUTE N-N DISTANCE AND DRAW DISTANCE-CONDITIONAL LINES

	// draw lines to nearest neighbors of each point in pos array;
	// compare compute time with brute force method.
	long start = GetTickCount();



		int *nbors;
		e_cnt = 0;

		if (sb)
			if (mt)
			{
				int nt = thread::hardware_concurrency() - 1;
				int numParticlesPerBlock = NUMBER_OF_POINTS / nt;

				th.clear();
				//threadEdges.clear();
				e_cnt = 0;
				for (int i = 0; i < NUMBER_OF_POINTS - numParticlesPerBlock; i += numParticlesPerBlock)
					th.push_back(std::thread(updateKernel, i, i + numParticlesPerBlock));

				for (auto &t : th)t.join();

				for (auto &t : threadEdges)drawLine(pos[t.str_id], pos[t.end_id]);
			}
			else
			{
				for (int i = 0; i < NUMBER_OF_POINTS; i++)
				{
					int n = grd.getNeighBors(nbors, pos[i], 3);
					for (int j = 0; j < n; j++)drawLine_parallel(i, nbors[j]);// drawLine(pos[i], pos[nbors[j]]);

				}

				for (auto &t : threadEdges)drawLine(pos[t.str_id], pos[t.end_id]);
			}
		else
			for (int i = 0; i < NUMBER_OF_POINTS; i++)
				for (int j = 0; j < NUMBER_OF_POINTS; j++)
				{
					if (i == j)continue;
					if ((pos[i] - pos[j]) *(pos[i] - pos[j]) < 3 * 3)
						drawLine(pos[i], pos[j]);
				}
	
	long end = GetTickCount();
	avgElapsed += end - start;
	cnt++;

	////////////////////////////////////////////////////////////////////////// DRAW STATS

	char s[200];
	char s_sb[200];
	char s_help[200];
	sprintf(s, " num particles %i | bin resolution %i | avg compute time in millisec %1.2f", NUMBER_OF_POINTS, RES, double(avgElapsed) / double(cnt));
	sprintf(s_sb, " spatialBin %i | multiThreading %i ", int(sb), int(mt));
	sprintf(s_help, " r - restart ; s - toggle spatial-binning ; m - toggle multi-threading ; d - toggle voxel draw ");

	glColor3f(0, 0, 0);
	setup2d();

		drawString(s, 50,50);
		drawString(s_sb, 50,75);
		drawString(s_help, 50,100);

	restore3d();

}

void keyPress(unsigned char k, int xm, int ym)
{
	if (k == 'r')setup();
	if (k == 'd')drawVoxels = !drawVoxels;
	if (k == 'm')
	{
		mt = !mt;
		setup();
	}
	if (k == 's')
	{
		sb = !sb;
		setup();
	}
}

void mousePress(int b, int state, int x, int y)
{
	if (GLUT_LEFT_BUTTON == b && GLUT_DOWN == state)
	{
		S.performSelection(x, y, HUDSelectOn);
//		B.performSelection(x, y);
	}
}

void mouseMotion(int x, int y)
{
	//if (GLUT_LEFT_BUTTON == b && GLUT_DOWN == s)
	{
		S.performSelection(x, y, HUDSelectOn);
	}
}



#endif // _MAIN_