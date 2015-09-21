#include <iostream>
	
class Product
{
};
class Product11 : public Product
{
	public:
		Product11(){std::cout << "Create Product11!\n";};
};
class Product12 : public Product
{
	public:
		Product12(){std::cout << "Create Product12!\n";};
};
class Product21 : public Product
{
	public:
		Product21(){std::cout << "Create Product21!\n";};
};
class Product22 : public Product
{
	public:
		Product22(){std::cout << "Create Product22!\n";};
};
class AbFactory
{
	public:
		virtual Product* GetProduct1() = 0;
		virtual Product* GetProduct2() = 0;
};
class Factory1 : public AbFactory
{
	public:
		Product* GetProduct1()
		{
			try{
				return new Product11();
			}catch(std::bad_alloc& e){
			}
			return 0;
		}
		Product* GetProduct2()
		{
			try{
				return new Product12();
			}catch(std::bad_alloc& e){
			}
			return 0;
		}
};
class Factory2 : public AbFactory
{
	public:
		Product* GetProduct1()
		{
			try{
				return new Product21();
			}catch(std::bad_alloc& e){
			}
			return 0;
		}
		Product* GetProduct2()
		{
			try{
				return new Product22();
			}catch(std::bad_alloc& e){
			}
			return 0;
		}
};
int main(int argc,char* argv[])
{
	AbFactory* af = new Factory1();
	delete af->GetProduct1();
	delete af->GetProduct2();
	delete af;
	af = new Factory2();
	delete af->GetProduct1();
	delete af->GetProduct2();
	delete af;
	return 0;
}