#include "myutil.h"
#include <ctime>
#include <iostream>
class A {
  private:
    int m_a;

  public:
    static void *operator new(size_t size) {
        if (size != sizeof(A))
            return ::operator new(size);
        A *p = headofFreeList;
        if (p)
            headofFreeList = p->next;
        else {
            A *t = static_cast<A *>(::operator new(BLOCK_SIZE * sizeof(A)));
            for (int i = 1; i < BLOCK_SIZE - 1; ++i)
                t[i].next = &t[i + 1];
            t[BLOCK_SIZE - 1].next = 0;
            p = t;
            headofFreeList = &t[1];
        }
        return p;
    }
    static void operator delete(void *deadObject, size_t size) {
        if (deadObject == NULL)
            return;
        if (size != sizeof(A)) {
            ::operator delete(deadObject);
            return;
        }
        A *t = static_cast<A *>(deadObject);
        t->next = headofFreeList;
        headofFreeList = t;
    }

  private:
    union {
        A *rep;
        A *next;
    };
    static const int BLOCK_SIZE;
    static A *headofFreeList;
};
const int A::BLOCK_SIZE = 100;
A *A::headofFreeList;
int main(int argc, char *argv[]) {
    CLOCK_START
    for (int i = 0; i < 1000000; i++) {
        A *a = new A;
        delete a;
    }
    CLOCK_END

    CLOCK_START
    for (int i = 0; i < 1000000; i++) {
        A *a = static_cast<A *>(::operator new(sizeof(A)));
        delete a;
    }
    CLOCK_END
}