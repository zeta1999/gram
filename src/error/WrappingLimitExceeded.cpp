#include <gram/error/WrappingLimitExceeded.h>

using namespace gram;
using namespace std;

WrappingLimitExceeded::WrappingLimitExceeded(unsigned long limit)
    : out_of_range("Gram error: Wrapping limit of " + to_string(limit) + " exceeded.") {
  //
}
