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

class TestThread2 : public QObject {
    Q_OBJECT
  public:
    explicit TestThread2(QObject *parent = 0) : QObject(parent) {}
    ~TestThread2() {}

  public slots:
    void thread_run() {
        std::cout << "test thread:id=" << QThread::currentThreadId()
                  << std::endl;
        QThread::currentThread()->exit();
    }
};
#endif