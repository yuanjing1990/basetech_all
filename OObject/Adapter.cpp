//下面说明了Adapter模式的两种实现方式：继承和聚合
//基本思想：有一个可用类Adaptee，但是其接口和Target稍有不同，
//			我们现在只想使用Target的接口来编码。所以需要一个
//			Adapter类，它需要继承Target的接口，并且使用Adaptee
//			的实现。对于“继承Target的接口”可以使用继承来实现，
//			对于“使用Adaptee的实现”可以通过聚合和继承来实现，
//			下面的例子对于这两种方法均有体现。
#include <iostream>
class Adaptee
{
public:
	void Operator(){
		std::cout << "This is Adaptee's Method!\n";
	};
};
class Target
{
public:
	virtual void SpecialOperator() = 0;
};
class Adapter : public Target
{
public:
	Adapter(Adaptee* ade):m_ade(ade){};
	virtual void SpecialOperator(){
		std::cout << "SpecialOp:" ;
		m_ade->Operator();
	}
private:
	Adaptee* m_ade;
};
class Adapter1 : public Target,public Adaptee
{
public:
	virtual void SpecialOperator(){
		std::cout << "Adapter1's SpecialOp:";
		Adaptee::Operator();
	}
};
int main(int argc,char* argv[])
{
	Target* t = new Adapter(new Adaptee());
	t->SpecialOperator();
	delete t;
	t = new Adapter1();
	t->SpecialOperator();
}