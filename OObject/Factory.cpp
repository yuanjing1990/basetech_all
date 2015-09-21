#include <iostream>

class Product
{
public:
	Product(){};
	virtual ~Product(){};
};
class ConProduct1 : public Product
{
public:
	ConProduct1(){std::cout << "ConProduct1 Created!\n";};
	virtual ~ConProduct1(){};
};
class ConProduct2 : public Product
{
public:
	ConProduct2(){std::cout << "ConProduct2 Created!\n";};
	virtual ~ConProduct2(){};
};

class Creator
{
public:
	virtual ~Creator(){};
	virtual Product* GetProduct() = 0;
};
class ConCreator1 : public Creator
{
public:
	~ConCreator1(){};
	Product* GetProduct(){
		try{
			return new ConProduct1();
		}catch(std::bad_alloc& e){
		}
		return 0;
	}
};
class ConCreator2 : public Creator
{
public:
	~ConCreator2(){};
	Product* GetProduct(){
		try{
			return new ConProduct2();
		}catch(std::bad_alloc& e){
		}
		return 0;
	}
};
int main(int argc,char* argv[])
{
	Creator* c1 = new ConCreator1();
	c1->GetProduct();
	Creator* c2 = new ConCreator2();
	c2->GetProduct();
	return 0;
}