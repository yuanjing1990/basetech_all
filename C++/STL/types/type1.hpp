#ifndef TYPE1_HPP
#define TYPE1_HPP
template <typename T>
class IsFundaT{
	public:
		enum{Yes = 0,No = 1};
};

#define MK_FUNDA_TYPE(T)			\
	template<> class IsFundaT<T>{	\
		public:						\
			enum{Yes = 1, No = 0};	\
	};

MK_FUNDA_TYPE(void)
MK_FUNDA_TYPE(bool)
MK_FUNDA_TYPE(signed char)
MK_FUNDA_TYPE(unsigned char)
MK_FUNDA_TYPE(wchar_t)

MK_FUNDA_TYPE(signed short)
MK_FUNDA_TYPE(unsigned short)
MK_FUNDA_TYPE(signed int)
MK_FUNDA_TYPE(unsigned int)
MK_FUNDA_TYPE(signed long)
MK_FUNDA_TYPE(unsigned long)

#if LONGLONG_EXISTS
	MK_FUNDA_TYPE(signed long long)
	MK_FUNDA_TYPE(unsigned long long)
#endif //LONGLONG_EXISTS

MK_FUNDA_TYPE(float)
MK_FUNDA_TYPE(double)
MK_FUNDA_TYPE(long double)

#undef MK_FUNDA_TYPE

#endif //TYPE1_HPP
