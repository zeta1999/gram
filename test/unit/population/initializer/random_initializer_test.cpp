#include "gram/population/initializer/RandomInitializer.h"

#include <catch.hpp>
#include <fakeit.hpp>

using namespace fakeit;
using namespace gram;
using namespace std;

#include "gram/individual/Genotype.h"
#include "gram/individual/Individual.h"
#include "gram/population/Population.h"
#include "gram/population/reproducer/Reproducer.h"
#include "gram/random/number_generator/NumberGenerator.h"
#include <gram/error/NoIndividuals.h>
#include <gram/error/ZeroGenotypeLength.h>

TEST_CASE("random initializer requires valid genotype length", "[random_initializer]") {
  Mock<NumberGenerator> numberGeneratorMock;
  Fake(Dtor(numberGeneratorMock));
  auto numberGenerator = unique_ptr<NumberGenerator>(&numberGeneratorMock.get());

  REQUIRE_THROWS_AS(RandomInitializer(move(numberGenerator), 0), ZeroGenotypeLength);
}

TEST_CASE("random initializer requires valid population size", "[random_initializer]") {
  Mock<NumberGenerator> numberGeneratorMock;
  Fake(Dtor(numberGeneratorMock));
  auto numberGenerator = unique_ptr<NumberGenerator>(&numberGeneratorMock.get());

  Mock<Reproducer> reproducerMock;
  Fake(Dtor(reproducerMock));
  auto reproducer = unique_ptr<Reproducer>(&reproducerMock.get());

  RandomInitializer initializer(move(numberGenerator), 200);

  REQUIRE_THROWS_AS(initializer.initialize(0, move(reproducer)), NoIndividuals);
}

TEST_CASE("random initializer initializes new population", "[random_initializer]") {
  Genotype genotype1({0, 1, 2});
  Genotype genotype2({3, 0, 1});
  Genotype genotype3({2, 3, 0});

  Individual individual1(genotype1);
  Individual individual2(genotype2);
  Individual individual3(genotype3);

  Mock<NumberGenerator> numberGeneratorMock;
  Fake(Dtor(numberGeneratorMock));
  When(Method(numberGeneratorMock, generateMany))
      .Return(vector<unsigned long>({0, 1, 2}))
      .Return(vector<unsigned long>({3, 0, 1}))
      .Return(vector<unsigned long>({2, 3, 0}));
  auto numberGenerator = unique_ptr<NumberGenerator>(&numberGeneratorMock.get());

  Mock<Reproducer> reproducerMock;
  Fake(Dtor(reproducerMock));
  auto reproducer = unique_ptr<Reproducer>(&reproducerMock.get());

  RandomInitializer initializer(move(numberGenerator), 3);

  Population population = initializer.initialize(3, move(reproducer));

  REQUIRE(population.size() == 3);
  REQUIRE(population[0] == individual1);
  REQUIRE(population[1] == individual2);
  REQUIRE(population[2] == individual3);
  REQUIRE(population.generationNumber() == 0);
}
