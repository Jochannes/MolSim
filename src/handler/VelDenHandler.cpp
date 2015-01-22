/*
 * VelDenHandler.cpp
 *
 *  Created on: 21.01.2015
 *      Author: Jochannes, DanielCAlbert
 */

#include "VelDenHandler.h"


void VelDenHandler::compute(Particle& p)
{
	double index_d = (p.getX()[0] - x_start) / width;
	int index = (int) index_d;

	if( index_d >= 0  &&  index_d < N ) {
		bin_vel[index]  += p.getV()[1];
		bin_mass[index] += p.getM();
	}
	else {
		// out of bound
	}
}

