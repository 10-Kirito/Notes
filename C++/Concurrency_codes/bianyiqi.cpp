#include <iostream>

using namespace std;

class Test
{
  
  public: 
  inline Test(int val)
  : _val{val}
  {
    std::operator<<(std::cout, "Test::Test()").operator<<(std::endl);
  }
  
  inline Test(const Test & other)
  : _val{other._val}
  {
    std::operator<<(std::cout, "Test::Test(const Test&)").operator<<(std::endl);
  }
  
  inline ~Test() noexcept
  {
    std::operator<<(std::cout, "Test::~Test()").operator<<(std::endl);
  }
  
  inline Test & operator=(const Test & other)
  {
    this->_val = other._val;
    std::operator<<(std::cout, "Test::operator=(const Test& other)").operator<<(std::endl);
    return *this;
  }
  
  
  private: 
  int _val;
};



int main()
{
  Test test = Test(5);
    
  class __lambda_21_27
  {
    public: 
    inline Test operator()() const
    {
      return Test(test);
    }
    
    private: 
    Test test;
    public: 
    // inline __lambda_21_27 & operator=(const __lambda_21_27 &) /* noexcept */ = delete;
    __lambda_21_27(const Test & _test)
    : test{_test}
    {}
    
  };
  
  __lambda_21_27 func_value = __lambda_21_27{test};
  func_value.operator()();
  return 0;
}
