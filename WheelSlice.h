#ifndef WHEELSLICE_H
#define WHEELSLICE_H

/*
 *  WheelSlice.h
 *  comp446final
 *
 *  Created by Angela Gabereau on 05/12/06.
 *	ID#: 4867815
 *  COMP 446  
 *  Final Programming Project
 *
 */

#include "Individual.h"

/**********************************************************************

	CLASS WHEEL SLICE
	------------------------
	This class defines a data structure intended to be used as a
	slice in a roulette wheel.  This is a template class, thus can 
	store any type along side a probability index, which represents
	the size or weight of the slice and it position on the wheel.

***********************************************************************/

template <class T>
class WheelSlice
{

public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;

	WheelSlice(double p, T d): probIndex(p), data(d){};
	//WheelSlice(const Slice & other);
	//WheelSlice & operator=(const Slice & other);
	~WheelSlice(){};
	T getData() const{ return data; };
	double getProbIndex() const{ return probIndex; };

private:
	T data;
	double probIndex;

};

#endif