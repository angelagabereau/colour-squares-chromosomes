#ifndef ROULETTEWHEEL_H
#define ROULETTEWHEEL_H

/*
 *  RouletteWheel.h
 *  comp446final
 *
 *  Created by Angela Gabereau on 05/12/06.
 *	ID#: 4867815
 *  COMP 446  
 *  Final Programming Project
 *
 */


#include "WheelSlice.h"
#include "Individual.h"
#include "Generation.h"
#include<vector>

class RouletteWheel  
{

public:
	typedef WheelSlice<Individual *> slice;
	RouletteWheel(Generation * g);
	//RouletteWheel(const RouletteWheel & other);
	//RouletteWheel & operator=(const RouletteWheel & other);
	~RouletteWheel();
	Individual * spin();

private:                                                                            
	double sumFitness;
	double sumProbability;
	Generation * generation;
	std::vector<slice *> wheel;
	void createWheel();
	void calculateSumFitness();

};

#endif

