#ifndef MYUTIL_H
#define MYUTIL_H
#include <ctime>
#include <iostream>
#define CLOCK_START                                                            \
    {                                                                          \
        clock_t t_s = clock();
#define CLOCK_END                                                              \
    std::cout << "RunTime:" << (double)(clock() - t_s) / CLOCKS_PER_SEC << "s" \
              << std::endl;                                                    \
    }

#endif