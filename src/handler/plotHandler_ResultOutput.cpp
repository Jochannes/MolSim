/*
 * plotHandler_ResultOutput.cpp
 *
 *  Created on: 07.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "plotHandler_ResultOutput.h"

#include <omp.h>

using namespace std;


void plotHandler_ResultOutput::compute(Particle& p)
{
#pragma omp critical
	output_file
		<< p.getX()[0] << " " << p.getX()[1] << " " << p.getX()[2] << " "
		<< p.getV()[0] << " " << p.getV()[1] << " " << p.getV()[2] << " "
		<< p.getF()[0] << " " << p.getF()[1] << " " << p.getF()[2] << " "
		<< p.getOldF()[0] << " " << p.getOldF()[1] << " " << p.getOldF()[2] << " "
		<< p.getM() << " " << p.getEpsilon() << " " << p.getSigma() << " "
		<< p.getType() <<
		"\n";
}
