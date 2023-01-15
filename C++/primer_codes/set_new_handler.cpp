#include <iostream>
#include <new>
 
void handler()
{
    std::cout << "Memory allocation failed, terminating\n";
    std::set_new_handler(0);
}
 
int main()
{
    std::set_new_handler(handler);
    try {
        while (true) {
            new int[1000'000'000ul]();
        }
    } catch (const std::bad_alloc& e) {
        std::cout << e.what() << '\n';
    }
}
