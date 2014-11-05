/*
 * ParticleInput_FileReader.cpp
 *
 *  Created on: 26.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ParticleInput_FileReader.h"
#include "FileReader.h"

/*
 * \brief Method for reading in a particle file using FileReader.
 */
void ParticleInput_FileReader::input()
{
	FileReader filereader;

	std::list<Particle> initialParticles;
	filereader.readFile(initialParticles, filename.c_str());
	container = ParticleContainer(&initialParticles);
}
