#include<iostream>
using namespace std;
class Point
{
public:
	Point(float xval):_x(xval){++_point_count;};
	virtual ~Point(){--_point_count;};
	float x() const{return _x;};
	static int PointCount(){return _point_count;};
protected:
	virtual ostream& print(ostream& os) const
	{
		os << _x;
	};
	float _x;
	static int _point_count;
};

class Foo
{
public:
	int m_a;
	double m_b;
	char m_c;
	virtual void print(){
		cout << "m_a:" << m_a << endl;
		cout << "m_b:" << m_b << endl;
		cout << "m_c:" << m_c << endl;
	}
};
class Bar : public Foo
{
public:
	virtual void print()
	{
		Foo::print();
	}
	virtual void implement(){
		cout << "implement";
	}
};
int main(int argc,char* argv[])
{
	Foo f;
	Bar b;
	cout << sizeof(b) << endl;
	cout << sizeof(f) << endl;
//	cout << "f.m_a:" << f.m_a << endl;
//	cout << "f.m_b:" << f.m_b << endl;
//	cout << "f.m_c:" << f.m_c << endl;
}