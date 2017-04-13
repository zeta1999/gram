#ifndef GRAM_LANGUAGE_RULE
#define GRAM_LANGUAGE_RULE

#include <gram/language/symbol/Option.h>

namespace gram {
/**
 * Class.
 */
class Rule {
 public:
  Rule(std::string name);
  std::string getName() const;
  void addOption(std::shared_ptr<gram::Option> option);
  Option& optionAt(unsigned long index) const;
  unsigned long size() const;
  bool operator==(const Rule& rule) const;
  bool operator!=(const Rule& rule) const;
 private:
  std::string name;
  std::vector<std::shared_ptr<Option>> options;
};
}

#endif // GRAM_LANGUAGE_RULE
