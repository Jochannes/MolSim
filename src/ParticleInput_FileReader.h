/*
 * ParticleInput_FileReader.h
 *
 *  Created on: 26.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef PARTICLEINPUT_FILEREADER_H_
#define PARTICLEINPUT_FILEREADER_H_

#include "ParticleInput.h"
#include "ParticleContainer.h"

#include <string>

/**
 * \brief Class implementing particle input using the input method provided by the class FileReader.
 */
class ParticleInput_FileReader : public ParticleInput
{
protected:
	std::string filename;

public:
	ParticleInput_FileReader(ParticleContainer& param_container, std::string param_filename)
		: ParticleInput(param_container), filename(param_filename) {
	}

	virtual ~ParticleInput_FileReader() {
	}

	virtual void input();

};


#endif /* PARTICLEINPUT_FILEREADER_H_ */
