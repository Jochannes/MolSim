/*
 * ParticleInput_FileReader.cpp
 *
 *  Created on: 26.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "ParticleInput_FileReader.h"
#include "FileReader.h"

using namespace std;


void ParticleInput_FileReader::input(list<Particle>& particleList) {
	FileReader filereader;

	filereader.readFile(particleList, filename.c_str());
}


std::string ParticleInput_FileReader::toString()
{
	std::stringstream str;

	str << "\"" << filename << "\"";

	return str.str();
}
