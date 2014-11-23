/*
 * UTestCellContainer.cpp
 *
 *  Created on: Nov 22, 2014
 *      Author: johannes
 */

#include "UTest_CellContainer.h"
#include "countParticles.h"
#include "countPairs.h"

namespace unitTest {

// Registration of the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(UTest_CellContainer);

/**
 * \brief Initializes the domainSize, cutoff radius and cell container
 *
 * The domainSize is set to (40, 40, 40) and the cutoff radius to 3.0.
 */
UTest_CellContainer::UTest_CellContainer() :
		domainSize(utils::Vector<double, 3>(40)), cutoff(3), cellContainer(
				CellContainer(domainSize, cutoff)) {
}

/**
 * \brief Set up a cell container.
 *
 * The cell container is set up with UTest_CellContainer::numParticles particles.
 * The particles are placed along the diagonal of the cell container.
 * Additionally, UTest_CellContainer::numHalo particles are placed inside the
 * halo region, half of them at either end of the diagonal.
 */
void UTest_CellContainer::setUp() {
	double x[] = { 0, 0, 0 };
	double v[] = { 1, 1, 1 };
	double m = 1;

	double test[] = { 0, 0, 0 };
	for (int j = 0; j < 3; j++) {
		test[j] += floor(numParticles/2) * domainSize[j] / numParticles;
	}

	std::list<Particle> initialParticleList;
	for (int i = 0; i < numParticles; i++) {
		Particle p(x, v, m);
		for (int j = 0; j < 3; j++) {
			x[j] += domainSize[j] / numParticles;
		}
		initialParticleList.push_back(p);
	}
	cellContainer = CellContainer(domainSize, cutoff, initialParticleList);


	//Add particles in halo region
	for (int j = 0; j < 3; j++) {
		x[j] = - cutoff * 0.5;
	}
	std::list<Particle> haloParticleList;
	for (int i = 0; i < numHalo; i++) {
		Particle p(x, v, m);
		if(i >= numHalo/2){
			for (int j = 0; j < 3; j++) {
				x[j] = domainSize[j] + cutoff;
			}
		}
		haloParticleList.push_back(p);
	}
	cellContainer.add(haloParticleList);
}

/**
 * \brief Free the used resources.
 */
void UTest_CellContainer::tearDown() {
}

/**
 * \brief Method for testing if CellContainer::size returns the correct number of particles.
 */
void UTest_CellContainer::testSize() {
	CPPUNIT_ASSERT(numParticles == cellContainer.size());
}

/**
 * \brief Method for testing if CellContainer::add adds the correct number of particles.
 */
void UTest_CellContainer::testAddSize() {

	//set up a particle
	double x[] = { 0, 0, 0 };
	double v[] = { 1, 1, 1 };
	double m = 1;
	Particle p(x, v, m);

	//Test the addition of a single particle
	cellContainer.add(p);
	CPPUNIT_ASSERT(numParticles + 1 == cellContainer.size());

	//Test the addition of a particle list
	std::list<Particle> lsPart;
	for (int i = 0; i < numParticles; i++) {
		lsPart.push_back(p);
	}
	cellContainer.add(lsPart);
	CPPUNIT_ASSERT(2 * numParticles + 1 == cellContainer.size());
}

/**
 * \brief Method for testing if CellContainer::remove removes the correct number of particles.
 */
void UTest_CellContainer::testRemoveSize(){

	//set up a particle
	double x[] = { 0, 0, 0 };
	double v[] = { 1, 1, 1 };
	double m = 1;
	Particle p(x, v, m);

	//Test the removal of a particle
	cellContainer.remove(p);
	CPPUNIT_ASSERT(numParticles - 1 == cellContainer.size());

	//Test the removal of a particle from a specific container
	//Add particle
	for (int j = 0; j < 3; j++) {
		x[j] += floor(numParticles/2) * domainSize[j] / numParticles;
	}
	p = Particle(x, v, m);
	cellContainer.cells[cellContainer.calcCell(x)].add(p);
	CPPUNIT_ASSERT(numParticles == cellContainer.size());

	//Remove particle
	cellContainer.remove(p,cellContainer.calcCell(x));
	CPPUNIT_ASSERT(numParticles - 1 == cellContainer.size());
}

/**
 * \brief Method for testing if CellContainer::remove_halo removes all halo particles.
 */
void UTest_CellContainer::testRemoveHalo(){
	cellContainer.remove_halo();
	countParticles cntPart = countParticles();
	cellContainer.iterate_halo(cntPart);
	CPPUNIT_ASSERT(cntPart.cnt == 0);
	CPPUNIT_ASSERT(numParticles == cellContainer.size());
}

/**
 * \brief Method for testing if CellContainer::iterate_boundary iterates over the correct number of particles.
 */
void UTest_CellContainer::testIterateBoundaryCount(){
	countParticles cntPart = countParticles();
	cellContainer.iterate_halo(cntPart);

	//Calculate how many cells are in the boundary
	int boundCnt = 0;
	double x[3] = { 0, 0, 0 };
	int nMin[3] = {1,1,1}; //lower left bottom cell
	int nMax[3]; //upper right top cell
	nMax[0] = cellContainer.cellCount[0] - 2;
	nMax[1] = cellContainer.cellCount[1] - 2;
	nMax[2] = cellContainer.cellCount[2] - 2;
	for (int i = 0; i < numParticles; i++) {
		for (int j = 0; j < 3; j++) {
			x[j] += domainSize[j] / numParticles;
		}
		if(cellContainer.calcCell(x) == cellContainer.calcInd(nMin) || cellContainer.calcCell(x) == cellContainer.calcInd(nMax)){
			boundCnt++;
		}
	}

	CPPUNIT_ASSERT(cntPart.cnt == boundCnt);
}

/**
 * \brief Method for testing if CellContainer::iterate_halo iterates over the correct number of particles.
 */
void UTest_CellContainer::testIterateHaloCount(){
	countParticles cntHalo = countParticles();
	cellContainer.iterate_halo(cntHalo);
	CPPUNIT_ASSERT(cntHalo.cnt == numHalo);
}

/**
 * \brief Method for testing if CellContainer::iterate_all iterates over the correct number of particles.
 */
void UTest_CellContainer::testIterateCount() {
	countParticles cntPart = countParticles();
	cellContainer.iterate_all(cntPart);
	CPPUNIT_ASSERT(cntPart.cnt == cellContainer.size());
}

/**
 * \brief Method for testing if CellContainer::iterate_pairs iterates over the correct number of particle pairs.
 *
 * Since the particles are distributed evenly along the diagonal of the cell container,
 * each particle should have \f$n_\text{neigbours} = 3 n_\text{cell} = 3 \cdot \frac{n_\text{tot}}{N_\text{cells} - 2} \f$ neighbours,
 * with \f$ N_\text{cells} \f$ being the total number of cells per dimension.
 * This leads to a total of \f$ n_\text{neigbours} = 3 n_\text{cell} n_\text{tot} - 2 n_\text{cell}^2 \f$ particle pairs,
 * the second term being due to particles in the boundary cells having fewer neigbours.
 * Since the exact particle distribution is unknown, this estimation can lead to an error of up to one interaction partner per particle.
 * The uncertainty is therefore limited by the number of particles.
 */
void UTest_CellContainer::testIteratePairCount() {
	double partsPerCell = numParticles / (cellContainer.cellCount[0] - 2);
	double avgCount = partsPerCell * numParticles * 3	//All particles interact with 3 cells
			- partsPerCell * partsPerCell * 2;			//except those in boundary cells
	countPairs cntPairs = countPairs();
	cellContainer.iterate_pairs(cntPairs);
	CPPUNIT_ASSERT(
			fabs(cntPairs.cnt - avgCount)
					<= numParticles);
}

/**
 * \brief Method for testing if CellContainer::iterate_pairs_half iterates over the correct number of particle pairs.
 *
 * Since the particles are distributed evenly along the diagonal of the cell container,
 * each particle should have \f$n_\text{neigbours} = 3 n_\text{cell} = 3 \cdot \frac{n_\text{tot}}{N_\text{cells} - 2} \f$ neighbours,
 * with \f$ N_\text{cells} \f$ being the total number of cells per dimension.
 * This leads to a total of \f$ n_\text{neigbours} = 0.5 \cdot \left( 3 n_\text{cell} n_\text{tot} - 2 n_\text{cell}^2 \right) \f$ particle pairs,
 * the second term being due to particles in the boundary cells having fewer neigbours.
 * Since the exact particle distribution is unknown, this estimation can lead to an error of up to one interaction partner per particle.
 * The uncertainty is therefore limited by the number of particles.
 */
void UTest_CellContainer::testIteratePairHalfCount() {
	double partsPerCell = numParticles / (cellContainer.cellCount[0] - 2);
	double avgCount = partsPerCell * numParticles * 3	//All particles interact with 3 cells
			- partsPerCell * partsPerCell * 2;			//except those in boundary cells
	avgCount *= 0.5;
	countPairs cntPairs = countPairs();
	cellContainer.iterate_pairs_half(cntPairs);
	CPPUNIT_ASSERT(
			fabs(cntPairs.cnt - avgCount)
					<= numParticles);
}

}
