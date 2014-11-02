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

	filereader.readFile(container.particleList, filename.c_str());
}
