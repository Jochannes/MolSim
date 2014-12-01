/*
 * Particle.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "Particle.h"

#include <sstream>
#include <log4cxx/logger.h>

using namespace log4cxx;

LoggerPtr Particlelogger(Logger::getLogger("MolSim.Particle"));

//initialize static Lennard-Jones default parameters
double Particle::def_epsilon = 5.0;
double Particle::def_sigma = 1.0;

/**
 * \brief Initializes the particle, defining its type.
 * @param type_arg Type of the particle
 */
Particle::Particle(int type_arg) :
		f(0.0), old_f(0.0), m(0.0), epsilon(def_epsilon), sigma(def_sigma), type(type_arg) {
	LOG4CXX_TRACE(Particlelogger, "Particle generated!");
}

/**
 * \brief Copies the particle from another one.
 * @param other Particle to copy
 */
Particle::Particle(const Particle& other) :
		x(other.x), v(other.v), f(other.f), old_f(other.old_f), m(other.m), epsilon(other.epsilon), sigma(other.sigma), type(
				other.type) {
	LOG4CXX_TRACE(Particlelogger, "Particle generated by copy!");
}

/**
 * \brief Initializes the particle with values.
 * @param type_arg Type of the particle
 * @param x_arg Initial particle position
 * @param v_arg Initial particle velocity
 * @param m_arg Particle mass
 * @param epsilon_arg Lennard-Jones parameter epsilon for this particle
 * @param sigma_arg Lennard-Jones parameter sigma for this particle
 */
Particle::Particle(utils::Vector<double, 3> x_arg,
		utils::Vector<double, 3> v_arg, double m_arg, int type_arg, double epsilon_arg, double sigma_arg) :
		x(x_arg), v(v_arg), m(m_arg), epsilon(epsilon_arg), sigma(sigma_arg), type(type_arg), f(0.0), old_f(0.0) {
	LOG4CXX_TRACE(Particlelogger, "Particle generated!");
}

/**
 * \brief Deconstructs the particle.
 */
Particle::~Particle() {
	LOG4CXX_TRACE(Particlelogger, "Particle destructed!");
}

/**
 * \brief Returns the particle position.
 */
utils::Vector<double, 3>& Particle::getX() {
	return x;
}

/**
 * \brief Returns the particle velocity.
 */
utils::Vector<double, 3>& Particle::getV() {
	return v;
}

/**
 * \brief Returns the force currently acting on the particle.
 */
utils::Vector<double, 3>& Particle::getF() {
	return f;
}

/**
 * \brief Returns the force that acted on the particle in the last iteration step.
 */
utils::Vector<double, 3>& Particle::getOldF() {
	return old_f;
}

/**
 * \brief Returns the particle mass.
 */
double Particle::getM() {
	return m;
}

/**
 * \brief Returns the Lennard-Jones parameter epsilon for this particle.
 */
double Particle::getEpsilon() {
	return epsilon;
}

/**
 * \brief Returns the Lennard-Jones parameter sigma for this particle.
 */
double Particle::getSigma() {
	return sigma;
}

/**
 * \brief Returns the particle type.
 */
int Particle::getType() {
	return type;
}

/**
 * \brief Returns a string with all particle parameters.
 */
std::string Particle::toString() {
	std::stringstream stream;
	stream << "Particle: X:" << x << " v: " << v << " f: " << f << " old_f: "
			<< old_f << " type: " << type;
	return stream.str();
}

/**
 * \brief Returns if the other particle has the same type, position, velocity, mass, current and old force.
 * @param other Particle to compare to
 */
bool Particle::operator ==(Particle& other) {
	if ((x == other.x) && (v == other.v) && (f == other.f)
			&& (type == other.type) && (m == other.m)
			&& (old_f == other.old_f)) {
		return true;
	}

	return false;
}

/**
 * \brief Passes a string with all particle parameters.
 */
std::ostream& operator<<(std::ostream& stream, Particle& p) {
	stream << p.toString();
	return stream;
}

