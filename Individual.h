#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

/*
 *  Individual.h
 *  comp446final
 *
 *  Created by Angela Gabereau on 05/12/06.
 *	ID#: 4867815
 *  COMP 446  
 *  Final Programming Project
 *
 */

#include<string>
#include<vector>

class Individual  
{

public:
	//if member of first generation just name, otherwise constructor supplied parents and chromosome.
	Individual();//perhaps this will not be used
	Individual(std::string c, Individual * p1, Individual * p2);
	Individual(const Individual & other);
	~Individual();
	Individual & operator=(const Individual & other);
	void calculateFitness();
	void createChromosome();
	std::string getChromosome() const;
	double getFitness() const;
	double getRed() const;
	double getBlue() const;
	double getGreen() const;
	Individual * getparent1();
	Individual * getparent2();

private:
	std::string chromosome;
	int chromSize;
	double fitness;
	Individual * parent1;
	Individual * parent2;
	double red;
	double blue;
	double green;
	void calculateColor();
	unsigned int binstr2uint(const std::string& s);
};

#endif