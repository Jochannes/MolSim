/*
 * PositionCalculator.cpp
 *
 *  Created on: 25.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "PositionCalculator.h"

// global variable for calculation. See "src/global.h".
extern double delta_t;

PositionCalculator::PositionCalculator()
	: omit_types(NULL), omit_count(0)
{
}

PositionCalculator::PositionCalculator(int arg_omit_count, int* arg_omit_types)
	: omit_count(arg_omit_count)
{
	if( arg_omit_count > 0  &&  arg_omit_types != NULL ) {
		omit_types = new int[omit_count];
		for(int i=0; i<omit_count; i++) {
			omit_types[i] = arg_omit_types[i];
		}
	}
}

PositionCalculator::~PositionCalculator() {
}

void PositionCalculator::compute(Particle& p) {
	// cancel calculation if the particles type is in the list.
	if( omit_count > 0 ) {
		for (int i=0; i<omit_count; i++) {
			if( p.getType() == omit_types[i] )
				return;
		}
	}

	double a = 0.5 * delta_t * delta_t / p.getM();

	p.getX() = p.getX() + delta_t * p.getV() + a * p.getF();
}

