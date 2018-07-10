/*************************************************************************
	> File Name: iostream_test.cpp
	> Author: yuanjing
	> Mail: 0yuanjing0@gmail.com
	> Created Time: 2015年10月23日  9:13:11
 ************************************************************************/

#include<iostream>
#include<vector>
#include<boost/iostreams/stream.hpp>
#include<boost/iostreams/device/file.hpp>
#include<boost/iostreams/device/array.hpp>
#include<boost/iostreams/device/back_inserter.hpp>
#include<boost/iostreams/filtering_stream.hpp>
using namespace boost::iostreams;
int main(int argc,char* argv[])
{
    //-------------------------------------------
    // test file_sink and file_source
    std::cout << "file device test............\n";
    stream<file_sink> out("iostream_test.txt");
    out << "This is a test!\n";
    out.flush();
    stream<file_source> in("iostream_test.txt");
    std::string tmp;
    std::getline(in,tmp);
    std::cout << tmp;
    std::cout << std::endl;
    //-------------------------------------------

    //-------------------------------------------
    // test array_sink and array_source
    std::cout << "array device test............\n";
    char tmp1[255] = {0};
    stream<array_sink> array_out(array_sink(tmp1,tmp1+tmp.length()));
    array_out << tmp;
    std::cout << tmp1;
    std::cout << std::endl;
    stream<array_source> array_in(array_source(tmp1,tmp1+tmp.length()));
    std::string tmp2;
    //array_in >> tmp2;
    while(array_in >> tmp2)
        std::cout << tmp2 << std::endl;
    //-------------------------------------------

    //-------------------------------------------
    std::cout << "back insert device test..........\n";
    std::vector<int> vec;
    //vec.resize(3);
    stream<back_insert_device<std::vector<int> > > back_inserter_out(vec);
    //stream<back_insert_device<std::string > > back_inserter_out(boost::iostreams::back_inserter(tmp2));
    int input[3] = {1,2,3};
    back_inserter_out.write(input,3);
    //Need flush,if not the vec will have no elem
    back_inserter_out.flush();
    std::cout << vec[0] << "," << vec[1] << "," << vec[2] << "\n" << vec.size() << std::endl;
    //std::cout << "tmp2=" << tmp2 << std::endl;
    //-------------------------------------------

    filtering_istream fs;
    fs.push(file_source("test.txt"));
    fs >> tmp;
    std::cout << tmp << std::endl;
    return 0;
}
