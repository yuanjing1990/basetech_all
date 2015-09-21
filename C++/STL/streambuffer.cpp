#include <iostream>
#include <fstream>
#include <algorithm>
	
class split_ifstream : public std::ifstream
{
	public:
		char* NextToken()
		{
			*this >> buf;
			return buf;
		};
	public:
		char buf[256];
};
int main(int argc,char* argv[])
{
	using namespace std;
	split_ifstream ss;
	ss.open("test.txt");
	while(!ss.eof())
		cout << ss.NextToken();
	//istreambuf_iterator<char>::istream_type& istrm = cin;
	//istreambuf_iterator<char>::streambuf_type* strmbf = cin.rdbuf();
	//cout << "replace ' ' with '-' :" << endl;
	//istreambuf_iterator<char> charReadIn(cin);
	//ostreambuf_iterator<char> charOut(cout);
	
	//replace_copy(charReadIn,istreambuf_iterator<char>(),charOut,' ','-');
}