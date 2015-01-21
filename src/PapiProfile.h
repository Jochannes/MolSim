/*
 * PapiProfile.h
 *
 *  Created on: Jan 21, 2015
 *      Author: johannes
 */

#ifndef PAPIPROFILE_H_
#define PAPIPROFILE_H_

/**
 * \brief Class for profiling with PAPI.
 */
class PapiProfile {
private:
	char* filename;		//!< Name of the file to store the PAPI profiling results.
	long long real_usec;	//!< Real time in microseconds.
	long long real_cyc;		//!< Real time in clock cycles.
	int* events;	//!< Events measured by each thread.
	int eventCnt;	//!< Number of events measured by each thread.
	long long** papiValues; //!< PAPI profiling values of each thread.

	inline void setEvents();

public:
	PapiProfile(const char* param_filename);

	void start();
	void stop();
};

#endif /* PAPIPROFILE_H_ */
