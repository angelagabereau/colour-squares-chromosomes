#ifndef GENERATION_H
#define GENERATION_H

/*
 *  Generation.h
 *  comp446final
 *
 *  Created by Angela Gabereau on 05/12/06.
 *	ID#: 4867815
 *  COMP 446  
 *  Final Programming Project
 *
 */


#include "Individual.h"
#include<vector>


class Generation  
{

public:
	Generation();
	Generation(std::vector<Individual*>::size_type genSize);
	Generation(Generation & other);
	~Generation();
	Generation & operator=(Generation & other);
	void addIndividual(Individual * i);
	Individual * getIndividual(std::vector<Individual*>::iterator index) const;
	void calculateAverageFitness();
	double getAverageFitness();
	std::vector<Individual*>::iterator getGenVecBegin();
	std::vector<Individual*>::iterator getGenVecEnd();
	std::vector<Individual*>::size_type getGenVecSize();
	std::vector<Individual*>::size_type getGenSize();
	
private:
	std::vector<Individual*> genVec;
	std::vector<Individual*>::size_type genSize;
	double averageFitness;
	
};

#endif