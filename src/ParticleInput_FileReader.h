/*
 * ParticleInput_FileReader.h
 *
 *  Created on: 26.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef PARTICLEINPUT_FILEREADER_H_
#define PARTICLEINPUT_FILEREADER_H_

#include "ParticleInput.h"

#include <string>

/**
 * \brief Class implementing particle input using the input method provided by the class FileReader.
 */
class ParticleInput_FileReader: public ParticleInput {
protected:
	/** name of the file where the particles are read. */
	const char* filename;

public:
	ParticleInput_FileReader(std::list<Particle>& param_particleList,
			const char* param_filename) :
			ParticleInput(param_particleList), filename(param_filename) {
	}

	virtual ~ParticleInput_FileReader() {
	}

	/**  Reads particles from the file specified by 'filename' and stores them in 'container'.
	 */
	virtual void input();

};

#endif /* PARTICLEINPUT_FILEREADER_H_ */
