/*
 * CellContainer.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: johannes
 */

#include "CellContainer.h"
#include "handler/CellUpdater.h"

/**
 * \brief Constructor for setting up an empty master container.
 * @param domainSize Size of the domain in 3 dimensions.
 * @param cutoff Cutoff radius of pairHandler interactions.
 */
CellContainer::CellContainer(const Vector<double, 3> domainSize,
		const double cutoff) :
		domainSize(domainSize), cutoff(cutoff) {

	//Calculate cell count in each dimension (including halo)
	cellCount[0] = domainSize[0] / cutoff + 3;
	cellCount[1] = domainSize[1] / cutoff + 3;
	cellCount[2] = domainSize[2] / cutoff + 3;

	//initialize cell list
	int N = cellCount[0] * cellCount[1] * cellCount[2];
	cells = new ParticleContainer[N];

	//set halo cells
	//iterate over cube surface
	Vector<int, 3> n;
	for (int dim = 0; dim < 3; dim++) { 	//iterate the fixed dimension
		for (int side = 0; side < 2; side++) { //iterate over the two sides of the cube (e.g. front/back)
			for (int i = 0; i < cellCount[(dim + 1) % 3]; i++) { //iterate over first free dimension
				for (int j = 0; j < cellCount[(dim + 2) % 3]; j++) { //iterate over second free dimension
					n[dim] = side * (cellCount[dim] - 1); //fixed dimension
					n[(dim + 1) % 3] = i;			//first free dimension
					n[(dim + 2) % 3] = j;			//second free dimension

					cells[calcInd(n)].halo = true;
				}
			}
		}
	}
}

/**
 * \brief Constructor for setting up the master container with an initial particle list.
 * @param initialParticleList ParticleList which is copied into the CellContainer.
 * @param domainSize Size of the domain in 3 dimensions.
 * @param cutoff Cutoff radius of pairHandler interactions.
 */
CellContainer::CellContainer(const Vector<double, 3> domainSize,
		const double cutoff, list<Particle>& initialParticleList) :
		domainSize(domainSize), cutoff(cutoff) {

	//Calculate cell count in each dimension (including halo)
	cellCount[0] = domainSize[0] / cutoff + 3;
	cellCount[1] = domainSize[1] / cutoff + 3;
	cellCount[2] = domainSize[2] / cutoff + 3;

	//initialize cell list
	int N = cellCount[0] * cellCount[1] * cellCount[2];
	cells = new ParticleContainer[N];

	//Set halo region
	//iterate over cube surface
	Vector<int, 3> n;
	for (int dim = 0; dim < 3; dim++) { 	//iterate the fixed dimension
		for (int side = 0; side < 2; side++) { //iterate over the two sides of the cube (e.g. front/back)
			for (int i = 0; i < cellCount[(dim + 1) % 3]; i++) { //iterate over first free dimension
				for (int j = 0; j < cellCount[(dim + 2) % 3]; j++) { //iterate over second free dimension
					n[dim] = side * (cellCount[dim] - 1); //fixed dimension
					n[(dim + 1) % 3] = i;			//first free dimension
					n[(dim + 2) % 3] = j;			//second free dimension

					cells[calcInd(n)].halo = true;
				}
			}
		}
	}

	//copy particles into the right cells
	add(initialParticleList);
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
	return n[0] + cellCount[0] * n[1] + cellCount[0] * cellCount[1] * n[2];
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
	Vector<double, 3> inds = x * (1 / CellContainer::cutoff);
	Vector<int, 3> n;
	n[0] = floor(inds[0]) + 1;
	n[1] = floor(inds[1]) + 1;
	n[2] = floor(inds[2]) + 1;

	//calculate cell index
	return calcInd(n);
}

/**
 * \brief Returns if the container stores any particles.
 */
bool CellContainer::empty() {
	bool empty = true;
	for (int i = 0; i < sizeof(*cells) / sizeof(*cells); i++) {
		empty &= cells[i].empty();
	}
	return empty;
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
void CellContainer::add(list<Particle>& addList) {
	list<Particle>::iterator it = addList.begin();
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
	for (int i = 0; i < sizeof(*cells) / sizeof(*cells); i++) {
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
//iterate over cube surface
	Vector<int, 3> n;
	for (int dim = 0; dim < 3; dim++) { 	//iterate the fixed dimension
		for (int side = 0; side < 2; side++) { //iterate over the two sides of the cube (e.g. front/back)
			for (int i = 0; i < cellCount[(dim + 1) % 3]; i++) { //iterate over first free dimension
				for (int j = 0; j < cellCount[(dim + 2) % 3]; j++) { //iterate over second free dimension
					n[dim] = side * (cellCount[dim] - 1); //fixed dimension
					n[(dim + 1) % 3] = i;			//first free dimension
					n[(dim + 2) % 3] = j;			//second free dimension

					cells[calcInd(n)].remove_all();
				}
			}
		}
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
	for (int i = 0; i < sizeof(*cells) / sizeof(*cells); i++) {
		if (!cells[i].halo) { //test if this cell is not in the halo region
			updater.oldContainerIndex = i;
			cells[i].iterate_all(updater);
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

//iterate over cube surface
	Vector<int, 3> n;
	for (int dim = 0; dim < 3; dim++) { 	//iterate the fixed dimension
		for (int side = 0; side < 2; side++) { //iterate over the two sides of the cube (e.g. front/back)
			for (int i = 0; i < cellCount[(dim + 1) % 3]; i++) { //iterate over first free dimension
				for (int j = 0; j < cellCount[(dim + 2) % 3]; j++) { //iterate over second free dimension
					n[dim] = side * (cellCount[dim] - 1); //fixed dimension
					n[(dim + 1) % 3] = i;			//first free dimension
					n[(dim + 2) % 3] = j;			//second free dimension

					cells[calcInd(n)].iterate_all(handler);
				}
			}
		}
	}
}

/**
 * \brief Function for iterating over all particles inside the boundary cells.
 * @param handler Object providing the compute function, which is called for every particle.
 *
 * This function iterates over all particles inside the boundary cells
 * and processes each by calling the provided function.
 *
 * If the number of cells in the third dimension is 3
 * including the halo cells, the simulation is two-dimensional
 * and the boundary cells are chosen accordingly.
 */
void CellContainer::iterate_boundary(ParticleHandler& handler) {

//iterate over cube surface
	if (cellCount[2] == 3) {
		Vector<int, 3> n;
		for (int dim = 0; dim < 2; dim++) { 	//iterate the fixed dimension
			for (int side = 0; side < 2; side++) { //iterate over the two sides of the square (e.g. front/back)
				for (int i = 1; i < cellCount[(dim + 1) % 2] - 2; i++) { //iterate over free dimension
					n[dim] = 1 + side * (cellCount[dim] - 3); //fixed dimension
					n[(dim + 1) % 2] = i;			//free dimension

					cells[calcInd(n)].iterate_all(handler);
				}
			}
		}
	} else {
		Vector<int, 3> n;
		for (int dim = 0; dim < 3; dim++) { 	//iterate the fixed dimension
			for (int side = 0; side < 2; side++) { //iterate over the two sides of the cube (e.g. front/back)
				for (int i = 1; i < cellCount[(dim + 1) % 3] - 2; i++) { //iterate over first free dimension
					for (int j = 1; j < cellCount[(dim + 2) % 3] - 2; j++) { //iterate over second free dimension
						n[dim] = 1 + side * (cellCount[dim] - 3); //fixed dimension
						n[(dim + 1) % 3] = i; 			//first free dimension
						n[(dim + 2) % 3] = j; 			//second free dimension

						cells[calcInd(n)].iterate_all(handler);
					}
				}
			}
		}
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
	for (int i = 0; i < sizeof(*cells) / sizeof(*cells); i++) {
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
	for (int i = 0; i < sizeof(*cells) / sizeof(*cells); i++) {
		if (!cells[i].halo) { //test if this cell is not in the halo region.
			//iterate inside of cell
			cells[i].iterate_pairs(handler);

			Vector<int, 3> n = calc3Ind(i);
			Vector<int, 3> tempN;
			//iterate over surrounding non-halo cells
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					for (int z = -1; z <= 1; z++) {
						tempN[0] = n[0] + x;
						tempN[1] = n[1] + y;
						tempN[2] = n[2] + z;
						if (!cells[calcInd(tempN)].halo //test if not a halo cell
						&& !(x == 0 && y == 0 && z == 0)) { //do not iterate over the cell itself
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
//iterate over all cells
	for (int i = 0; i < sizeof(*cells) / sizeof(*cells); i++) {
		if (!cells[i].halo) { //test if this cell is not in the halo region.
			//iterate inside of cell
			cells[i].iterate_pairs_half(handler);

			Vector<int, 3> n = calc3Ind(i);
			Vector<int, 3> tempN;
			//iterate over surrounding non-halo cells
			for (int x = 0; x <= 1; x++) {
				for (int y = 0; y <= 1; y++) {
					for (int z = 0; z <= 1; z++) {
						tempN[0] = n[0] + x;
						tempN[1] = n[1] + y;
						tempN[2] = n[2] + z;
						if (!cells[calcInd(tempN)].halo //test if not a halo cell
						&& !(x == 0 && y == 0 && z == 0)) { //do not iterate over the cell itself
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
