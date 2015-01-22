/*
 * Check_Force.cpp
 *
 *  Created on: 23.12.2014
 *      Author: Jochannes, DanielCAlbert
 */

#include "Check_Force.h"


namespace unitTest {


/**
 * \brief This method checks if the particle has the specified type and the specified force.
 * It sets 'successful' to false if it encounters a particle that has the specified type,
 * but does not have the specified force.
 *
 * @param p Particle to check
 */
void Check_Force::compute(Particle& p) {

	if( p.getType() == type ) {
		if( !(p.getF() == force) )
			successful = false;
	}
}


}
