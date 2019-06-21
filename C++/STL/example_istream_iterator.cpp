#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    using namespace std;

    // Used in conjunction with copy algorithm
    // to put elements into a vector read from cin
    vector<int> vec;
    vec.resize(4);
    vector<int>::iterator Iter;

    cout << "Enter 4 integers separated by spaces & then\n"
         << " a character ( try example: '2 4 6 8 a' ): ";
    istream_iterator<int> intvecRead(cin);

    // Default constructor will test equal to end of stream
    // for delimiting source range of vecor
    copy(intvecRead, istream_iterator<int>(), vec.begin());
    cin.clear();

    cout << "vec = ";
    copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;
}
