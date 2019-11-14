#include <iostream>
#include "threadpool.h"
#include "unistd.h"


void fun()
{
    std::cout << "fun" << std::endl;
    return;
}

int main()
{
    ThreadPool threadPool(4);
    sleep(5);
    for(int i = 0; i < 20; i ++)
    threadPool.enqueue([=]{std::cout << "Task" << i <<  std::endl;});

    return 0;
}
