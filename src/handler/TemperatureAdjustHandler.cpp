/*
 * TemperatureAdjustHandler.cpp
 *
 *  Created on: 01.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "TemperatureAdjustHandler.h"


void TemperatureAdjustHandler::compute(Particle& p)
{
	p.getV() = beta * p.getV();
}
