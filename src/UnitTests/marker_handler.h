/*
 * marker_handler.h
 *
 *  Created on: Nov 22, 2014
 *      Author: johannes
 */

#ifndef MARKER_HANDLER_H_
#define MARKER_HANDLER_H_

#include "ParticleHandler.h"

namespace unitTest {

class marker_handler: public ParticleHandler {
public:
	marker_handler();
	virtual ~marker_handler();

	virtual void compute(Particle& p);
};
}

#endif /* MARKER_HANDLER_H_ */
