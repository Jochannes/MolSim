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
 * It offers implementations for several different methods for force calculation, input and output.
 *
 * The current build simulates the collision of two bodies using the Lennard-Jones-Potential.
 * The result is saved in a VTK-file, which can be visualized using ParaView.
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
