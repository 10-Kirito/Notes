#include <iostream>
#include <thread>
#include <mutex>
#include <list>

using namespace std;

mutex my_mutex;
list<int> global_l;

void producer()
{
    for (int i = 1; i < 100 ; i++)
    {

        if (i != 99)
        {

			my_mutex.lock();
            global_l.push_back(i);
            cout << "write data " << i << endl;
			my_mutex.unlock();
        }
        else
        {
			my_mutex.lock();
            global_l.push_back(0);
			my_mutex.unlock();
            cout << "producer quit" << endl;
        }

        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer()
{
    int temp = -1;
    while (temp != 0)
    {
		if(!global_l.empty()) {

			my_mutex.lock();
			temp = global_l.front();
			global_l.pop_front();
			my_mutex.unlock();

			cout << "consumer read " << temp << endl;
		}

    }
}

int main()
{
    thread thread_producer(producer);
    thread thread_consumer(consumer);

    thread_producer.join();
    thread_consumer.join();

    cout << "Main quit" << endl;
}
