# ThreadPool
 
# 11.14
仿照网上线程池  
补充设计思路：在线程池ThreadPool的构造函数中，创建目标数量线程，**虽然在构造函数中出现While(1),但是这不是在构造函数中的while(1)，这个死循环是在写入线程中的，通过lambda函数表示线程函数。**  
**在其lanmbda函数中的等待任务队列不为空，即此时有任务加入时，任务会触发notify_one()，那么wait()将从阻塞变成不阻塞，然后程序向下执行任务。**  
# 11.15  
补充编码思路：  
  1.需要如下关键的变量  
    **1.1 互斥锁  
      1.2 条件变量  
      1.3 存放线程的vector  
      1.4 存放任务的queue(必须是具有双向迭代器的数据结构)**    
  2. 程序开始，通过输入的数字决定线程池的大小，每个线程中需要一个死循环来不停的判断任务queue是否为空，若不为空则从任务queue的最前面(front)弹出，并且执行任务。若为空则阻塞住，或者当所有任务完成或出现停止时，则线程return，表示线程结束。任务可通过enqueue()接口插入任务queue，这也就是为什么存放任务必须是有双向迭代器的数据结构，因为必须要有pop和push两种功能。
      
      
