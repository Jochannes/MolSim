/*
 * ParticleOutput_VTK.cpp
 *
 *  Created on: 26.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ParticleOutput_VTK.h"
#include "outputWriter/VTKWriter.h"
#include "handler/plotHandler_VTK.h"

#include <list>


void ParticleOutput_VTK::output(int iteration)
{
	outputWriter::VTKWriter writer;
	writer.initializeOutput(container.size());

	// plot each particle
	plotHandler_VTK plotHandler = plotHandler_VTK(writer);
	container.iterate_all(plotHandler);


	writer.writeFile(out_name, iteration);
}
