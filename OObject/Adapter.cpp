//����˵����Adapterģʽ������ʵ�ַ�ʽ���̳к;ۺ�
//����˼�룺��һ��������Adaptee��������ӿں�Target���в�ͬ��
//			��������ֻ��ʹ��Target�Ľӿ������롣������Ҫһ��
//			Adapter�࣬����Ҫ�̳�Target�Ľӿڣ�����ʹ��Adaptee
//			��ʵ�֡����ڡ��̳�Target�Ľӿڡ�����ʹ�ü̳���ʵ�֣�
//			���ڡ�ʹ��Adaptee��ʵ�֡�����ͨ���ۺϺͼ̳���ʵ�֣�
//			��������Ӷ��������ַ����������֡�
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