#ifndef TEMPLATE_H
#define TEMPLATE_H
#include <iostream>
template <typename T> class SingletonTemplte {
public:
  static T &get_instance() {
    static T instance;
    return instance;
  }

  virtual ~SingletonTemplte() {
    std::cout << "basic destructor called" << std::endl;
  }

  SingletonTemplte(const SingletonTemplte &) = delete;
  SingletonTemplte &operator=(const SingletonTemplte &) = delete;

protected:
  SingletonTemplte() { std::cout << "contructor called" << std::endl; }
};

#endif // TEMPLATE_H