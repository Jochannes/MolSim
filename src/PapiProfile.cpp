/*
 * PapiProfile.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: johannes
 */

#include <papi.h>
#include <omp.h>
#include <log4cxx/logger.h>
#include <fstream>
#include <cstring>

#include "PapiProfile.h"

using namespace log4cxx;
using namespace std;

extern LoggerPtr logger;

/**
 * \brief Constructor for setting up PAPI profiling.
 * @param param_filename File in which the PAPI profile will be saved.
 *
 * This method initializes PAPI profiling and sets the necessary variables.
 */
PapiProfile::PapiProfile(const char* param_filename) {
	filename = new char[strlen(param_filename) + 1];
	strcpy(filename, param_filename);
	PAPI_library_init(PAPI_VER_CURRENT);
	PAPI_thread_init(pthread_self);
	setEvents();
}

/**
 * \brief Set the counters measured for each thread.
 *
 * Currently measured:
 * 0. Total cycles
 * 1. Instructions completed
 * 2. Floating point operations
 * (3. Cycles stalled on any resource)
 */
void PapiProfile::setEvents() {
	eventCnt = 3;
	events = new int[eventCnt];
	events[0] = PAPI_TOT_CYC;
	events[1] = PAPI_TOT_INS;
	events[2] = PAPI_FP_OPS;
	//events[3] = PAPI_RES_STL;
}

/**
 * \brief Initialize all counters and start counting.
 */
void PapiProfile::start(){
	real_usec = PAPI_get_real_usec();
	real_cyc = PAPI_get_real_cyc();
	#ifdef _OPENMP
	#pragma omp parallel
	{
		#pragma omp critical
		if (PAPI_start_counters(events, eventCnt) != PAPI_OK) {
			LOG4CXX_ERROR(logger, "PAPI counter start failed.");
		}
	}
	#else
	if (PAPI_start_counters(events, eventCnt) != PAPI_OK) {
		LOG4CXX_ERROR(logger, "PAPI counter start failed.");
	}
	#endif
}

/**
 * \brief Stop all counters, collect the results and save them.
 */
void PapiProfile::stop(){

	//Collect overall counters
	real_usec = PAPI_get_real_usec() - real_usec;
	real_cyc = PAPI_get_real_cyc() - real_cyc;

	//Collect per-thread counters
	#ifdef _OPENMP
	papiValues = new long long*[omp_get_max_threads()];
	for(int i = 0; i < omp_get_max_threads(); i++) {
		papiValues[i] = new long long[eventCnt];
		for(int j = 0; j < eventCnt; j++){
			papiValues[i][j] = 0;
		}
	}
	#pragma omp parallel
	{
		#pragma omp critical
		if (PAPI_stop_counters(papiValues[omp_get_thread_num()], eventCnt) != PAPI_OK) {
			LOG4CXX_ERROR(logger, "PAPI counter stop failed.");
		}
	}
	#else
	papiValues = new long long*[1];
	papiValues[0] = new long long[eventCnt];
	if (PAPI_stop_counters(papiValues[omp_get_thread_num()], eventCnt) != PAPI_OK) {
		LOG4CXX_ERROR(logger, "PAPI counter stop failed.");
	}
	#endif

	//Save overall counters in file
	ofstream papiStream;
	papiStream.open(filename);
	double real_sec = real_usec * 0.000001;
	papiStream << "Overall: " << real_sec << "s, " << real_cyc << " cycles" << endl << endl;

	//Save per-thread counters in file
	#ifdef _OPENMP
	papiStream << "Per thread: " << endl;
	papiStream << "thread number; total cycles; completed instructions; floating point operations; instructions per cycle" << endl;
	double usage;
	for(int i = 0; i < omp_get_max_threads(); i++) {
		papiStream << i;
		for(int j = 0; j < eventCnt; j++) {
			papiStream << ";" << papiValues[i][j];
		}
		usage = papiValues[i][1] / (papiValues[i][0] * 1.0);
		papiStream << ";" << usage << endl;
	}
	#else
	papiStream << "total cycles; completed instructions; floating point operations; instructions per cycle" << endl;
	for(int j = 0; j < eventCnt; j++) {
		papiStream << papiValues[0][j] << ";";
	}
	double usage = papiValues[0][1] / (papiValues[0][0] * 1.0);
	papiStream << usage << endl;
	#endif
	papiStream.close();
}
