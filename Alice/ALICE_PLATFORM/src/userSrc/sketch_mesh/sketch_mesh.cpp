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

/// ----- variables

Mesh M; //empty mesh to hold meshes that will be created

void setup()
{

	cout << "HELLO UBIK" << endl;
}

void update(int value)
{


}

/////////////////////////// view  ///////////////////////////////////////////

void draw()
{


	backGround(0.75);
	drawGrid(20);

	wireFrameOn();
	M.draw();
	wireFrameOff();
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

	if (k == 'c') // create a cube
	{

		MeshFactory fac; // a mesh primitive creating factory
		M = fac.createPlatonic(3, 6);// create a polyhedra of sides 6, that fits in a sphere of radius of 3 ;
		
		// assign face normals.. this is a temporary fix in current repository. This won't be needed in the future.
		//for (int i = 0; i < M.n_f; i++)M.faces[i].faceVertices();
	}
	


	if (k == 'q') // create a quad
	{
		M = *new Mesh();
		// add vertices to M;
		float radius = 3.0;
		for (int i = 0; i < 4; i++)
		{
			float x = radius * sin(PI * 0.5 * i);
			float y = radius * cos(PI * 0.5 * i);
			M.createVertex(vec(x, y, 0));
		}

		// add face to M;.. in this case , only one face is added

		Vertex *fv[4];
		for (int i = 0; i < 4; i++)fv[i] = &M.vertices[i]; // the order of vertices of the face should be in counter clock direction.
		M.createFace(fv, 4);

		// assign face normals.. this is a temporary fix in current repository. This won't be needed in the future.
		for (int i = 0; i < M.n_f; i++)M.faces[i].faceVertices();

	}



	if (k == 'r') // create a circle
	{
		M.n_v = 0;
		M.n_f = 0;
		M.n_e = 0;
		// add vertices to M;
		int numV = 10;
		float radius = 3.0;
		for (int i = 0; i < numV; i++)
		{
			float x = radius * sin(PI * 0.5 * i);
			float y = radius * cos(PI * 0.5 * i);
			M.createVertex(vec(x, y, 0));
		}

		M.createVertex( vec(0, 0, 0) ); // central vertex of he circle
		// add face to M;.. in this case , 10 faces are to be added
		// each face consists two adjacent vertices, and the central one ( vertex 11 in this case numV+1) 

		Vertex *fv[3];
		for (int i = 0; i < numV; i++)
		{
			fv[i] = &M.vertices[i]; // the order of vertices of the face should be in counter clock direction.
			fv[i] = &M.vertices[(i + 1) % numV]; // when the last vertex is reached, its neighbor will be 0. thus use the modulo trick
			fv[i] = &M.vertices[numV + 1]; // the central vertex
			M.createFace(fv, 3);
		}

		// assign face normals.. this is a temporary fix in current repository. This won't be needed in the future.
		for (int i = 0; i < M.n_f; i++)M.faces[i].faceVertices();

	}




}





#endif // _MAIN_
