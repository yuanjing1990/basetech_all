#include <iostream>

#include "MyDownloader.h"
#include "MyXml.h"
#include "TestThread.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    std::cout << "1.1 ============>Begin" << std::endl;
    int a = 3, b = 5;
    std::cout << "a = " << a << ", b=" << b << std::endl;
    a = a + b;
    b = a - b;
    a = a - b;
    std::cout << "a = " << a << ", b=" << b << std::endl;
    std::cout << "1.1 ============<End" << std::endl;

    std::cout << "1.3 第一种创建线程方法============>Begin" << std::endl;
    {
        TestThread1 thread;
        thread.start();
        thread.wait();
        std::cout << "finish thread:id=" << QThread::currentThreadId() << std::endl;
    }
    std::cout << "1.3 第一种创建线程方法============<End" << std::endl;

    std::cout << "1.3 第二种创建线程方法============>Begin" << std::endl;
    {
        TestThread2 thread;
        QThread tmp;
        QObject::connect(&tmp, SIGNAL(started()), &thread, SLOT(thread_run()));
        thread.moveToThread(&tmp);
        tmp.start();
        tmp.wait();
        std::cout << "finish thread:id=" << QThread::currentThreadId() << std::endl;
    }
    std::cout << "1.3 第二种创建线程方法============<End" << std::endl;

    std::cout << "1.5 下载文件============>Begin" << std::endl;
    MyDownloader m_downLoder;
    {
        m_downLoder.setData(
            QUrl("http://yantu.qiniu.tms.y-link.cn/plt_update_yldz_v1.zip"),
            "./download.zip");
        // m_downLoder.cancel();
        m_downLoder.getFile();
        std::cout << "Downloading ...";
        // while (!m_downLoder.isFinished()) {
        //     std::cout << ".";
        //     std::cout.flush();
        //     QThread::sleep(1);
        // }
        std::cout << std::endl;
    }
    std::cout << "1.5 下载文件============<End" << std::endl;

    std::cout << "2.1 读写xml============>Begin" << std::endl;
    {
        std::cout << "写入到文件：test.xml============>Begin" << std::endl;
        WriteXml();
        std::cout << "写入到文件：test.xml============>End" << std::endl;

        std::cout << "从文件：test.xml读取============>Begin" << std::endl;
        ReadXml();
        std::cout << "从文件：test.xml读取============>Begin" << std::endl;
    }
    std::cout << "2.1 读写xml============<End" << std::endl;

    return app.exec();
}