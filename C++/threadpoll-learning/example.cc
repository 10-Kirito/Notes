#include "threadpool.h"
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <thread>

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(-1000, 1000);
auto rnd = std::bind(dist, mt);


void simulate_hard_computaion() {
    std::this_thread::sleep_for(std::chrono::milliseconds(200 + rnd()));
}

void multiply(const int a, const int b) {
    simulate_hard_computaion();
    const int res = a * b;
    std::cout << a << " * " << b << " = " << res << std::endl;
}

void multiply_output(int &out, const int a, const int b) {
    simulate_hard_computaion();
    out = a * b;
    std::cout << a << " * " << b << " = " << out << std::endl; 
}

int multiply_return(const int a, const int b) {
    simulate_hard_computaion();
    const int res = a * b;
    std::cout << a << " * " << b << " = " << res << std::endl;
    return res;
}

int main(int argc, char** argv) {
    ThreadPool pool(3);
    pool.init();

    // 1.这里模拟的是正常的函数提交，我们只需要线程池帮助我们运行这些任务即可，无须访问其对应的执行结果
    for(int i = 1; i < 3; ++i) {
        for(int j = 1; j < 10; ++j) {
            pool.submit(multiply, i, j);
        }
    }

    int output_ref;
    // 2.这里模拟的是我们需要线程池帮助我们运行这些任务，并且我们需要其对应的执行结果
    auto future1 = pool.submit(multiply_output, std::ref(output_ref), 5, 6);
    // 这里等待对应的线程执行完成并返回结果，主线程在这里陷入阻塞
    future1.get();
    std::cout << "Last operation is equals to " << output_ref << std::endl;

    // 3. 这里模拟的是具有返回值的函数
    auto future2 = pool.submit(multiply_return, 5, 4);
    int res = future2.get();
    std::cout << "Last operation is equals to " << res << std::endl;

    pool.shutdown();
    return 0;
}