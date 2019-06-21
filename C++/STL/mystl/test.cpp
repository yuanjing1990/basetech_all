#include "bitree.h"
#include "nested.h"
#include "stack.h"
using namespace yq;
int main(int argc, char *argv[]) {
    // 1 bitree.h
    // yq::BiTree<int> bt;
    // int a[10] = {1,3,8,5,4,2,6,9,7,10};
    // bt.CreateBiTree(a,10);
    // bt.PrintTree();

    // 2 stack.h
    // try{
    // 	Stack<int> s;
    // 	s.push(10);
    // 	std::cout << s.top() << std::endl;
    // 	s.pop();
    // 	s.pop();
    // 	std::cout << "After Exception!" << std::endl;
    // }catch(std::out_of_range e)
    // {
    // 	std::cerr << e.what() << std::endl;
    // }

    // 3 nested.h
    Nest<std::vector<int>> n;
    std::bitset<5> bs;
    bs.set(4);
    PrintBitset(bs);
}