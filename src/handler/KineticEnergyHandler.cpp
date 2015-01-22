/*
 * KineticEnergyHandler.cpp
 *
 *  Created on: 01.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "KineticEnergyHandler.h"


void KineticEnergyHandler::compute(Particle& p)
{
	if( type == -1  ||  p.getType() == type ) {
		utils::Vector<double, 3> v = p.getV() - v_mean;

		E_kin += 0.5 * p.getM() * v.innerProduct(v);
	}
}

