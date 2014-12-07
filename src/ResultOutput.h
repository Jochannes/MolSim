/*
 * ResultOutput.h
 *
 *  Created on: 07.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef RESULTOUTPUT_H_
#define RESULTOUTPUT_H_


#include "ParticleContainer/ParticleContainer.h"
#include <string>

/**
 * \brief Class for exporting the result of a simulation to a file.
 *
 * This class will write all particles from a particle container to a file.
 * The generated file can be used as an input using ParticleFileReader.
 *
 * In contrast to ParticleOutput, which saves several iterations of a simulation,
 * ResultOutput is meant for exporting only the final result.
 */
class ResultOutput
{
protected:
	ParticleContainer& container;	//!< particle container from which the particles are exported.
	std::string filename;			//!< name of the file to write the particles to.

public:
	ResultOutput(ParticleContainer& param_container, std::string& param_filename)
		: container(param_container), filename(param_filename)
	{ }

	virtual ~ResultOutput() {
	}

	/** Writes the particles to the file.
	 *
	 */
	virtual void output();

};


#endif /* RESULTOUTPUT_H_ */
