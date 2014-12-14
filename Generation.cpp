/*
 *  Generation.cpp
 *  comp446final
 *
 *  Created by Angela Gabereau on 05/12/06.
 *	ID#: 4867815
 *  COMP 446  
 *  Final Programming Project
 *
 */

/**********************************************************************

	CLASS GENERATION
	-----------------
	This class provides the data structure for a generation, a vector
	containing pointers to the Individuals of this generation. It 
	provides limited functionality, just ability to calculate the 
	average fitness of the generation.  The remaining function provide
	ability to access Indivduals and add Individuals


***********************************************************************/

#include "Individual.h"
#include "Generation.h"
#include<vector>
#include<iostream>

using namespace std;

/********************************************************

	CONSTRUCTORS, DESTRUCTORS
	---------------------------
	Default constructor reserve a vector of size 50
	the other reserves a vecotor of genSize.

*********************************************************/

Generation::Generation() : genSize(50), averageFitness(0)
{
	Generation::genVec.reserve(Generation::genSize);
}


Generation::Generation(vector<Individual*>::size_type genSize) : genSize(genSize), averageFitness(0) 
{	
	Generation::genVec.reserve(genSize);
}

Generation::~Generation(){

	for(vector<Individual*>::iterator i = Generation::genVec.begin(); i!=Generation::genVec.end(); ++i)
		delete *i;
}

Generation::Generation(Generation & other) : genSize(other.genSize), averageFitness(other.averageFitness){

	vector<Individual*>::const_iterator j = other.getGenVecBegin();
	for(vector<Individual*>::iterator i = Generation::genVec.begin(); i!=Generation::genVec.end(); ++i){
		*i = new Individual((*j)->getChromosome(), (*j)->getparent1(), (*j)->getparent2());
		++j;
	}
}
	
Generation & Generation::operator=(Generation & other){
	if(this==&other)
		return *this;
	Generation::genSize = other.getGenVecSize();
	Generation::averageFitness = other.getAverageFitness();
	vector<Individual*>::const_iterator j = other.getGenVecBegin();
	for(vector<Individual*>::iterator i = Generation::genVec.begin(); i!=Generation::genVec.end(); ++i){
		*i = *j;
		++j;
	}


	return *this;
}

/********************************************************

	FUNCTION ADD INDIVIDUAL
	------------------------
	This function adds an Individual to the generation 
	by pushing a pointer to an Individual onto the
	vector

*********************************************************/

void Generation::addIndividual(Individual * i){

	if((vector<Individual*>::size_type)Generation::genVec.size()<Generation::genSize){
		Generation::genVec.push_back(i);
	}else{
		cerr<<"Generation is full, Individual can not be added"<< endl;
	}

	return;
}

/********************************************************

	FUNCTION CALCULATE AVERAGE FITNESS
	-----------------------------------
	This function calculates the average fitness of
	the generation by summing the fitness of each 
	individual in the generation and dividing by the
	number of individuals in the generation.

*********************************************************/

void Generation::calculateAverageFitness(){

	double sum = 0;
 
	for(vector<Individual*>::iterator i = Generation::genVec.begin(); i!=Generation::genVec.end(); ++i){
		sum += (*i)->getFitness();
	}

	Generation::averageFitness = sum / Generation::genVec.size();

	return;

}

/********************************************************

	ACCESSOR FUNCTIONS
	------------------

*********************************************************/

double Generation::getAverageFitness(){

	if(Generation::averageFitness == 0)
		Generation::calculateAverageFitness();
	return Generation::averageFitness;
}

vector<Individual*>::iterator Generation::getGenVecBegin(){
	return Generation::genVec.begin();
}
vector<Individual*>::iterator Generation::getGenVecEnd(){
	return Generation::genVec.end();
}
vector<Individual*>::size_type Generation::getGenSize(){
	return Generation::genSize;
}

Individual * Generation::getIndividual(vector<Individual*>::iterator index) const{
	cout<<"getIndividual"<<endl;
	if(index < Generation::genVec.end()){
		return *index;
	}else{
		cerr<<"Index out of range, Individual does not exist" << endl;
		return 0;
	}
}

vector<Individual*>::size_type Generation::getGenVecSize(){
	return Generation::genVec.size();
}



