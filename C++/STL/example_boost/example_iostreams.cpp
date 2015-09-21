#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <iostream>
#include <string>
namespace io = boost::iostreams;
class my_source : public io::source
{
public:
	my_source(std::string str):m_str(str),m_off(0){};
	~my_source(){};
public:
	std::streamsize read(char_type* s,std::streamsize n)
	{
		using namespace std;
		streamsize result = min(n,static_cast<streamsize>(m_str.size())-m_off);
		if(result != 0)
		{
			copy(m_str.begin()+m_off,m_str.begin()+m_off+result,s);
			m_off += result;
			return result;
		}
		else
		{
			return -1;
		}
	}
	std::string& str(){return m_str;};
private:
	std::string 	m_str;
	std::streamsize m_off;
};
class my_sink : public io::sink
{
public:
	my_sink(std::string& str):m_str(str),m_off(0){};
	~my_sink(){};
public:
	std::streamsize write(const char_type* s,std::streamsize n)
	{
		m_str.append(s,s+n);
		return n;
	}
	std::string& str(){return m_str;};
private:
	std::string& 	m_str;
	std::streamsize m_off;
};
int main(int argc,char* argv[])
{
	//source
	std::string str;
	io::stream<my_source> sb("Hello World");
	char buffer[256] = {0};
	sb >> buffer;
	std::cout << buffer << std::endl;
	
	//sink
	io::stream<my_sink> ss(str);
	ss << "Check";
	ss << buffer;
	ss.flush();
	std::cout << str << std::endl;
	
	//Filtering
	io::filtering_ostream fo;
	fo.push(my_sink(str));
	fo << "Filtering";
	fo.flush();
	std::cout << str << std::endl;
	return 0;
}