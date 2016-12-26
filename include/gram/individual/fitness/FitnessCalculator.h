#ifndef GRAM_INDIVIDUAL_FITNESS_CALCULATOR
#define GRAM_INDIVIDUAL_FITNESS_CALCULATOR

namespace gram {
/**
 * Interface.
 */
class FitnessCalculator {
 public:
  virtual ~FitnessCalculator() = default;
  virtual double calculate(int desired, int actual) const = 0;
};
}

#endif // GRAM_INDIVIDUAL_FITNESS_CALCULATOR
