/*
 * CellContainer.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: johannes
 */

#include "CellContainer.h"
#include "handler/CellUpdater.h"
#include "BoundaryCondition/BoundaryCondition.h"
#include "BoundaryCondition/Outflow.h"

#include <log4cxx/logger.h>
#include <stdlib.h>
using namespace log4cxx;

LoggerPtr CellLogger(Logger::getLogger("MolSim.CellContainer"));

/**
 * \brief Auxiliary function for setting halo cells and generating the haloInds and boundInds lists.
 *
 * This methods iterates over the cube surface for reaching all halo cells and over the
 * inner cube surface for reaching all boundary cells.
 */
void CellContainer::setHaloBoundary() {
	//set halo cells
	//iterate over cube surface
	Vector<int, 3> n;
	int cellNr = 0;
	if (dim3) {
		//calculate overall size of the haloInds array
		haloSize = 2
				* ((cellCount[0] - 1) * (cellCount[1] - 1)
						+ (cellCount[0] - 1) * (cellCount[2] - 1)
						+ (cellCount[1] - 1) * (cellCount[2] - 1) + 1);
		haloInds = new int[haloSize];

		//iterate over top and bottom
		for (int side = 0; side < 2; side++) { //iterate over both sides
			for (int y = 0; y < cellCount[1]; y++) { //iterate over area
				for (int z = 0; z < cellCount[2]; z++) { //iterate over area

					//calculate indices
					n[0] = side * (cellCount[0] - 1);
					n[1] = y;
					n[2] = z;

					//set cell as halo cell and store index in haloInds
					cells[calcInd(n)].halo = true;
					haloInds[cellNr] = calcInd(n);
					cellNr++;
				}
			}
		}
		//iterate over surrounding sides (front, left, right and back)
		for (int x = 1; x < cellCount[0] - 1; x++) { //iterate over the whole height
			for (int side = 0; side < 2; side++) { //iterate over both sides
				for (int y = 0; y < cellCount[1]; y++) { //iterate over front/back line

					//calculate indices
					n[0] = x;
					n[1] = y;
					n[2] = side * (cellCount[2] - 1);

					//set cell as halo cell and store index in haloInds
					cells[calcInd(n)].halo = true;
					haloInds[cellNr] = calcInd(n);
					cellNr++;
				}
				for (int z = 1; z < cellCount[2] - 1; z++) { //iterate over left/right line

					//calculate indices
					n[0] = x;
					n[1] = side * (cellCount[2] - 1);
					n[2] = z;

					//set cell as halo cell and store index in haloInds
					cells[calcInd(n)].halo = true;
					haloInds[cellNr] = calcInd(n);
					cellNr++;
				}
			}
		}
	} else {
		//calculate overall size of the haloInds array
		haloSize = 2 * (cellCount[0] + cellCount[1] - 2);
		haloInds = new int[haloSize];
		n[2] = 0;

		for (int side = 0; side < 2; side++) { //iterate over both sides
			for (int x = 0; x < cellCount[0]; x++) { //iterate over front/back line

				//calculate indices
				n[0] = x;
				n[1] = side * (cellCount[1] - 1);

				//set cell as halo cell and store index in haloInds
				cells[calcInd(n)].halo = true;
				haloInds[cellNr] = calcInd(n);
				cellNr++;
			}
			for (int y = 1; y < cellCount[1] - 1; y++) { //iterate over left/right line

				//calculate indices
				n[0] = side * (cellCount[0] - 1);
				n[1] = y;

				//set cell as halo cell and store index in haloInds
				cells[calcInd(n)].halo = true;
				haloInds[cellNr] = calcInd(n);
				cellNr++;
			}
		}
	}
	if (haloSize != cellNr) {
		LOG4CXX_FATAL(CellLogger,
				"ERROR: Something went wrong creating the halo cells. Number of cells not matching expectation (Expected: " << haloSize << ", actual: " << cellNr);
		exit(1);
	}

	//set boundary cells
	//iterate over inner cube surface
	cellNr = 0;
	if (dim3) {

		//check if domain size makes sense for creating boundary cells
		if (cellCount[2] == 3) {
			LOG4CXX_FATAL(CellLogger,
					"ERROR: Domain too small in z-direction (<= cutoff radius). All cells would be boundary cells.");
			exit(1);
		}

		//calculate overall size of the boundInds array
		boundSize = 2
				* ((cellCount[0] - 3) * (cellCount[1] - 3)
						+ (cellCount[0] - 3) * (cellCount[2] - 3)
						+ (cellCount[1] - 3) * (cellCount[2] - 3) + 1);
		boundInds = new int[boundSize];

		//iterate over top and bottom
		for (int side = 0; side < 2; side++) { //iterate over both sides
			for (int y = 1; y < cellCount[1] - 1; y++) { //iterate over area
				for (int z = 1; z < cellCount[2] - 1; z++) { //iterate over area

					//calculate indices
					n[0] = 1 + side * (cellCount[0] - 3);
					n[1] = y;
					n[2] = z;

					//store cell index in boundInds
					boundInds[cellNr] = calcInd(n);
					cellNr++;
				}
			}
		}
		//iterate over surrounding sides (front, left, right and back)
		for (int x = 2; x < cellCount[0] - 2; x++) { //iterate over the whole height
			for (int side = 0; side < 2; side++) { //iterate over both sides
				for (int y = 1; y < cellCount[1] - 1; y++) { //iterate over front/back line

					//calculate indices
					n[0] = x;
					n[1] = y;
					n[2] = 1 + side * (cellCount[2] - 3);

					//store cell index in boundInds
					boundInds[cellNr] = calcInd(n);
					cellNr++;
				}
				for (int z = 2; z < cellCount[2] - 2; z++) { //iterate over left/right line

					//calculate indices
					n[0] = x;
					n[1] = 1 + side * (cellCount[2] - 3);
					n[2] = z;

					//store cell index in boundInds
					boundInds[cellNr] = calcInd(n);
					cellNr++;
				}
			}
		}
	} else {
		//calculate overall size of the boundInds array
		boundSize = 2 * (cellCount[0] + cellCount[1] - 6);
		boundInds = new int[boundSize];
		n[2] = 0;

		for (int side = 0; side < 2; side++) { //iterate over both sides
			for (int x = 1; x < cellCount[0] - 1; x++) { //iterate over front/back line

				//calculate indices
				n[0] = x;
				n[1] = 1 + side * (cellCount[1] - 3);

				//store cell index in boundInds
				boundInds[cellNr] = calcInd(n);
				cellNr++;
			}
			for (int y = 2; y < cellCount[1] - 2; y++) { //iterate over left/right line

				//calculate indices
				n[0] = 1 + side * (cellCount[0] - 3);
				n[1] = y;

				//store cell index in boundInds
				boundInds[cellNr] = calcInd(n);
				cellNr++;
			}
		}
	}
	if (boundSize != cellNr) {
		LOG4CXX_FATAL(CellLogger,
				"ERROR: Something went wrong creating the boundary cells. Number of cells not matching expectation (Expected: " << boundSize << ", actual: " << cellNr);
		exit(1);
	}
}

/**
 * \brief Constructor for setting up the master container with an initial particle list.
 * @param initialParticleList ParticleList which is copied into the CellContainer.
 * @param domainSize Size of the domain in 3 dimensions.
 * @param cutoff Cutoff radius of pairHandler interactions.
 */
CellContainer::CellContainer(const Vector<double, 3> domainSize,
		const double cutoff, std::vector<Particle>* initialParticleList) :
		domainSize(domainSize), cutoff(cutoff) {

	LOG4CXX_DEBUG(CellLogger,
			"Generating cell container: domain size = " << domainSize.toString() << ", cutoff radius = " << cutoff);

	//Calculate cell count in each dimension (including halo)
	cellCount[0] = domainSize[0] / cutoff + 3;
	cellCount[1] = domainSize[1] / cutoff + 3;
	if (domainSize[2] == 0) {
		dim3 = false;
		cellCount[2] = 0;
	} else {
		dim3 = true;
		cellCount[2] = domainSize[2] / cutoff + 3;
	}

	//Calculate effective domain size
	effDomain[0] = (cellCount[0] - 2) * cutoff;
	effDomain[1] = (cellCount[1] - 2) * cutoff;
	if (dim3) {
		effDomain[2] = (cellCount[2] - 2) * cutoff;
	} else {
		effDomain[2] = cutoff;
	}

	//initialize cell list
	int N;
	if (dim3) {
		N = cellCount[0] * cellCount[1] * cellCount[2];
	} else {
		N = cellCount[0] * cellCount[1];
	}
	cells = new SimpleContainer[N];
	cellTotal = N;

	//Set halo and boundary cells
	setHaloBoundary();

	//Set default boundary conditions
	for (int i = 0; i < 6; i++) {
		boundConds[i] = new Outflow(i);
	}

	//copy particles into the right cells
	if (initialParticleList != NULL) {
		add(*initialParticleList);
	}
}

/**
 * \brief Auxiliary function for calculating the three-dimensional cell index.
 * @param n Linearized cell index.
 * @return Cell index of the particle container.
 *
 * The index is calculated using the following equation:
 * \f{eqnarray*}{
 * n_0 &=& \left( n\ \mbox{mod}\ N_0 N_1 \right)\ \mbox{mod}\ N_0\\
 * n_1 &=& \left \lfloor \frac{n\ \mbox{mod}\ N_0 N_1 }{N_0} \right \rfloor\\
 * n_2 &=& \left \lfloor \frac{n}{N_0 N_1} \right \rfloor
 * \f}
 *
 * With n being the linearized index and \f$ n_i \f$ being the index and
 * \f$ N_i \f$ being the cellCount in the respective dimension.
 */
Vector<int, 3> CellContainer::calc3Ind(int n) {
	Vector<int, 3> ind;
	ind[0] = ((n % (cellCount[0] * cellCount[1])) % cellCount[0]);
	ind[1] = floor((n % (cellCount[0] * cellCount[1])) / (1.0 * cellCount[0]));
	ind[2] = floor(n / (1.0 * cellCount[0] * cellCount[1]));

	return ind;
}

/**
 * \brief Auxiliary function for calculating the linearized cell index.
 * @param n Three-dimensional index.
 * @return Cell index of the particle container.
 *
 * The index is calculated using the following equation:
 * \f[
 * n = n_0 + N_0 \cdot n_1 + N_0 N_1 \cdot n_2
 * \f]
 *
 * With \f$ n_i \f$ being the index and
 * \f$ N_i \f$ being the cellCount in the respective dimension.
 */
int CellContainer::calcInd(Vector<int, 3> n) {
	if (dim3) {
		if ((n[0] < 0 || n[0] >= cellCount[0])
				|| (n[1] < 0 || n[1] >= cellCount[1])
				|| (n[2] < 0 || n[2] >= cellCount[2])) {
			LOG4CXX_FATAL(CellLogger,
					"Error calculating linearized cell index: Index out of domain (n = " << n.toString() << " out of N = " << cellCount.toString() << ")");
			exit(1);
		}
		return n[0] + cellCount[0] * n[1] + cellCount[0] * cellCount[1] * n[2];
	} else {
		if ((n[0] < 0 || n[0] >= cellCount[0])
				|| (n[1] < 0 || n[1] >= cellCount[1])) {
			LOG4CXX_FATAL(CellLogger,
					"Error calculating linearized cell index: Index out of domain (n = " << n.toString() << " out of N = " << cellCount.toString() << ")");
			exit(1);
		}
		return n[0] + cellCount[0] * n[1];
	}
}

/**
 * \brief Auxiliary function for calculating the cell index from Particle coordinates.
 * @param x Coordinates for which the index is calculated
 * @return Cell index of the particle container.
 *
 * The index is calculated using the following equation:
 * \f[
 * n = \left \lfloor \frac{x_0}{r_{cutoff}} + 1 \right \rfloor
 * 	+ N_0 \cdot \left \lfloor \frac{x_1}{r_{cutoff}} + 1 \right \rfloor
 * 	+ N_0 N_1 \cdot \left \lfloor \frac{x_2}{r_{cutoff}} + 1 \right \rfloor
 * \f]
 *
 * With \f$ x_i \f$ being the coordinate and
 * \f$ N_i \f$ being the cellCount in the respective dimension.
 * The addition by 1 is necessary due to the halo region.
 */
int CellContainer::calcCell(Vector<double, 3> x) {

//calculate index in each dimension
	Vector<double, 3> inds = x * (1 / cutoff);
	Vector<int, 3> n;
	n[0] = floor(inds[0]) + 1;
	n[1] = floor(inds[1]) + 1;
	n[2] = floor(inds[2]) + 1 * dim3;

	//calculate cell index
	return calcInd(n);
}

/**
 * \brief Returns if the container stores any particles.
 */
bool CellContainer::empty() {
	bool empty = true;
	for (int i = 0; i < cellTotal; i++) {
		empty &= cells[i].empty();
	}
	return empty;
}

/**
 * \brief Returns how many particles the container stores (not including the halo region).
 */
int CellContainer::size() {
	int cnt = 0;
	for (int i = 0; i < cellTotal; i++) {
		if (!cells[i].halo) {
			cnt += cells[i].size();
		}
	}
	return cnt;
}

/**
 * \brief Adds a particle to the right particle container.
 * @param p Particle to add.
 */
void CellContainer::add(Particle& p) {
	cells[calcCell(p.getX())].add(p);
}

/**
 * \brief Adds particles from a list to the particle containers.
 * @param list List of the particles to add.
 */
void CellContainer::add(std::vector<Particle>& addList) {
	std::vector<Particle>::iterator it = addList.begin();
	while (it != addList.end()) {
		add(*it);
		it++;
	}
}

/**
 * \brief Removes the particle from all particle containers.
 * @param p Particle to remove.
 *
 * This function removes all particles that match the
 * properties of the specified particle from all containers.
 */
void CellContainer::remove(Particle& p) {
	for (int i = 0; i < cellTotal; i++) {
		cells[i].remove(p);
	}
}

/**
 * \brief Removes the particle from the specified particle container.
 * @param p Particle to remove.
 * @param contInd Index of the ParticleContainer to be searched.
 *
 * This function removes all particles that match the
 * properties of the specified particle from the container
 * with the specified index.
 *
 * This function is useful for updating particles.
 */
void CellContainer::remove(Particle& p, int contInd) {
	cells[contInd].remove(p);
}

/**
 * \brief Removes all particles from the halo cells.
 */
void CellContainer::remove_halo() {
//iterate over all halo cells
	for (int i = 0; i < haloSize; i++) {
		cells[haloInds[i]].remove_all();
	}
}

/**
 * \brief Removes all virtual particles from the halo cells.
 */
void CellContainer::remove_halo_virtual() {
//iterate over all halo cells
	for (int i = 0; i < haloSize; i++) {
		cells[haloInds[i]].remove_virtual();
	}
}

/**
 * \brief Function for updating the cells for all particles.
 *
 * This method should always be called after
 * changing the positions of the particles.
 */
void CellContainer::update_cells() {
	CellUpdater updater = CellUpdater(this);

	//iterate over all cells
	for (int i = 0; i < cellTotal; i++) {
		if (!cells[i].halo) { //test if this cell is not in the halo region
			updater.oldContainerIndex = i;
			cells[i].iterate_all(updater);
		}
	}

	std::list<pair<Particle, int> >::iterator it = updater.toRemove.begin();
	while (it != updater.toRemove.end()) {
		remove((*it).first, (*it).second);
		it++;
	}
}

/**
 * \brief Function for imposing boundary conditions.
 *
 * This method should always be called after
 * changing the positions of the particles.
 *
 * The boundary conditions for particles at the corners
 * are imposed twice/three times (as they should be).
 */
void CellContainer::impose_boundConds() {

	//first impose conditions on halo cells
	Vector<int, 3> n;
	for (int i = 0; i < haloSize; i++) {
		n = calc3Ind(haloInds[i]);
		//Find the right boundary
		for (int dim = 0; dim < 2 + dim3; dim++) {
			if (n[dim] == 0) {
				//check if the condition acts on halo cells
				if (boundConds[2 * dim]->haloCells) {
					boundConds[2 * dim]->impose(&cells[haloInds[i]]);
				}
			} else if (n[dim] == cellCount[dim] - 1) {
				//check if the condition acts on halo cells
				if (boundConds[2 * dim + 1]->haloCells) {
					boundConds[2 * dim + 1]->impose(&cells[haloInds[i]]);
				}
			}
		}
	}

	//impose conditions on boundary cells after halo cells
	for (int i = 0; i < boundSize; i++) {
		n = calc3Ind(boundInds[i]);
		//Find the right boundary
		for (int dim = 0; dim < 2 + dim3; dim++) {
			if (n[dim] == 1) {

				//check if the condition acts on boundary cells
				if (boundConds[2 * dim]->boundCells) {
					boundConds[2 * dim]->impose(&cells[boundInds[i]]);
				}
			} else if (n[dim] == cellCount[dim] - 2) {

				//check if the condition acts on boundary cells
				if (boundConds[2 * dim + 1]->boundCells) {
					boundConds[2 * dim + 1]->impose(&cells[boundInds[i]]);
				}
			}
		}
	}
}

/**
 * \brief Function for iterating over all particles inside the halo cells.
 * @param handler Object providing the compute function, which is called for every particle.
 *
 * This function iterates over all particles inside the halo cells
 * and processes each by calling the provided function.
 */
void CellContainer::iterate_halo(ParticleHandler& handler) {
//iterate over all halo cells
	for (int i = 0; i < haloSize; i++) {
		cells[haloInds[i]].iterate_all(handler);
	}
}

/**
 * \brief Function for iterating over all particles inside the boundary cells.
 * @param handler Object providing the compute function, which is called for every particle.
 *
 * This function iterates over all particles inside the boundary cells
 * and processes each by calling the provided function.
 */
void CellContainer::iterate_boundary(ParticleHandler& handler) {
//iterate over all boundary cells
	for (int i = 0; i < boundSize; i++) {
		cells[boundInds[i]].iterate_all(handler);
	}
}

/**
 * \brief Function for iterating over all active particles.
 * @param handler Object providing the compute function, which is called for every particle.
 *
 * This function iterates over all particles except for those in
 * the halo cells and processes each by calling the provided function.
 */
void CellContainer::iterate_all(ParticleHandler& handler) {

//iterate over all cells
	for (int i = 0; i < cellTotal; i++) {
		if (!cells[i].halo) { //test if this cell is not in the halo region
			cells[i].iterate_all(handler);
		}
	}
}

/**
 * \brief Function for iterating over all particle pairs.
 *
 * @param handler Object providing the compute function, which is called for every particle pair.
 *
 * This function iterates over all particle pairs and processes
 * each by calling the provided function.
 *
 * Force calculators use Newton's third law and therefore give
 * wrong outputs with this method. Use ParticleContainer::iterate_pairs_half instead.
 */
void CellContainer::iterate_pairs(PairHandler& handler) {
//iterate over all cells
	int cnt = 0;
	for (int i = 0; i < cellTotal; i++) {
		if (!cells[i].halo) { //test if this cell is not in the halo region.
			//iterate inside of cell
			cells[i].iterate_pairs(handler);

			Vector<int, 3> n = calc3Ind(i);
			Vector<int, 3> tempN;
			//iterate over surrounding cells, including halo cells.
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					if (dim3) {
						for (int z = -1; z <= 1; z++) {
							tempN[0] = n[0] + x;
							tempN[1] = n[1] + y;
							tempN[2] = n[2] + z;
							if (!(x == 0 && y == 0 && z == 0)) { //do not iterate over the cell itself
								cells[calcInd(n)].iterate_partner(handler,
										&cells[calcInd(tempN)]);
							}
						}
					} else {
						tempN[0] = n[0] + x;
						tempN[1] = n[1] + y;
						tempN[2] = n[2];
						if (!(x == 0 && y == 0)) { //do not iterate over the cell itself
							cells[calcInd(n)].iterate_partner(handler,
									&cells[calcInd(tempN)]);
						}
					}
				}
			}
		}
	}
}

/**
 * \brief Function for iterating over unique particle pairs.
 * @param handler Object providing the compute function, which is called for every particle pair.
 *
 * This function uniquely iterates over all particle pairs and processes
 * each by calling the provided function. While `iterate_pairs` would process
 * both the particle pairs (a,b) and (b,a), this function only processes (a,b).
 *
 * This way the performance can be improved using Newton's third law.
 */
void CellContainer::iterate_pairs_half(PairHandler& handler) {
	//iterate over all non-halo cells
	for (int i = 0; i < cellTotal; i++) {
		if (!cells[i].halo) { //test if this cell is not in the halo region.
			//iterate inside of cell
			cells[i].iterate_pairs_half(handler);

			Vector<int, 3> n = calc3Ind(i);
			Vector<int, 3> tempN;
			//iterate over surrounding cells, including halo cells.
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					if (dim3) {
						for (int z = -1; z <= 1; z++) {
							tempN[0] = n[0] + x;
							tempN[1] = n[1] + y;
							tempN[2] = n[2] + z;
							if (calcInd(tempN) < i //only iterate over cells before this one
									|| cells[calcInd(tempN)].halo) { //except halo cells (preventing asymmetry with virtual particles)
								cells[calcInd(n)].iterate_partner(handler,
										&cells[calcInd(tempN)]);
							}
						}
					} else {
						tempN[0] = n[0] + x;
						tempN[1] = n[1] + y;
						tempN[2] = n[2];
						if (calcInd(tempN) < i //only iterate over cells before this one
								|| cells[calcInd(tempN)].halo) { //except halo cells (preventing asymmetry with virtual particles)
							cells[calcInd(n)].iterate_partner(handler,
									&cells[calcInd(tempN)]);
						}
					}
				}
			}
		}
	}
}

/**
 * \brief Function for preparing the forces saved in the particle list.
 *
 * This function resets the forces calculated in the previous iteration step.
 * This preparation step is necessary for the calculation of the new forces.
 */
void CellContainer::prepare_forces() {
	iterate_all(*new ForcePrepareHandler());
}
