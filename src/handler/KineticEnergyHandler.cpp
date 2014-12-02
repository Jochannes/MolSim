/*
 * KineticEnergyHandler.cpp
 *
 *  Created on: 01.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "KineticEnergyHandler.h"


void KineticEnergyHandler::compute(Particle& p)
{
	E_kin += 0.5 * p.getM() * p.getV().innerProduct(p.getV());
}

