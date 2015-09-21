#ifndef NAMEDTMP1_HPP
#define NAMEDTMP1_HPP
#include <iostream>
class DefaultPolicy1{
	public:
		static void print(){std::cout << "This is DefaultPolicy1!\n";}
};
class DefaultPolicy2{
	public:
		static void print(){std::cout << "This is DefaultPolicy2!\n";}
};
class DefaultPolicy3{
	public:
		static void print(){std::cout << "This is DefaultPolicy3!\n";}
};
class DefaultPolicy4{
	public:
		static void print(){std::cout << "This is DefaultPolicy4!\n";}
};
class CustomPolicy1{
	public:
		static void print(){std::cout << "This is CustomPolicy1!\n";}
};
class CustomPolicy2{
	public:
		static void print(){std::cout << "This is CustomPolicy2!\n";}
};

template <typename Base, int D>
class Discriminator : public Base{
};
template <typename Setter1,typename Setter2,typename Setter3,typename Setter4>
class PolicySelector : public Discriminator<Setter1,1>,
					   public Discriminator<Setter2,2>,
					   public Discriminator<Setter3,3>,
					   public Discriminator<Setter4,4>{
};
class DefaultPolicies{
	public:
		typedef DefaultPolicy1 P1;
		typedef DefaultPolicy2 P2;
		typedef DefaultPolicy3 P3;
		typedef DefaultPolicy4 P4;
};
class DefaultPolicyArgs : virtual public DefaultPolicies{
};
template <typename Policy>
class Policy1_is : virtual public DefaultPolicies{
	public:
		typedef Policy P1;
};
template <typename Policy>
class Policy2_is : virtual public DefaultPolicies{
	public:
		typedef Policy P2;
};
template <typename Policy>
class Policy3_is : virtual public DefaultPolicies{
	public:
		typedef Policy P3;
};
template <typename Policy>
class Policy4_is : virtual public DefaultPolicies{
	public:
		typedef Policy P4;
};

template <typename PolicySetter1 = DefaultPolicyArgs,
	typename PolicySetter2 = DefaultPolicyArgs,
	typename PolicySetter3 = DefaultPolicyArgs,
	typename PolicySetter4 = DefaultPolicyArgs>
class BreadSlicer
{
	typedef PolicySelector<PolicySetter1,PolicySetter2,
						   PolicySetter3,PolicySetter4> Policies;
	public:
		void print(){
			Policies::P1::print();
			Policies::P2::print();
			Policies::P3::print();
			Policies::P4::print();
		}
};

#endif