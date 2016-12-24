#include <gtest/gtest.h>
#include <gtest/fakeit.hpp>

#include <gram/individual/operator/Crossover.h>
#include <gram/util/number_generator/TwisterNumberGenerator.h>

using namespace gram::individual;
using namespace gram::util;

using namespace fakeit;

TEST(crossover_operator_test, test_it_combines_genotypes_of_the_same_length) {
  Mock<NumberGenerator> mock;
  Fake(Dtor(mock));
  When(Method(mock,generate)).Return(2);
  auto numberGenerator = std::unique_ptr<NumberGenerator>(&mock.get());

  Crossover crossover(std::move(numberGenerator));

  Genotype genotype1({0, 1, 2, 3, 4});
  Genotype genotype2({5, 6, 7, 8, 9});

  ASSERT_EQ(Genotype({0, 1, 7, 8, 9}), crossover.apply(genotype1, genotype2));
}

TEST(crossover_operator_test, test_it_combines_short_and_long_genotypes) {
  Mock<NumberGenerator> mock;
  Fake(Dtor(mock));
  When(Method(mock,generate)).Return(2);
  auto numberGenerator = std::unique_ptr<NumberGenerator>(&mock.get());

  Crossover crossover(std::move(numberGenerator));

  Genotype genotype1({0, 1, 2});
  Genotype genotype2({5, 6, 7, 8, 9});

  ASSERT_EQ(Genotype({0, 1, 7, 8, 9}), crossover.apply(genotype1, genotype2));
}

TEST(crossover_operator_test, test_it_combines_long_and_short_genotypes) {
  Mock<NumberGenerator> mock;
  Fake(Dtor(mock));
  When(Method(mock,generate)).Return(2);
  auto numberGenerator = std::unique_ptr<NumberGenerator>(&mock.get());

  Crossover crossover(std::move(numberGenerator));

  Genotype genotype1({0, 1, 2, 3, 4});
  Genotype genotype2({5, 6});

  ASSERT_EQ(Genotype({0, 1}), crossover.apply(genotype1, genotype2));
}