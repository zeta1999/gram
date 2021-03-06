#ifndef GRAM_EVOLUTION
#define GRAM_EVOLUTION

#include <functional>
#include <memory>

#include "gram/evaluation/driver/EvaluationDriver.h"
#include "gram/population/Population.h"
#include "gram/util/logger/Logger.h"

namespace gram {
/**
 * Class.
 */
class Evolution {
public:
  Evolution(std::unique_ptr<EvaluationDriver> evaluationDriver, std::unique_ptr<Logger> logger);
  Population run(Population population, std::function<bool(Population&)> terminatingCondition) const;

private:
  std::unique_ptr<EvaluationDriver> evaluationDriver;
  std::unique_ptr<Logger> logger;
};
}

#endif
