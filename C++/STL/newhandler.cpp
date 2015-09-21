#include <iostream>
#include <new>
using std::new_handler;
const int LENGTH = 1000000;
void noMoreMemory()
{
	std::cerr << "Unable to statisfy request for memory\n";
	abort();
}

template<class T>
class NewHandlerSupport
{
	public:
		static void* operator new(size_t size);
		static new_handler set_new_handler(new_handler p);
	private:
		static new_handler currentHandler;
};
template<class T>
new_handler NewHandlerSupport<T>::set_new_handler(new_handler p)
{
	new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}
template<class T>
void* NewHandlerSupport<T>::operator new(size_t size)
{
	new_handler globalHandler = std::set_new_handler(currentHandler);
	void* memory;
	try{
		memory = ::operator new(size);
	}catch(std::bad_alloc& e){
		std::set_new_handler(globalHandler);
		throw;
	}
	std::set_new_handler(globalHandler);
	return memory;
}
template<class T>
new_handler NewHandlerSupport<T>::currentHandler = 0;

class T_X : public NewHandlerSupport<T_X>
{
	public:
		int m_x;
};
class T_Y : public NewHandlerSupport<T_Y>
{
	public:
		int m_y;
};
int main(int argc,char* argv[])
{
	//std::set_new_handler(noMoreMemory);
	//int* p[LENGTH];
	//X::set_new_handler(noMoreMemory);
	T_X::set_new_handler(noMoreMemory);
	try{
		//T_X t_x;
		//X* x = new X();
		T_X* t_x = new T_X;
		//while(x = new int[4096]);
	}catch(std::bad_alloc &e)
	{
		std::cerr << e.what();
	}
	return 0;
}