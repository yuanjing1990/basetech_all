#ifndef MY_STACK_H_
#define MY_STACK_H_

#include <vector>
namespace yq {
template <typename T, typename CONT = std::vector<T>> class Stack {
  private:
    CONT elems;

  public:
    void push(T const &t);
    void pop();
    T top() const;
    bool empty() const { return elems.empty(); }
};
template <typename T, typename CONT> void Stack<T, CONT>::push(T const &t) {
    elems.push_back(t);
}
template <typename T, typename CONT> void Stack<T, CONT>::pop() {
    if (elems.empty())
        throw std::out_of_range("Stack<>::pop: Empty Stack.");
    elems.pop_back();
}
template <typename T, typename CONT> T Stack<T, CONT>::top() const {
    if (elems.empty())
        throw std::out_of_range("Stack<>::top: Empty Stack.");
    return elems.back();
}
} // namespace yq

#endif // MY_STACK_H_
