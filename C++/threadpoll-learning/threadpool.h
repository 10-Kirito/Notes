#pragma once

#include "safe_queue.h"
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>
class ThreadPool {
private:
    class ThreadWorker { // 内置的线程工作类
    private:
        int _id; // 工作id
        ThreadPool* _pool; // 所属于的线程池
    public:
        ThreadWorker(ThreadPool* pool, const int id): _pool(pool), _id(id) {}

        void operator()() {
            std::function<void()> func;

            bool dequeued;

            while(!_pool->_shutdown) {// 如果该工作线程对应的线程池类没有关闭的话
                {
                    std::unique_lock<std::mutex> lock(_pool->_conditional_mutex);
                    if(_pool->_tasks_queue.empty()) {
                        _pool->_conditional_lock.wait(lock);
                    }
                    dequeued = _pool->_tasks_queue.dequeue(func);
                }
                // 如果重新从任务队里当中获取了相应的任务事件，就执行相应的任务
                if(dequeued) {
                    func();
                }
            }
        }
    };

    bool _shutdown; // 线程池是否已经关闭
    SafeQueue<std::function<void()>> _tasks_queue; // 待分配任务队列，队列使用的是安全队列
    std::vector<std::thread> _threads; // 存储工作线程的数组

    std::mutex _conditional_mutex; // 控制线程之间的临界资源竞争

    std::condition_variable _conditional_lock; // 线程环境锁，让线程可以处于休眠或者唤醒状态
public:
    ThreadPool(const int n_threads) :_threads(std::vector<std::thread>(n_threads)), _shutdown(false) {
    }
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool &&) = delete;
    ThreadPool & operator=(const ThreadPool &) = delete;
    ThreadPool & operator=(ThreadPool&&) = delete;

    void init() {
        for(int i = 0; i < _threads.size(); i++) {
            _threads[i] = std::thread(ThreadWorker(this, i)); // 分配工作线程
        }
    }

    void shutdown() {
        _shutdown = true;
        _conditional_lock.notify_all();
        for(int i = 0; i < _threads.size(); i++) {
            if(_threads[i].joinable()) _threads[i].join();
        }
    }

    template<typename F, typename ...Args>
    auto submit(F&& f, Args... args) -> std::future<decltype(f(args...))> {
        // 创建我们提交的函数以及绑定对应的参数
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        // 使用共享指针来保存我们任务，来使得其可以得到正确的释放
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
        // 将任务进行下一步的封装，将其封装为更一般的函数void function(void){}
        std::function<void()> wrapper_func = [task_ptr]() {
            (*task_ptr)();
        };
        // 将一般化之后的任务来插入到我们的任务队列当中
        _tasks_queue.enqueue(wrapper_func);
        // 通知一个正处于阻塞状态的线程
        _conditional_lock.notify_one();
        // 立即返回，来保证主线程不陷入阻塞
        return task_ptr->get_future(); 
    }
};