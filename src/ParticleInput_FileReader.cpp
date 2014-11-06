/*
 * ParticleInput_FileReader.cpp
 *
 *  Created on: 26.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ParticleInput_FileReader.h"
#include "FileReader.h"


void ParticleInput_FileReader::input()
{
	FileReader filereader;
	std::list<Particle> readParticles;

	filereader.readFile(readParticles, filename.c_str());

	container.add(readParticles);
}
