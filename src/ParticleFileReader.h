/*
 * ParticleFileReader.h
 *
 *  Created on: 07.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef PARTICLEFILEREADER_H_
#define PARTICLEFILEREADER_H_

#include "ParticleInput.h"

#include <string>

/**
 * \brief Class for reading particles from a file.
 *
 * The file format is the same as used by ResultOutput.
 *
 */
class ParticleFileReader: public ParticleInput {
protected:
	/** name of the file from where the particles are read. */
	std::string filename;

public:
	ParticleFileReader(std::string param_filename) :
			filename(param_filename) {
	}

	virtual ~ParticleFileReader() {
	}

	/**  Reads particles from the file specified by 'filename' and stores them in 'particleList'.
	 */
	virtual void input(std::list<Particle>& particleList);

	/**
	 * /brief Returns the filename
	 */
	virtual std::string toString();
};

#endif /* PARTICLEFILEREADER_H_ */
