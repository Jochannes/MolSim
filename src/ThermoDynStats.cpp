/*
 * ThermoDynStats.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: johannes
 */

#include "ThermoDynStats.h"
#include "handler/VarHandler.h"
#include "handler/RDFHandler.h"

#include <fstream>
#include <stdio.h>
#include <log4cxx/logger.h>
#include <cstdlib>

using namespace std;
using namespace log4cxx;

/**
 * \brief Constructor for initializing all values for statistics calculation
 * @param arg_freq Frequency of statistics calculation.
 * @param arg_avgOver Number of iterations over which the statistics will be averaged.
 * @param arg_dr Radius discretization length for the radial pair distribution function.
 * @param arg_maxrad Maximum radius for the radial pair distribution function (usually the cutoff radius).
 * @param arg_varFile File for storing the movement variance.
 * @param arg_rdfFile File for storing the radial pair distribution function.
 */
ThermoDynStats::ThermoDynStats(int arg_freq, int arg_avgOver,
		double arg_dr, double arg_maxrad, string& arg_varFile, string& arg_rdfFile) :
		freq(arg_freq), avgOver(arg_avgOver), dr(arg_dr), maxrad(arg_maxrad), varFile(arg_varFile), rdfFile(arg_rdfFile) {

	var = new double[avgOver];

	rdf = new double*[avgOver];
	intervalCnt = ceil(maxrad / dr);
	for (int i = 0; i < avgOver; i++) {
		rdf[i] = new double[intervalCnt];
	}

	std::remove(varFile.c_str());
	std::remove(rdfFile.c_str());
}

/**
 * \brief Function for calculating and saving the thermodynamical statistics.
 * @param cont ParticleContainer for which the statistics are calculated.
 * @param iteration Current iteration number.
 *
 * This method should be called for each iteration step. Depending
 * on the iteration number, it either does nothing, calculates the
 * thermodynamical statistics and/or saves them.
 */
void ThermoDynStats::analyze(ParticleContainer* cont, int iteration) {

	//Calculate statistics
	if (iteration % freq < avgOver) {
		calcVar(cont, iteration % freq);
		calcRDF(cont, iteration % freq);
	}

	//Calculate average and save the statistics
	int it = iteration % freq;
	int end = avgOver - 1;
	if (iteration % freq == avgOver - 1) {
		double avg_var = 0;
		double* avg_rdf = new double[intervalCnt];
		for(int i = 0; i < intervalCnt; i++){
			avg_rdf[i] = 0;
		}

		//sum over iterations
		for (int i = 0; i < avgOver; i++) {
			avg_var += var[i];
			for (int j = 0; j < intervalCnt; j++) {
				avg_rdf[j] += rdf[i][j];
			}
		}

		//divide by number of iterations
		avg_var /= avgOver;
		for (int j = 0; j < intervalCnt; j++) {
			avg_rdf[j] /= avgOver;
		}

		saveStats(iteration, avg_var, avg_rdf);
	}
}

/**
 * \brief Function for calculating the movement variance.
 * @param cont ParticleContainer for which the statistics are calculated.
 * @param it Iteration number (between 0 and avgOver).
 */
inline void ThermoDynStats::calcVar(ParticleContainer* cont, int it) {
	VarHandler varSum = VarHandler();
	cont->iterate_all(varSum);
	var[it] = varSum.varN / cont->size();
}

/**
 * \brief Function for calculating the radial pair distribution function.
 * @param cont ParticleContainer for which the statistics are calculated.
 * @param it Iteration number (between 0 and avgOver).
 */
inline void ThermoDynStats::calcRDF(ParticleContainer* cont, int it) {
	RDFHandler rdfSum = RDFHandler(dr, intervalCnt);
	cont->iterate_pairs_half(rdfSum);
	for (int i = 0; i < intervalCnt; i++) {
		double vol = 4 * M_PI / 3 * (pow((i + 1) * dr, 3) - pow(i * dr, 3));
		rdf[it][i] = rdfSum.intervals[i] / vol;
	}
}

/**
 * \brief Function for saving the statistics in text files.
 * @param it Iteration number (between 0 and avgOver).
 * @param avg_var Calculated movement variance, averaged over multiple iterations.
 * @param avg_rdf Calculated radial pair distribution function, averaged over multiple iterations.
 */
inline void ThermoDynStats::saveStats(int it, double avg_var, double* avg_rdf) {

	static LoggerPtr thdynLogger(Logger::getLogger("MolSim.ResultOutput"));

	//save movement variance
	ofstream ofs;
	ofs.open(varFile.c_str(), fstream::out | fstream::app);
	if (!ofs.is_open()) {
		LOG4CXX_FATAL(thdynLogger, "Error: could not open file " << varFile);
		exit(1);
	}
	ofs << it << ";" << avg_var << endl;
	ofs.close();

	//save radial pair distribution function
	ofs.open(rdfFile.c_str(), fstream::out | fstream::app);
	if (!ofs.is_open()) {
		LOG4CXX_FATAL(thdynLogger, "Error: could not open file " << rdfFile);
		exit(1);
	}
	ofs << it;
	for (int i = 0; i < intervalCnt; i++) {
		ofs << ";" << avg_rdf[i];
	}
	ofs << endl;
	ofs.close();
}
