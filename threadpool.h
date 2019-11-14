#ifndef __THREAD_POOL_H
#define __THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    ThreadPool(int threadnum)
    : stop(false)
    {
        for(int i = 0; i < threadnum; i++)
        {
            workers.emplace_back(
			    [this]
			    {
                    while(1)
                    {
                        std::function<void()> task; //声明一个函数指针
                        {
							std::unique_lock<std::mutex> lock(queue_mutex);
                            condition.wait(lock, [this]{return stop || !tasks.empty();});
                            if(tasks.empty() && stop)
                            return;
                            task = std::move(tasks.front());
                            tasks.pop();
                        }
                        task();
                    }
                }
            );
        }
    }
	void enqueue(std::function<void()> task)
	{
		{
	        std::unique_lock<std::mutex> lock(queue_mutex);
			tasks.emplace(task);
		}
		condition.notify_one();
	}
    ~ThreadPool()
    {
		{
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
		condition.notify_all();
		for(std::thread &worker: workers)
		worker.join();
    }
private:
    bool stop;
	std::mutex queue_mutex;
	std::condition_variable condition;
    std::vector< std::thread > workers;
    std::queue< std::function<void()> > tasks;

};

#endif

