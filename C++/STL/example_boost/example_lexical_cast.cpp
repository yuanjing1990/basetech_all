//Define:
//namespace boost
//{
//    class bad_lexical_cast;
//    template<typename Target, typename Source>
//      Target lexical_cast(const Source& arg);
//}

//Requirment:
//Source is OutputStreamable, meaning that an operator<< is defined that takes a std::ostream or std::wostream object on the left hand side and an instance of the argument type on the right. 
//Target is InputStreamable, meaning that an operator>> is defined that takes a std::istream or std::wistream object on the left hand side and an instance of the result type on the right. 
//Target is CopyConstructible [20.1.3]. 
//Target is DefaultConstructible, meaning that it is possible to default-initialize an object of that type [8.5, 20.1.4]. 

#include <boost/lexical_cast.hpp>
#include <stdio.h>
int main(int argc,char* argv[])
{
	int i = 0;
	try{
		i = boost::lexical_cast<int>('3');
	}catch(boost::bad_lexical_cast& bc){
		printf(bc.what());
	}
	printf("i = %d",i);
	return 0;
}