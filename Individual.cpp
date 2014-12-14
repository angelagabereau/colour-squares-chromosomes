/*
 *  Individual.cpp
 *  comp446final
 *
 *  Created by Angela Gabereau on 05/12/06.
 *	ID#: 4867815
 *  COMP 446  
 *  Final Programming Project
 *
 */
/**********************************************************************

	CLASS INDIVIDUAL
    -----------------

***********************************************************************/

#include "Individual.h"
#include<string>
#include<vector>
#include<cassert>
#include "math.h"
#include <bitset>
#include <climits>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>


using namespace std;

/***********************************************************

	CONSTRUCTORS, DESTRUCTORS
	---------------------------
	
	-to create an Individual with a randomly generated
	chromosome use default constructor
	-to create an from parents pass chromosome, which
	is created in Population::reproduce() and it's parents
 

*************************************************************/
	
Individual::Individual() : parent1(0), parent2(0), chromSize(48), red(0.0), blue(0.0), green(0.0)
{
	Individual::createChromosome();
	Individual::calculateFitness();
	Individual::calculateColor();
}

Individual::Individual(string c, Individual * p1, Individual * p2) : chromosome(c), parent1(p1), parent2(p2), chromSize(48), red(0.0), blue(0.0), green(0.0)
{	
	Individual::calculateFitness();
	Individual::calculateColor();
}

Individual::~Individual(){

}
	
Individual::Individual(const Individual & other) : chromosome(other.chromosome), chromSize(other.chromSize), 
												fitness(other.fitness), parent1(other.parent1), parent2(other.parent2),
												red(other.red), blue(other.blue), green(other.green)	
{	
}

Individual & Individual::operator=(const Individual & other){
	if(this==&other)
		return *this;
	Individual::chromosome =other.chromosome;
	Individual::chromSize =other.chromSize;
	Individual::fitness=other.fitness;
	Individual::parent1=other.parent1;
	Individual::parent2=other.parent2;
	Individual::red=other.red;
	Individual::blue=other.blue;
	Individual::green=other.green;
	return *this;
}


/********************************************************

	FUNCTION CREATE CHROMOSOME
	---------------------------
	This function creates a chromosome by randomly
	generating a bit string.

*********************************************************/

void Individual::createChromosome(){

	ostringstream buffer;
	assert(Individual::chromSize%3==0);
	for(int i = 0; i!= Individual::chromSize; ++i)
		buffer << rand()%2;

	//store string
	Individual::chromosome = buffer.str();

}


/********************************************************

	FUNCTION CALCULATE FITNESS
	---------------------------
	This function calculates the fitness of the
	Individual based on the chromosome. This
	function simply counts the number of 0's
	in the chromosome and sets the sum as fitness.

*********************************************************/

void Individual::calculateFitness(){

	Individual::fitness =0;
	for(string::iterator i = Individual::chromosome.begin(); i!=Individual::chromosome.end(); ++i){
		
	if(*i=='0')
			++Individual::fitness;
	}

}


/********************************************************

	FUNCTION CALCULATE COLOR
	------------------------
	This function parses the chromosome into 
	3 equal substrings, these bit substrings are
	then converted to int, then converts this
	int to a double representation and stored 
	in member variables.

*********************************************************/

void Individual::calculateColor()
{
	assert(Individual::chromosome.size()%3==0);
	int i = Individual::chromosome.size()/3;

	//calculate largest int value of string of length i
	double max = pow(2,i);

	string rstring = Individual::chromosome.substr(0, i);
	string bstring = Individual::chromosome.substr(i, i);
	string gstring = Individual::chromosome.substr(i*2, i);

	try{
		unsigned int rInt(binstr2uint(rstring));
		unsigned int bInt(binstr2uint(bstring));
		unsigned int gInt(binstr2uint(gstring));

		//convert ints to double between 0.0 and 1.0
		Individual::red = rInt/max;
		Individual::blue = bInt/max;
		Individual::green = gInt/max;
	}
	catch(const char *e)
	{
	std::cout << e << '\n';
	}
	catch(std::invalid_argument&)
	{
	std::cout << "[binstr2uint]: Invalid digit in input\n";
	}
}



/********************************************************

	FUNCTION BINSTR2UINT
	--------------------
	This function converts a bit string to an intger.
	I found this function on the web at:
	http://www.thescripts.com/forum/thread62239.html

*********************************************************/

unsigned int Individual::binstr2uint(const std::string& s)
{
const std::string::size_type
max_bits(sizeof(unsigned int) * CHAR_BIT);

if(s.size() > max_bits)
throw "[binstr2uint]: Too many digits in input\n";

return (std::bitset<max_bits>(s).to_ulong());
}




/********************************************************

	ACCESSOR FUNCTIONS
	------------------

*********************************************************/


string Individual::getChromosome() const{
	return Individual::chromosome;
}

double Individual::getFitness() const{
	return Individual::fitness;
}

double Individual::getRed() const{
	return Individual::red;
}
double Individual::getBlue() const{
	return Individual::blue;
}
double Individual::getGreen() const{
	return Individual::green;
}

Individual* Individual::getparent1(){
	return Individual::parent1;
}
Individual* Individual::getparent2(){
	return Individual::parent2;
}
