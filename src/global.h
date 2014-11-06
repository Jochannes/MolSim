/*
 * global.h

 *
 *  Created on: 30.10.2014
 *      Author: Jochannes, DanielCAlbert
 */

/**
 * \mainpage Molecular Dynamics Simulation
 *
 * MolSim is a simulation program for molecular dynamics.
 * It simulates a set particles over a specified span of time.
 * Force calculation between particles can be done using Lennard-Jones-potential
 * or using gravity-potential.
 * It is possible to read the particles from a file and to generate a cuboid of
 * particles with brownian motion.
 * The results can be saved in a VTK-file, which can be visualized e.g. by ParaView.
 *
 * For an explanation on how to use MolSim, run MolSim using the option "-help".
 *
 * \file
 * \brief Declaration of all relevant global variables.
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_


extern double start_time;
extern double end_time;
extern double delta_t;


#endif /* GLOBAL_H_ */
