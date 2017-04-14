#include <catch.hpp>
#include <fakeit.hpp>

#include <gram/evaluation/driver/SingleThreadDriver.h>
#include <gram/individual/crossover/OnePointCrossover.h>
#include <gram/individual/mutation/FastCodonMutation.h>
#include <gram/language/parser/BnfRuleParser.h>
#include <gram/language/mapper/ContextFreeMapper.h>
#include <gram/population/initializer/RandomInitializer.h>
#include <gram/population/selector/TournamentSelector.h>
#include <gram/util/logger/NullLogger.h>
#include <gram/util/number_generator/TwisterNumberGenerator.h>
#include <gram/Evolution.h>
#include <gram/util/number_generator/XorShiftNumberGenerator.h>

using namespace fakeit;
using namespace gram;
using namespace std;

class FakeEvaluator : public Evaluator {
 public:
  FakeEvaluator(shared_ptr<ContextFreeMapper> mapper, string desired) : mapper(mapper), desired(desired) {}

  double evaluate(Individual& individual) {
    string program = individual.serialize(*mapper.get());

    return static_cast<double>(edit_distance(program, desired));
  }

 private:
  shared_ptr<ContextFreeMapper> mapper;
  string desired;

  unsigned long edit_distance(const string& s1, const string& s2) const {
    const unsigned long len1 = s1.size(), len2 = s2.size();
    vector<vector<unsigned long>> d(len1 + 1, vector<unsigned long>(len2 + 1));

    d[0][0] = 0;

    for (unsigned int i = 1; i <= len1; ++i) {
      d[i][0] = i;
    }

    for (unsigned int i = 1; i <= len2; ++i) {
      d[0][i] = i;
    }

    for (unsigned int i = 1; i <= len1; ++i) {
      for (unsigned int j = 1; j <= len2; ++j) {
        d[i][j] = min({d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1)});
      }
    }

    return d[len1][len2];
  }
};

TEST_CASE("evolution_test") {
  auto numberGenerator1 = make_unique<XorShiftNumberGenerator>();
  auto numberGenerator2 = make_unique<XorShiftNumberGenerator>();
  auto numberGenerator3 = make_unique<XorShiftNumberGenerator>();
  auto numberGenerator4 = make_unique<XorShiftNumberGenerator>();
  auto numberGenerator5 = make_unique<XorShiftNumberGenerator>();
  auto stepGenerator = make_unique<BernoulliDistributionStepGenerator>(0.1, move(numberGenerator5));

  auto selector = make_unique<TournamentSelector>(20, move(numberGenerator1));
  auto mutation = make_unique<FastCodonMutation>(move(stepGenerator), move(numberGenerator2));
  auto crossover = make_unique<OnePointCrossover>(move(numberGenerator3));
  auto reproducer = make_shared<Reproducer>(move(selector), move(crossover), move(mutation));

  string grammarString =
      "<number> ::= <number> <digit> | <digit>\n"
          "<digit> ::= \"0\" | \"1\" | \"2\" | \"3\" | \"4\" | \"5\" | \"6\" | \"7\" | \"8\" | \"9\"";

  BnfRuleParser parser;

  auto grammar = make_shared<ContextFreeGrammar>(parser.parse(grammarString));
  auto mapper = make_shared<ContextFreeMapper>(grammar, 1);

  RandomInitializer initializer(move(numberGenerator4), 16);

  auto evaluator = make_unique<FakeEvaluator>(mapper, "1234");
  auto evaluationDriver = make_unique<SingleThreadDriver>(move(evaluator));
  auto logger = make_unique<NullLogger>();

  Evolution evolution(move(evaluationDriver), move(logger));

  Population population = initializer.initialize(1000, reproducer);

  Individual result = evolution.run(population);

  REQUIRE(result.getFitness() == 0.0);
  REQUIRE(result.serialize(*mapper) == "1234");
}
