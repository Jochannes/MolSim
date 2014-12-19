/*
 * plotHandler_VTK.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: johannes
 */

#include "plotHandler_VTK.h"

#include <omp.h>

plotHandler_VTK::plotHandler_VTK(outputWriter::VTKWriter& writer) :
		vtkWriter(&writer) {
}

plotHandler_VTK::~plotHandler_VTK() {
}

void plotHandler_VTK::compute(Particle& p) {
#pragma omp critical
	vtkWriter->plotParticle(p);
}
