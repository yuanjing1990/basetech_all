#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <iostream>
#include <QtCore/QThread>

class TestThread1 : public QThread {
  public:
    void run() {
        std::cout << "test thread:id=" << QThread::currentThreadId() << std::endl;
    }
};


#endif