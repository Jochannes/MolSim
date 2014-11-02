/*
 * ParticleOutput_VTK.cpp
 *
 *  Created on: 26.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ParticleOutput_VTK.h"
#include "outputWriter/VTKWriter.h"

#include <list>


void ParticleOutput_VTK::output(int iteration)
{
	outputWriter::VTKWriter writer;
	writer.initializeOutput(container.particleList.size());

	// plot each particle
	std::list<Particle>::iterator iterator = container.particleList.begin();

	while (iterator != container.particleList.end()) {
		writer.plotParticle(*iterator);
		++iterator;
	}

	writer.writeFile(out_name, iteration);
}

