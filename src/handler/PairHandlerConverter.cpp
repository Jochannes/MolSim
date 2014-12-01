/*
 * PairHandlerConverter.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: johannes
 */

#include "PairHandlerConverter.h"

PairHandlerConverter::PairHandlerConverter(PairHandler *original) :
		original(original) {
}
PairHandlerConverter::PairHandlerConverter(PairHandler *original,
		Particle *partner1) :
		original(original), partner1(partner1) {
}

PairHandlerConverter::~PairHandlerConverter() {
}

/**
 * \brief Set the first partner particle.
 * @param partner1 Partner particle to set.
 */
void PairHandlerConverter::setPartner(Particle *partner1) {
	this->partner1 = partner1;
}

/**
 * \brief Method converted from the original compute method.
 * @param p Second particle in the PairHandler::compute() function.
 */
void PairHandlerConverter::compute(Particle& p) {
	original->compute(*partner1, p);
}
