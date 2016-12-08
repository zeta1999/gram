#ifndef GRAM_POPULATION_INITIALIZER
#define GRAM_POPULATION_INITIALIZER

#include <gram/population/Population.h>
#include <gram/util/NumberGenerator.h>

namespace gram {
namespace population {
/**
 * Class.
 */
class Initializer {
 public:
  Initializer(gram::util::NumberGenerator &generator, int individualSize);
  virtual Population initialize(int individualCount);
 private:
  gram::util::NumberGenerator &generator;
  int individualSize;
};
}
}

#endif // GRAM_POPULATION_INITIALIZER