/*
 * TemperatureAdjustHandler.cpp
 *
 *  Created on: 01.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "TemperatureAdjustHandler.h"


void TemperatureAdjustHandler::compute(Particle& p)
{
	if( type == -1  ||  p.getType() == type ) {
		for( int i=0; i < 3; i++ ) {
			if( direction != i )
				p.getV()[i] = beta * p.getV()[i];
		}
	}
}

