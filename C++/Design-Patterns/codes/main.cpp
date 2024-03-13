#include "template.hpp"
#include <iostream>
#include <memory>
#include <mutex>

// version1:
/* class Singleton {
private:
  Singleton() { std::cout << "constructor called" << std::endl; }
  // ban copy constructor and assignment operator
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;
  // the only instance
  static Singleton *instance;

public:
  ~Singleton() { std::cout << "destrcutor called" << std::endl; }

  static Singleton *getInstance() {
    if (instance == nullptr) {
      instance = new Singleton();
    }
    return instance;
  }
}; */

// version 2 : using shared_ptr and call_once to implement singleton
class Singleton {
private:
  typedef std::shared_ptr<Singleton> SingletonPtr;
  Singleton() { std::cout << "constructor called" << std::endl; }
  // ban copy constructor and assignment operator
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;
  // the only instance
  static SingletonPtr instance;
  static std::once_flag flag;
public:
  ~Singleton() { std::cout << "destrcutor called" << std::endl; }
  static SingletonPtr getInstance() {
    std::call_once(
        flag, []() { instance = std::shared_ptr<Singleton>(new Singleton); });
    return instance;
  }
};

// initialize static member
Singleton::SingletonPtr Singleton::instance = nullptr;
std::once_flag Singleton::flag;

// version 3: most elegant way to implement singleton
class Singleton2 {
public:
  ~Singleton2() {}
  Singleton2(const Singleton2 &) = delete;
  Singleton2 &operator=(const Singleton2 &) = delete;
  static Singleton2 &get_instance() {
    static Singleton2 instance;
    return instance;
  }
private:
  Singleton2() {}
};

// version 4: using template to implement singleton
class DerivedSingleton : public SingletonTemplte<DerivedSingleton> {
  friend class SingletonTemplte<DerivedSingleton>;
public:
  DerivedSingleton(const DerivedSingleton &) = delete;
  DerivedSingleton &operator=(const DerivedSingleton &) = delete;
private:
  DerivedSingleton() = default;
};

int main() {
  DerivedSingleton &instance1 = DerivedSingleton::get_instance();
  DerivedSingleton &instance2 = DerivedSingleton::get_instance();
}