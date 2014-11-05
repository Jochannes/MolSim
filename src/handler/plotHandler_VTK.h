/*
 * plotHandler_VTK.h
 *
 *  Created on: Nov 5, 2014
 *      Author: johannes
 */

#ifndef PLOTHANDLER_VTK_H_
#define PLOTHANDLER_VTK_H_

#include "../outputWriter/VTKWriter.h"
#include "../ParticleHandler.h"


/**
 * \brief Class for plotting all particles when writing a VTK-file.
 */
class plotHandler_VTK : public ParticleHandler {
private:
	outputWriter::VTKWriter *vtkWriter;

public:
	plotHandler_VTK(outputWriter::VTKWriter& writer);
	virtual ~plotHandler_VTK();

	virtual void compute(Particle& P);
};

#endif /* PLOTHANDLER_VTK_H_ */
