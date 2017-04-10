#ifndef GRAM_LANGUAGE_CONTEXT_FREE_GRAMMAR
#define GRAM_LANGUAGE_CONTEXT_FREE_GRAMMAR

#include <memory>

#include <gram/language/symbol/Option.h>

namespace gram {
/**
 * Class.
 */
class ContextFreeGrammar {
 public:
  ContextFreeGrammar();
  void addRule(std::string name, std::shared_ptr<NonTerminal> rule);
  std::shared_ptr<NonTerminal> ruleNamed(std::string name);
  std::shared_ptr<NonTerminal> startRule() const;
 private:
  std::shared_ptr<NonTerminal> start;
  std::unordered_map<std::string, std::shared_ptr<NonTerminal>> rules;
};
}

#endif // GRAM_LANGUAGE_CONTEXT_FREE_GRAMMAR