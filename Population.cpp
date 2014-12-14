/*
 *  Population.cpp
 *  comp446final
 *
 *  Created by Angela Gabereau on 05/12/06.
 *	ID#: 4867815
 *  COMP 446  
 *  Final Programming Project
 *
 */
/**********************************************************************

	CLASS POPULATION
	-----------------
	

***********************************************************************/

#include "Individual.h"
#include "Generation.h"
#include "RouletteWheel.h"
#include "Population.h"
#include<vector>
#include<cstdlib>
#include<iostream>
#include<cassert>


using namespace std;


/********************************************************

	CONSTRUCTORS, DESTRUCTORS
	---------------------------

*********************************************************/


Population::Population() : totalGenerations(50), sizeGenerations(50), probMutate(0.001), probCrossover(0.7)
{
	Population::popVec.reserve(Population::totalGenerations);
}

Population::Population(int totalGen, int sizeGen) : totalGenerations(totalGen), sizeGenerations(sizeGen), probMutate(0.001), probCrossover(0.7)
{
	if(totalGen<=0)
		cerr<<"ERROR: totalGen must be greater than 0"<<endl;
	else
		Population::totalGenerations=totalGen;

	if(sizeGen<=0)
		cerr<<"ERROR: sizeGen must be greater then 0"<<endl;
	else
		Population::sizeGenerations=sizeGen;

	assert(totalGen>0 && sizeGen>0);

	Population::popVec.reserve(Population::totalGenerations);
}

Population::Population(int totalGen, int sizeGen, double probMut, double probCross) : totalGenerations(totalGen), sizeGenerations(sizeGen)
{
	if(totalGen<=0)
		cerr<<"ERROR: totalGen must be greater than 0"<<endl;
	else
		Population::totalGenerations=totalGen;

	if(sizeGen<=0)
		cerr<<"ERROR: sizeGen must be greater then 0"<<endl;
	else
		Population::sizeGenerations=sizeGen;
	if(probMut>1.0)
		cerr<<"ERROR: Argument probMut must be within 0.0 and 1.0"<<endl;
	else
		Population::probMutate = probMut;
	if(probCross>1.0)
		cerr<<"ERROR: Argument probMut must be within 0.0 and 1.0"<<endl;
	else
		Population::probCrossover = probCross;
	
	assert(probMut<=1.0 && probCross<=1.0&& totalGen>0 && sizeGen>0);

	Population::popVec.reserve(Population::totalGenerations);
}

Population::~Population(){

	for(vector<Generation*>::iterator i = Population::popVec.begin(); i != Population::popVec.end(); ++i)
		delete *i;
}

Population::Population(Population & other): totalGenerations(other.totalGenerations), sizeGenerations(other.sizeGenerations),
												probMutate(other.probMutate), probCrossover(other.probCrossover)
{	vector<Generation*>::const_iterator j = other.getPopVecBegin();
	for(vector<Generation*>::iterator i = Population::popVec.begin(); i!=Population::popVec.end(); ++i){
		
		
		vector<Individual*>::iterator l = (*j)->getGenVecBegin();
		for(vector<Individual*>::iterator k = (*i)->getGenVecBegin(); k!=(*i)->getGenVecEnd(); ++i){
			*k = new Individual((*l)->getChromosome(), (*l)->getparent1(), (*l)->getparent2());
			++l;
		}
		++j;
	}
}

Population & Population::operator=(Population & other){

	if(this == &other)
		return *this;
	std::vector<Generation*> popVec;
	Population::totalGenerations = other.getTotalGenerations();
	Population::sizeGenerations = other.getSizeGenerations();
	Population::probMutate = other.getProbMutate();
	Population::probCrossover = other.getProbCrossover();
	vector<Generation*>::const_iterator j = other.getPopVecBegin();
	for(vector<Generation*>::iterator i = Population::popVec.begin(); i!=Population::popVec.end(); ++i){
		
		
		vector<Individual*>::iterator l = (*j)->getGenVecBegin();
		for(vector<Individual*>::iterator k = (*i)->getGenVecBegin(); k!=(*i)->getGenVecEnd(); ++i){
			*k = *l;
			++l;
		}
		++j;
	}

	return *this;
}






/********************************************************

	FUNCTION ANALYZE
	-----------------
	This function is responsible for displaying
	the average fitness of each generation in the
	population and the change in average fitness
	from the first generation to the last.

*********************************************************/

void Population::analyze(){
	std::cout << "********   ANALYSIS  ******" <<endl;
	std::cout << "The average fitness of each generation, from the initial generation to the last." <<endl;

	int lineCount=1;
	double firstFitness = 0;
	double lastFitness = 0;
	double changeFitness = 0;
	for(vector<Generation*>::iterator i = Population::popVec.begin(); i!=Population::popVec.end(); ++i){
		
		std::cout << (*i)->getAverageFitness()<<"	";
		if(i==Population::popVec.begin())
			firstFitness = (*i)->getAverageFitness();
		if(i==Population::popVec.end()-1)
			lastFitness = (*i)->getAverageFitness();
		if(lineCount%10==0)
			std::cout<<endl;
		++lineCount;
	}
	changeFitness = lastFitness - firstFitness;

	std::cout<<"The fitness of the first generation: "<<firstFitness<<endl;
	std::cout<<"The fitness of the last generation: "<<lastFitness<<endl;
	std::cout<<"The change in fitness from first to last generation: "<<changeFitness<<endl;
	std::cout<<endl;
	std::cout<<endl;
	return;
}

/********************************************************

	FUNCTION RUN
	------------
	run runs only once during program execution.
	iterator currentGeneratio is set to begining 
	of popVec, for the first generation a new 
	generation is pushed onto vecPop

*********************************************************/


void Population::run(){

	vector<Generation*>::iterator childGeneration = Population::popVec.begin();
	vector<Generation*>::iterator parentGeneration;

	//assert that the population is empty before attempting to fill it.
	assert(Population::popVec.size()==0);

	if( childGeneration == Population::popVec.begin()){
		//create first, empty generation
		Population::popVec.push_back(new Generation(Population::sizeGenerations));
		//fill generation, must create individuals of a generation individually
		Population::initialGeneration(*childGeneration);

		parentGeneration = childGeneration;
		++childGeneration;

	}

	while(Population::popVec.size() != Population::totalGenerations){//this may not work because not sure that popVec.reserve changes what popVec.end() returns.
	
		//reproduce from currentGeneration
		Population::popVec.push_back(new Generation(Population::sizeGenerations));

		//pass references to parent generation and an empty child generation
		Population::reproduce(*parentGeneration, *childGeneration);

		parentGeneration = childGeneration;
		++childGeneration;
	} 

	return;
}

/********************************************************

	FUNCTION INITIAL GENERATION
	---------------------------
	This function creates the initial generation
	by creates a generation filled with Individuals
	with randomly generated chromosomes

*********************************************************/

void Population::initialGeneration(Generation* firstGen){

	vector<Individual*>::iterator i = firstGen->getGenVecBegin();

	while(firstGen->getGenVecSize()<firstGen->getGenSize()){
		firstGen->addIndividual((new Individual));
		++i;

	}

	return;
}

/********************************************************

	FUNCTION REPRODUCE
	-------------------
	This function creates a new generation of Individuals
	from the previous generation.  It selects parents
	using a instance of RouletteWheel, the parents' 
	chromosomes are then used to create a new chromosome.
	This chromosome is then mutated.  The new chromosome
	is then used to create a new Individual.  This is 
	repeated until the new generation is full of
	Individuals.

*********************************************************/

void Population::reproduce(Generation * parentGen, Generation * childGen){

	RouletteWheel wheel = RouletteWheel(parentGen);

	while(childGen->getGenVecSize()<childGen->getGenSize()){

		Individual * parent1 = wheel.spin();
		Individual * parent2 = wheel.spin();
		string newChromosome;

		if(rand()%2)
			newChromosome = Population::crossover(parent1, parent2);
		else
			newChromosome = Population::crossover(parent2, parent1);

		newChromosome = Population::mutate(newChromosome);

		childGen->addIndividual((new Individual(newChromosome, parent1, parent2)));
		
	}

	return;
}

/********************************************************

	FUNCTION CROSSOVER
	------------------------
	This function creates a new string with one point crossover
	There is a probility of crossover, if there is no
	crossover then there is asexual reproduction and 
	parent1 passes down a copy of it's chromosome.
	The probability of crossover is Population::probCrossover
	and random double between 0.0 and 1.0 detemines if
	crossover occurs.  If random value fails between 0.0
	and Population::probCrossover then crossover proceeds.
	
	A random number between 0 and the length of the
	chromosome string of the Individual argument a is
	generated. This is the crossOverPoint.  In the new 
	chromosome string from position 0 to crossOverPoint
	is a substring of chromosome1 and the remaining
	portion of the string is a substring of chromosome2.

*********************************************************/


string Population::crossover(Individual * a, Individual * b){

	string newChromosome;

	if(static_cast< double >( rand() ) / RAND_MAX < Population::probCrossover){
		string chromosome1 = a->getChromosome();
		string chromosome2 = b->getChromosome();

		int crossOverPoint = rand()%chromosome1.size();
	
		newChromosome = chromosome1.substr(0, crossOverPoint) 
						+ chromosome2.substr(crossOverPoint, chromosome2.size()-crossOverPoint);

	}else{
		newChromosome = a->getChromosome();
	}

	return newChromosome;

}

/********************************************************

	FUNCTION MUTATE
	----------------
	This function mutates each bit of the chromosome
	with a probabilty of Population::probMutate.
	Mutation is simply a bit fill.

*********************************************************/

string Population::mutate(string s){

	string mutateChromosome = s;

	for(string::iterator i = mutateChromosome.begin(); i!=mutateChromosome.end(); ++i){

		if(static_cast< double >( rand() ) / RAND_MAX< Population::probMutate){
			//flip bit
			//std::cout << "mutating " <<*i<<endl;
			if(*i=='1'){
				*i='0';
			}else{
				*i='1';
			}
		}
	}

	return mutateChromosome;

}

/********************************************************

	ACCESSOR FUNCTIONS
	-------------------
*********************************************************/



vector<Generation*>::iterator Population::getPopVecBegin(){
	return Population::popVec.begin();
}

vector<Generation*>::iterator Population::getPopVecEnd(){
	return Population::popVec.end();
}


vector<Generation*>::size_type Population::getTotalGenerations() const{
	return Population::totalGenerations;
}
vector<Individual*>::size_type Population::getSizeGenerations() const{
	return Population::sizeGenerations;
}

double Population::getProbMutate() const{
	return Population::probMutate;
}
double Population::getProbCrossover() const{
	return Population::probCrossover;
}
