/*
 * plotHandler_VTK.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: johannes
 */

#include "plotHandler_VTK.h"


plotHandler_VTK::plotHandler_VTK(outputWriter::VTKWriter& writer)
	: vtkWriter(&writer)
{
}


plotHandler_VTK::~plotHandler_VTK() {
}

/**
 * \brief Method for plotting a particle.
 */
void plotHandler_VTK::compute(Particle& P)
{
	vtkWriter->plotParticle(P);
}
