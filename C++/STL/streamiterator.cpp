#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <string>
using namespace std;
int main(int argc,char* argv[])
{
	set<int> st(istream_iterator<int>(cin),istream_iterator<int>());
	cin.clear();
	//copy(st.begin(),st.end(),ostream_iterator<int>(cout,"5"));	
	return 0;
}