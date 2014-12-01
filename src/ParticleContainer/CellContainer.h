/*
 * CellContainer.h
 *
 *  Created on: Nov 18, 2014
 *      Author: johannes
 */

#ifndef CELLCONTAINER_H_
#define CELLCONTAINER_H_

#include "ParticleContainer/ParticleContainer.h"
#include "ParticleContainer/SimpleContainer.h"
#include "Particle.h"
#include "ParticleHandler.h"
#include "PairHandler.h"
#include "handler/ForcePrepareHandler.h"

#include <list>

using namespace std;
using namespace utils;

//Forward declarations
class BoundaryCondition;
namespace unitTest {
	class UTest_CellContainer;
	class UTest_BoundaryCondition;
}

/**
 * \brief Particle container for the linked-cell algorithm
 *
 * The linked-cell algorithm divides the domain into separate
 * cells. The particles within each cell then only interact with
 * the particles in the neigbouring cells.
 * The normal algorithm iterates over all particle pairs and therefore
 * has quadratic runtime. The linked-cell algorithm on the other hand
 * has an approximately linear runtime, leading to a significant
 * increase in performance. The following graph compares this algorithm
 * to the normal mode. The simulations were done in a two-dimensional
 * domain of size (150, 150). The resulting iteration times were averaged
 * over 20 iterations. The graph shows that the linked-cell algorithm's
 * runtime per iteration only increases approximately linearly and
 * performs significantly better, as expected.
 *
 * \image html time_linked-cell.png "Comparing the linked-cell algorithm to the normal mode" width=10cm
 * \image latex time_linked-cell.png "Comparing the linked-cell algorithm to the normal mode" width=10cm
 */
class CellContainer: public ParticleContainer {
	friend unitTest::UTest_CellContainer;
	friend unitTest::UTest_BoundaryCondition;

private:
	SimpleContainer* cells; //!< Array with one SimpleContainer per cell, including the halo region.
	Vector<double, 3> domainSize; 	//!< Domain size in each dimension.
	int* haloInds;//!< Indices of all halo cells for fast and simple iteration.
	int* boundInds;	//!< Indices of all boundary cells for fast and simple iteration.
	int haloSize;					//!< Number of halo cells.
	int boundSize;					//!< Number of boundary cells.
	bool dim3;					//!< Stores if the domain is three dimensional.

	void setHaloBoundary();

public:
	/**
	 * \brief Array with one boundary condition per domain side.
	 *
	 * The standard boundary condition is "Outflow".
	 * The domain sides are defined as following:
	 * 0: x=0
	 * 1: x=max
	 * 2: y=0
	 * 3: y=max
	 * 4: z=0
	 * 5: z=max
	 */
	BoundaryCondition *boundConds[6];

	double cutoff;					//!< Cutoff radius.
	Vector<double, 3> effDomain; //!< Effective domain size in each dimension.
	Vector<int, 3> cellCount; //!< Number of cells in each dimension \f$ N_i \f$.
	int cellTotal;					//!< Total number of cells \f$ N \f$.

	CellContainer(const Vector<double, 3> domainSize, const double cutoff,
			list<Particle>* initialParticleList = NULL);

	Vector<int, 3> calc3Ind(int n);
	int calcInd(Vector<int, 3> n);
	int calcCell(Vector<double, 3> x);

	bool empty();
	int size();

	void add(Particle& p);
	void add(list<Particle>& list);

	void remove(Particle& p);
	void remove(Particle& p, int contInd);
	void remove_halo();
	void remove_halo_virtual();

	void prepare_forces();

	void update_cells();
	void impose_boundConds();

	void iterate_halo(ParticleHandler& handler);
	void iterate_boundary(ParticleHandler& handler);
	void iterate_all(ParticleHandler& handler);
	void iterate_pairs(PairHandler& handler);
	void iterate_pairs_half(PairHandler& handler);
};

#endif /* CELLCONTAINER_H_ */
