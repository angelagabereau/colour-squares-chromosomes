#ifndef POPULATION_H
#define POPULATION_H

/*
 *  Population.h
 *  comp446final
 *
 *  Created by Angela Gabereau on 05/12/06.
 *	ID#: 4867815
 *  COMP 446  
 *  Final Programming Project
 *
 */
#include "Generation.h"
#include<vector>

class Population
{

public:
	Population();
	Population(int numGen, int sizeGen);
	Population(int numGen, int sizeGen, double probMut, double probCross);
	~Population();
	Population(Population & other);
	Population & operator=(Population & other);
	void analyze();
	void run();
	std::vector<Generation*>::iterator getPopVecBegin();
	std::vector<Generation*>::iterator getPopVecEnd();
	std::vector<Generation*>::size_type getTotalGenerations() const;
	std::vector<Individual*>::size_type getSizeGenerations() const;
	double getProbMutate() const;
	double getProbCrossover() const;
	
private:
	std::vector<Generation*> popVec;
	std::vector<Generation*>::size_type totalGenerations;
	std::vector<Individual*>::size_type sizeGenerations;
	double probMutate;
	double probCrossover;
	void reproduce(Generation * parentGen, Generation * childGen);
	void initialGeneration(Generation* firstGen);
	std::string crossover(Individual * a, Individual * b);
	std::string mutate(std::string s);


};

#endif