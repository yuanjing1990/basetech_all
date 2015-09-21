#include <iostream>
#define H_W 3.14 //Test
template<class T>
inline T& max(T& a,T& b)
{
	return a > b ? a : b;
}
class Test
{
	public:
		static const char* const count;
	private:
		enum {MAX_COUNT = 5};
	public:
		int m_mem[MAX_COUNT];
	public:
		void print(){
			for(int i = 0; i < MAX_COUNT; ++i)
				std::cout << m_mem[i] << "\t";
			std::cout << count;
			std::cout << std::endl;
		}
};
const char* const Test::count = "count";
int main(int argc,char* argv[])
{
	char a,b;
	std::cin >> a >> b;
	std::cout << "Max:" << max(a,b) << std::endl;
	Test t;
	t.print();
	std::cout << t.count << std::endl;
	std::cout << H_W << std::endl;
	return 0;
}