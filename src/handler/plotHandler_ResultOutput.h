/*
 * plotHandler_ResultOutput.h
 *
 *  Created on: 07.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#ifndef PLOTHANDLER_RESULTOUTPUT_H_
#define PLOTHANDLER_RESULTOUTPUT_H_

#include "ParticleHandler.h"
#include <fstream>

/**
 * \brief Class for plotting all particles when writing a result file.
 */
class plotHandler_ResultOutput: public ParticleHandler
{
private:
	std::ofstream& output_file;

public:
	plotHandler_ResultOutput(std::ofstream& param_output_file)
		: output_file(param_output_file)
	{ }

	virtual ~plotHandler_ResultOutput() {
	}

	/**
	 * \brief Method for plotting a particle.
	 * @param p Particle to plot.
	 */
	virtual void compute(Particle& p);
};

#endif /* PLOTHANDLER_RESULTOUTPUT_H_ */

