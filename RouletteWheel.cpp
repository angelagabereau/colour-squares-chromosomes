/*
 *  RouletteWheel.cpp
 *  comp446final
 *
 *  Created by Angela Gabereau on 05/12/06.
 *	ID#: 4867815
 *  COMP 446  
 *  Final Programming Project
 *
 */


/**********************************************************************

	CLASS ROULETTE WHEEL
	------------------------
	This class is responsible for selecting the Individuals for
	reproduction.  It does this using a simulation of a weighted
	roulette wheel.  The weights of each slice of the wheel is
	calculated based on the fitness of the indiviual and the sum
	of the fitnesses of the entire generation.  The marble is
	represented by a random number between 0.0 and 1.0.

***********************************************************************/

#include "WheelSlice.h"
#include "Individual.h"
#include "Generation.h"
#include "RouletteWheel.h"
#include<vector>
#include<cstdlib>
#include<cassert>
#include<iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;



/********************************************************

	CONSTRUCTORS, DESTRUCTORS
	---------------------------

*********************************************************/

RouletteWheel::RouletteWheel( Generation * g ) : generation(g), sumProbability(0), sumFitness(0) 
{ 
	/* initialize random generator */
	srand ( (unsigned)time(NULL) );
	createWheel(); 
}

RouletteWheel::~RouletteWheel()
{	
	for(vector<slice*>::iterator i = RouletteWheel::wheel.begin(); i != RouletteWheel::wheel.end(); ++i)
		delete *i;
}


/********************************************************

	FUNCTION CREATE WHEEL
	---------------------
	This function creates the roulette wheel using 
	a vector of slice objects. First the sum of all
	the fitnesses of the population is calculated.
	Then the probability index, which is the probability 
	of the Individual, (fitness/sumfitness), plus the 
	sum of the previous probabilites.  This gives each
	slice a unique probIndex, which are stored in
	increasing order in the vector.
	Each slice object is initialized with a pointer to 
	the Individual and its probIndex.  Pointers to
	the slice are stored in vector wheel.

*********************************************************/

void  RouletteWheel::createWheel()
{
	double probIndex = 0;
	double indivVitality = 0;

	RouletteWheel::calculateSumFitness();

	for(vector<Individual*>::iterator i=generation->getGenVecBegin(); i!=generation->getGenVecEnd();++i)
	{
		indivVitality = ((*i)->getFitness()/RouletteWheel::sumFitness);
		probIndex += indivVitality;
		wheel.push_back(new WheelSlice<Individual*>(probIndex, *i));
	}

	RouletteWheel::sumProbability = probIndex;

	return;

}

/********************************************************

	FUNCTION CALCULATE SUM FITNESS
	------------------------------
	This function calculates the sum of all fitnesses
	of the generation by looping through vector of
	individuals, retriving each fitness and adding
	to member data sumFitness.

*********************************************************/

void RouletteWheel::calculateSumFitness()
{

	for(vector<Individual*>::iterator i=generation->getGenVecBegin(); i!=generation->getGenVecEnd();++i)
	{
		RouletteWheel::sumFitness += (*i)->getFitness();
	}
	
	return;
}

/********************************************************

	FUNCTION SPIN
	-------------
	This function simulates a spin of a roulette wheel
	by generating a random double between 0.0 and 1.0 
	called marble.Then looping through slices looking 
	for a slice with a probIndex greater than marble 
	and the previous slice's probIndex less than marble.
	The function returns a pointer to the individual
	selected  by spin.

*********************************************************/

Individual * RouletteWheel::spin()
{
	double marble = static_cast< double >( rand() ) / RAND_MAX;
	
	//check that marble is in range, if not generate new marble
	while(marble>RouletteWheel::sumProbability)
		marble = static_cast< double >( rand() ) / RAND_MAX;

	assert( 0.0 <= marble && marble <= RouletteWheel::sumProbability);

	//invariant: the value of marble is greater than the previous slice's probIndex

	double probIndexPrevious = 0;

	for(vector<slice*>::iterator i = RouletteWheel::wheel.begin(); i != RouletteWheel::wheel.end(); ++i)
	{	
		slice* s = *i;
		double probIndex = s->getProbIndex();
		Individual * indiv = s->getData(); 
		//if marble is less than first slice's probIndex return first slices data
		if( i == wheel.begin()){
			if(marble < probIndex){ 
				return indiv; 
			}

		//if marble is greater than previous slice's probIndex and less than current slice's probIndex return slice's data
		} else if( probIndexPrevious < marble && marble < probIndex){
			return indiv;
		}

		probIndexPrevious = probIndex;
		
	}

	return 0;

}

