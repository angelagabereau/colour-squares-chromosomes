/*
 *  main.cpp
 *  comp446final
 *
 *  Created by Angela Gabereau on 05/12/06.
 *	ID#: 4867815
 *  COMP 446  
 *  Final Programming Project
 *
 */
#include <iostream>
#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include "stdio.h"
#include "defs.h"
#include "Individual.h"
#include "Generation.h"
#include "RouletteWheel.h"
#include "Population.h"


//Display function declarations
void myInit();
void displayPopulation ();
void idle ();

using namespace std;


// Global variables
Population * pP; //pointer to Population used to display population


int main(int argc, char ** argv)
{

	float genSize;
	float numGen;
	std::cout<<"Enter the size of a generation: ";
	std::cin>>genSize;
	std::cout<<"Enter the number of generations: ";
	std::cin>>numGen;
	std::cout<<endl<<endl;

	//**************************************************************
	//   Create Population
	//**************************************************************
	Population p((int)numGen,(int)genSize);
	
	p.run();

	p.analyze();

	pP = &p;//initialize global pointer to population 

	//**************************************************************
	//  Display Population
	//**************************************************************

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Angela Gabereau's Genetic Algorithm");
	glutDisplayFunc(displayPopulation);
	glutIdleFunc(displayPopulation);

	glutMainLoop();



return 0;
}


//*********************************************************************************
//	NOTE: The following code is code that I have reworked from a tutorial
//        on OpenGL, which can be found at:
//        http://www.rivier.edu/faculty/amoreira/web/repository/OpenGL/Checkerboard/

//*********************************************************************************


//*********************************************************************************
//	Initialize graphics.
//*********************************************************************************

void myInit()
{
	glColor(0.0,0.0,0.0);					//	black foreground
	glClearColor(1.0, 1.0, 1.0, 1.0);		//	white background
	glEnable(GL_LINE_SMOOTH);				//	enable antialiasing
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);	//	hint we want antialiasing
	glMatrixMode(GL_PROJECTION);			//	hit the projection matrix
	glLoadIdentity();						//	make it one to one
}

void displayPopulation()
{	
	myInit();

	
	glutInitWindowPosition(100,100);

	vector<Generation*>::size_type totalGens = pP->getTotalGenerations();
	vector<Individual*>::size_type genSize = pP->getSizeGenerations();



	//****************************************************************
	//	The width and height of each square.
	//****************************************************************

	int maxWindowSize=1000;
	GLint width;

	if(totalGens<50&&genSize<50){
		width = (totalGens*100);
		glutInitWindowSize(genSize*width, totalGens*width);
	}else{
		width = maxWindowSize/(totalGens);
		glutInitWindowSize(genSize*width, totalGens*width);
		
	}

	//****************************************************************
	// Scale window size to number of Individuals in Population
	//****************************************************************

	signed int x = (0-genSize/2)+genSize/2;
	gluOrtho2D(x, genSize*width, x, totalGens*width);

	//********************************************************************
	//	Loop through the population, getting a generation for each row
	//********************************************************************

	GLint top = 0;

	//outter loop: looping .
	for(vector<Generation*>::iterator iPop = pP->getPopVecBegin(); iPop != pP->getPopVecEnd(); ++iPop){

		GLint left = 0;

		glBegin(GL_QUADS);

		//********************************************************************
		//	Inner loop: looping through a generation,
		//  getting color of each individual, and displaying in window
		//********************************************************************
		
		for(vector<Individual*>::iterator iGen = (*iPop)->getGenVecBegin(); iGen != (*iPop)->getGenVecEnd(); ++iGen){

			//***********************************************
			//	Get the color of Individual 
			//***********************************************
			const double red = (*iGen)->getRed();
			const double green = (*iGen)->getGreen();
			const double blue = (*iGen)->getBlue();
			acolor c(red, green, blue);
			glColor(c);

			//***********************************************
			//	Render the square as one quad.
			//***********************************************

			glVertex(left,top);
			glVertex(left,top+width);
			glVertex(left+width, top+width);
			glVertex(left+width,top);
			//***********************************************
			//	Advance to next column.
			//***********************************************

			left = left + width;

		}

		glEnd();

		//***************************************************
		//	Advance to next row.
		//***************************************************

		top = top + width;

	}

 //	glFinish();
//	glutSwapBuffers();
	glutPostRedisplay();
}

void idle ()
{
	glutPostRedisplay();
}