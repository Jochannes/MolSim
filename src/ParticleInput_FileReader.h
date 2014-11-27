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
	std::string filename;

public:
	ParticleInput_FileReader(std::string param_filename) :
			filename(param_filename) {
	}

	virtual ~ParticleInput_FileReader() {
	}

	/**  Reads particles from the file specified by 'filename' and stores them in 'particleList'.
	 */
	virtual void input(std::list<Particle>& particleList);

	/**
	 * /brief Returns the filename
	 */
	virtual std::string toString();
};

#endif /* PARTICLEINPUT_FILEREADER_H_ */
