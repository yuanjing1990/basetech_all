//描述顺序表的查找
//#include <algorithm>
//#include <functional>
#include <vector>
#include <cstdlib>
#include "myutil.h"
int main(int argc,char** argv)
{
	using namespace std;
	vector<int> vec;
	for(int i = 0; i < 21; ++i)
		vec.push_back(i);
	cout << "search for:" << argv[1] << endl;
	int temp = atoi(argv[1]);
	//yq::print(vec);
	//使用查询一个等于特定的值的元素
	OUT_TICK_BEGIN;
	vector<int>::iterator it = yq::seq_search(vec,temp);
	if(it != vec.end())
		cout << *it << endl;
	else cout << "not found!" << endl;
	OUT_TICK_END;
	
	//使用查询一个满足特定函数的元素
	TICK_BEGIN;
	it = yq::seq_search(vec,bind2nd(greater<int>(),temp));
	if(it != vec.end())
		cout << *it << endl;
	else cout << "not found!" << endl;  
	TICK_END;
	
	//使用查询一个等于特定的值的元素
	TICK_BEGIN;
	bool b_find = yq::binary_search(vec,temp);
	if(b_find)
		cout << temp << endl;
	else cout << "not found!" << endl;
	TICK_END;
	
//	using namespace yq;
//	int _up_pos = (int)vec.size() - 1;
//	int _down_pos = 1;
//	TICK_BEGIN
//	_bitree<int>* tree = _bitree<int>::CreateTree(vec,_up_pos,_down_pos);
//	cout << *tree;
//	tree->InsertElem(21);
//	cout << *tree;
//	TICK_END
//	delete tree;
	return 0;
}