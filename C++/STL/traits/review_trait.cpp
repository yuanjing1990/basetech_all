//trait��ָĳһ�������ݵ��������ԣ����������С�������trait��һЩ������Ϣ�;�̬��Ա�򷽷�
#include <iostream>
using namespace std;

//���涨���trait������ȡ�ض������϶���Ĳ�����Ϣ
template <typename T>
class trait
{
	public:
		typedef enum{ADD=0,SUB=0,MUL=0,DIV=0} OP;
};

//ģ�����Ϊint���ػ�ʵ��
template <>
class trait<int>
{
	public:
		typedef enum{ADD=1,SUB=1,MUL=1,DIV=0} OP;
};

//ģ�����Ϊfloat���ػ�ʵ��
template <>
class trait<float>
{
	public:
		typedef enum{ADD=1,SUB=0,MUL=0,DIV=0} OP;
};

//����ģ�棬�Ե�һ��ģ�����Ϊtrait�Ĳ�������Ϊ�ڶ���ģ�����
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