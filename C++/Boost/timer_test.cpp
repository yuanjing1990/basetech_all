#include <boost/timer.hpp>
#include <boost/progress.hpp>
#include <iostream>
int main(int argc,char* argv[])
{
    //class timer
    boost::timer t;
    uint64_t i = 0;
    while(i<1000000000)
        i = i+1;
    std::cout << "timer::elapsed:" << t.elapsed() << std::endl;

    //class progress_timer
    {
        boost::progress_timer t_p;
        i = 0;
        while(i<1000000000)
            i = i+1;
        std::cout << "progress_timer::~progress_timer:";
    }

    //progress_display
    {
        boost::progress_display t_d(1000000000);
        i = 0;
        while(i<1000000000)
        {
            i = i+1;
            ++t_d;
        }
    }
    return 0;
}
