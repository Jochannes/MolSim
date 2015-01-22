/*
 * MeanVelocityHandler.cpp
 *
 *  Created on: 08.01.2015
 *      Author: Jochannes, DanielCAlbert
 */

#include "MeanVelocityHandler.h"


void MeanVelocityHandler::compute(Particle& p)
{
	if( type == -1  ||  p.getType() == type ) {
		sum += p.getV()[direction];
		count++;
	}
}

