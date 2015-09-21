//trait是指某一类型数据的特有属性（“类型特有”决定了trait是一些类型信息和静态成员或方法
#include <iostream>
using namespace std;

//下面定义的trait用来提取特定类型上定义的操作信息
template <typename T>
class trait
{
	public:
		typedef enum{ADD=0,SUB=0,MUL=0,DIV=0} OP;
};

//模版参数为int的特化实例
template <>
class trait<int>
{
	public:
		typedef enum{ADD=1,SUB=1,MUL=1,DIV=0} OP;
};

//模版参数为float的特化实例
template <>
class trait<float>
{
	public:
		typedef enum{ADD=1,SUB=0,MUL=0,DIV=0} OP;
};

//定义模版，以第一个模版参数为trait的参数来作为第二个模版参数
template <typename T,typename TT=trait<T> >
class JudgeOp
{
	public:
		void GetOpInfo(){
			cout << "============================" << endl;
			if(TT::ADD) cout << "Add Defined" << endl;
			else cout << "Add Not Defined" << endl;
			if(TT::SUB) cout << "Sub Defined" << endl;
			else cout << "Sub Not Defined" << endl;
			if(TT::MUL) cout << "Mul Defined" << endl;
			else cout << "Mul Not Defined" << endl;
			if(TT::DIV) cout << "Div Defined" << endl;
			else cout << "Div Not Defined" << endl;
			cout << "============================" << endl;
		}
};

int main(int argc,char* argv[])
{
	JudgeOp<int> tmp1;
	tmp1.GetOpInfo();
	JudgeOp<float> tmp2;
	tmp2.GetOpInfo();
	JudgeOp<short> tmp3;
	tmp3.GetOpInfo();
	return 0;
}