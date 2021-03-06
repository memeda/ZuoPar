#ifndef __ZUOPAR_APP_DEPPARSER_ARCSTANDARD_STATE_H__
#define __ZUOPAR_APP_DEPPARSER_ARCSTANDARD_STATE_H__

#include "types/common.h"
#include "types/dependency.h"
#include "app/settings.h"
#include "app/depparser/arcstandard/action.h"

namespace ZuoPar {
namespace DependencyParser {
namespace ArcStandard {

class State {
public:
  //! The empty constructor.
  State();

  /**
   * The constructor for the State.
   *
   *  @param[in]  r   The pointer to the dependency state.
   */
  State(const CoNLLXDependency* r);

  /**
   * This method is needed by @class TransitionSystem.
   *
   *  @param[in]  source  The source of state to copy from.
   */
  void copy(const State& source);

  //! Clear the state.
  void clear();

  /**
   * Perform the shift action from source state.
   *
   *  @param[in]  source  The source state.
   */
  bool shift(const State& source);

  /**
   * Perform the left arc action from source state onto current state.
   *
   *  @param[in]  source  The source state.
   *  @param[in]  deprel  The dependency relation.
   */
  bool left_arc(const State& source, deprel_t deprel);

  /**
   * Perform the right arc action from source state onto current state.
   *
   *  @param[in]  source  The source state.
   *  @param[in]  deprel  The dependency relation.
   */
  bool right_arc(const State& source, deprel_t deprel);

  //! Used in dynamic oracle, should only be performed on gold state.
  int cost(const std::vector<int>& heads, const std::vector<int>& deprels);

  //! Return true on the buffer is empty.
  bool buffer_empty() const;

  //! Get the size of the stack.
  size_t stack_size() const;

  bool is_complete() const;           //! shorthand for stack.size() == 1 &&
  
  //! The pointer to the previous state.
  std::vector<int> stack;

  //! The front word in the buffer.
  int buffer;

  //! The pointer to the previous state.
  const State* previous;

  //! The pointer to the dependency tree.
  const CoNLLXDependency* ref;

  //! The score.
  floatval_t score;

  //! The last action.
  Action last_action;

  //! The top word on the stack.
  int top0;

  //! The second top word on the stack.
  int top1;

  //! Use to record the heads in current state.
  int heads[kMaxNumberOfWords];

  //! The dependency relation cached in state.
  deprel_t deprels[kMaxNumberOfWords];

  //!
  int left_label_set[kMaxNumberOfWords];

  //!
  int right_label_set[kMaxNumberOfWords];

  //! Use to record the number of left children in current state.
  int nr_left_children[kMaxNumberOfWords];

  //! Use to record the number of right children in current state.
  int nr_right_children[kMaxNumberOfWords];

  //! Use to record the left most child for each word in current state.
  int left_most_child[kMaxNumberOfWords];

  //! Use to record the right most child for each word in current state.
  int right_most_child[kMaxNumberOfWords];

  //! Use to record the left 2nd-most child for each word in current state.
  int left_2nd_most_child[kMaxNumberOfWords];

  //! Use to record the right 2nd-most child for each word in current state.
  int right_2nd_most_child[kMaxNumberOfWords];

private:
  void refresh_stack_information();   //! Refresh the value of top0 and top1.
  bool can_shift() const;             //! Return can perform shift action.
  bool can_left_arc() const;          //! Return can perform left arc action.
  bool can_right_arc() const;         //! Return can perform right arc action.
};

} //  end for namespace arcstandard
} //  end for namespace dependencyparser
} //  end for namespace zuopar
#endif  //  end for __ZUOPAR_APP_DEPPARSER_ARCSTANDARD_STATE_H__
