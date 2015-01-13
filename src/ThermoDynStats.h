/*
 * ThermoDynStats.h
 *
 *  Created on: Jan 13, 2015
 *      Author: johannes
 */

#ifndef THERMODYNSTATS_H_
#define THERMODYNSTATS_H_

#include "ParticleContainer/ParticleContainer.h"
#include <string>

using namespace std;

/**
 * \brief Class for calculating thermodynamical statistics.
 *
 * This class calculates the movement variance as a measure
 * of diffusion and the radial pair distribution function
 * and saves them in separate files.
 */
class ThermoDynStats {
private:
	int freq;			//!< Specifies how often thermodynamical statistics will be calculated.
	int avgOver;		//!< Specifies over how many iterations the statistics will be averaged.

	double* var;		//!< Calculated movement variance for each timestep.
	string varFile;		//!< Name of the file to store the movement variance.

	double dr;			//!< Radius discretization length for the radial pair distribution function.
	double maxrad;		//!< Maximum radius for the radial pair distribution function (usually the cutoff radius).
	int intervalCnt;	//!< Number of intervals in the radial pair distribution function.
	double** rdf;		//!< Calculated radial pair distribution function for each timestep.
	string rdfFile;		//!< Name of the file to store the radial pair distribution function.

	inline void calcVar(ParticleContainer* cont, int it);
	inline void calcRDF(ParticleContainer* cont, int it);
	inline void saveStats(int it, double avg_var, double* avg_rdf);
public:

	ThermoDynStats(double arg_freq, double arg_avgOver, double arg_dr, double arg_maxrad, string& arg_varFile, string& arg_rdfFile);

	void analyze(ParticleContainer* cont, int iteration);
};

#endif /* THERMODYNSTATS_H_ */
