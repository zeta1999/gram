#include "gram/individual/Individual.h"

#include <vector>

#include "gram/error/FitnessNotCalculated.h"
#include "gram/evaluation/Evaluator.h"
#include "gram/language/mapper/Mapper.h"
#include "gram/operator/crossover/Crossover.h"
#include "gram/operator/mutation/Mutation.h"

using namespace gram;
using namespace std;

Individual::Individual(Genotype genotype) : genotype(move(genotype)), fitnessScore(0.0), fitnessCalculated(false) {
  //
}

Individual Individual::mateWith(const Individual& partner, Crossover& crossover) const {
  Genotype childGenotype = crossover.apply(genotype, partner.genotype);

  return Individual(childGenotype);
}

void Individual::mutate(Mutation& mutation) {
  genotype = mutation.apply(genotype);
}

void Individual::assignFitness(Fitness fitness) {
  fitnessScore = fitness;
  fitnessCalculated = true;
}

Fitness Individual::fitness() const {
  if (!fitnessCalculated) {
    throw FitnessNotCalculated();
  }

  return fitnessScore;
}

bool Individual::hasFitnessCalculated() const {
  return fitnessCalculated;
}

Phenotype Individual::serialize(Mapper& mapper) const {
  return mapper.map(genotype);
}

bool Individual::operator==(const Individual& individual) const {
  return genotype == individual.genotype;
}

bool Individual::operator!=(const Individual& individual) const {
  return !operator==(individual);
}
