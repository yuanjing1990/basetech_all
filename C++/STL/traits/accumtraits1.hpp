#ifndef ACCUMTRAITS_HPP
#define ACCUMTRAITS_HPP

template<typename T>
class AccumulationTraits;

template<>
class AccumulationTraits<char>{
	public:
		typedef int Acct;
		static Acct const zero = 0;
};
template<>
class AccumulationTraits<short>{
	public:
		typedef int Acct;
		static Acct const zero = 0;
};
template<>
class AccumulationTraits<int>{
	public:
		typedef long Acct;
		static Acct const zero = 0;
};
template<>
class AccumulationTraits<unsigned int>{
	public:
		typedef unsigned long Acct;
		static Acct const zero = 0;
};
template<>
class AccumulationTraits<float>{
	public:
		typedef double Acct;
		//ֻ�������κ�ö�ٵľ�̬��Ա�ڶ���ʱ��ʼ��
		static Acct zero(){
			return 0.0;
		}
};
#endif
