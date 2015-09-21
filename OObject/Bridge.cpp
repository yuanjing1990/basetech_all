#include <iostream>

class Implement
{
public:
	virtual void Operator() = 0;
};

class Abstract
{
public:
	virtual void Operator() = 0;
private:
	Implement* m_imp;
};

class ConImplement : public Implement
{
public:
	void Operator(){
		std::cout << "ConImplement Operator!\n";
	}
};


int main(int argc,char* argv[])
{
}