# GoogleTest

> 官方文档：
>
> https://github.com/google/googletest/blob/main/docs/primer.md

# 1. 基本测试

```c++
#include "pch.h"
#include <cstring>

using namespace std;
TEST(TestCaseName, TestName) {
  

	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
	
	// 0. 错误信息打印：
	// 这里是将我们自己定义的失败消息，只需要使用运算符<< 将自定义信息传输到相应的宏函数中即可
	// 这样的话如果我们测试的时候出现了错误就会打印相应的信息
	EXPECT_EQ(1, 1) << "1 and 2 is not equal";


}
	// 1. 使用TEST()宏来定义和命名测试函数，这些是不返回值的普通的C++函数
TEST(TestMyCode, TestFun) {
	// 2. 测试函数的两个参数问题：
	
	// 这里就是定义了一个组测试TestMyCode, 该组测试中有一个测试单元叫做TestFun
	// 第一个参数被称为Test Suite,即测试套件；
	// 第二个参数是测试套件中的测试名称

	// 注意：两个名称都必须是有效的C++标识符，不应该包含任何下划线。
	// 测试的全名是由包含它的Test Suits以及它的individual name所组成，来自不同Test Suits的测试可以具有相同的individual name
	EXPECT_EQ(Factorial(1), 1);
	EXPECT_EQ(Factorial(2), 1) << "函数的返回值为：" << Factorial(2);
	EXPECT_EQ(Factorial(3), 1) << "函数的返回值为：" << Factorial(3);
}
```

# 2. Test Fixture( 夹具，这名字是人起的吗？？？)

有的时候，我们需要对同一组数据进行不同的测试，这样的话，如果我们仍然按照之前所学的知识就会造成代码的冗余，所以说我们Google Test可以创建一种名字为fixture的东西，其实就是类。

***要创建夹具：***

1. 我们需要先创建一个测试类，该测试类派生自`::testing::Test`. 我们在写该类的时候需要将所有的数据声明为`protected`，因为我们想要从子类当中去访问fixture成员；
2. 在我们创建的类中声明出我们将要使用的任何对象；
3. 然后我们通过书写成员函数`SetUp()`来对我们所创建的对象进行一系列的初始化，我们也可以编写默认的构造函数来帮助我们准备对象；
4. 如果有必要的话，我们需要写一个析构函数或者`TearDown`函数来释放我们在构造函数或者`SetUp`函数当中申请的资源，或者我们也可以编写一个`TearDown()`函数来进行资源的释放；

当我们使用我们所编写的夹具的时候，我们应该使用TEST_F()函数来进行测试：

```c++
TEST_F(TestFixtureName, TestName){
  ··· test body ···
}
```

***其中的名称的命名规则是和TEST()是完全一样的。***

对于每一个测试，Google Test 在运行的时候会创建一个新的测试Fixture对象，然后通过`SetUp`函数对其进行初始化；接着就是运行我们所编写的测试代码进行测试；最后Google Test 会调用`TearDown()`函数来销毁掉刚才创建的测试Fixture对象。***还有就是我们需要注意一点：同一测试套件中的不同测试具有不同的测试Fixture对象，也就是说我们每一个测试都会有一个独立的新的测试Fixture对象。***

```C++
// 示例代码，仅展示接口
template <typename E>  // E is the element type.
class Queue {
 public:
  Queue();
  void Enqueue(const E& element);
  E* Dequeue();  // Returns NULL if the queue is empty.
  size_t size() const;
  ...
};
```

测试Fixture类：

```C++
class QueueTest : public ::testing::Test {
 protected:
  void SetUp() override {
     // q0_ remains empty
     q1_.Enqueue(1);
     q2_.Enqueue(2);
     q2_.Enqueue(3);
  }

  // void TearDown() override {}
  // 这里我们并没有实现TearDown函数，这是因为我们在这里还用不上

  Queue<int> q0_;
  Queue<int> q1_;
  Queue<int> q2_;
};
```

接下来我们就该使用`TEST_F`来编写测试代码：

张若曦

```C++
TEST_F(QueueTest, IsEmptyInitially){
  EXPECT_EQ(q0_Deque(), 0);
}

TEST_F(QueueTest, DequeueWorks){
  int* n = q0_.Dequeue();
  // equal
  EXPECT_EQ(n, nullptr);
  
  n = q1_.Dequeue();
  // not equal
  ASSERT_NE(n, nullptr);
  EXPECT_EQ(*n, 1);
  EXPECT_EQ(q1_.size(), 0);
  delete n;
  
  n = q2_.Dequeue();
  ASSERT_NE(n, nullptr);
  EXPECT_EQ(q2_.size(),1);
  delete n;
}
```

> 上面的测试在运行的时候会发生下面的过程：
>
> - googletest 构造一个`QueueTest`对象（我们称之为`t1`）。
> - `t1.SetUp()`初始化`t1`。
> - 第一个测试 ( `IsEmptyInitially`) 在 上运行`t1`。
> - `t1.TearDown()`测试完成后清理。
> - `t1`被释放。
> - 在另一个对象上重复上述步骤`QueueTest`，这次运行`DequeueWorks`测试。

# 3. 调用测试

`TEST`和`TEST_F`使用GoogleTest隐式注册他们的测试，所以说我们在测试的时候只需要定义我们的测试即可。

我们如果定义好了我们所有的测试之后，我们可以利用`RUN_ALL_TESTS()`来运行所有的测试，如果所有的测试都成功的话会返回0，否则的话会返回1.

> PS：
>
> Note that `RUN_ALL_TESTS()` runs *all tests* in your link unit--they can be from different test suites, or even different source files.

***当我们调用`RUN_ALL_TESTS`宏的时候会发生下面的事情：***

1. 保存所有GoogleTest 标志的状态；
2. 为第一个测试创建一个test fixture object；
3. 通过函数`SetUp`或者构造函数进行初始化；
4. 利用GoogleTest隐式创建的对象来运行我们所有的测试；
5. 最后如果有必要的话，调用析构函数或者`TearDown()`函数来释放我们申请的资源；
6. 重复上述过程进行下面一个测试；

> IMPORTANT: You must **not** ignore the return value of `RUN_ALL_TESTS()`, or you will get a compiler error. The rationale for this design is that the automated testing service determines whether a test has passed based on its exit code, not on its stdout/stderr output; thus your `main()` function must return the value of `RUN_ALL_TESTS()`.
>
> Also, you should call `RUN_ALL_TESTS()` only **once**. Calling it more than once conflicts with some advanced googletest features (e.g., thread-safe [death tests](https://github.com/google/googletest/blob/main/docs/advanced.md#death-tests)) and thus is not supported.

# 4. 编写main函数

```c++
#include "this/package/foo.h"

#include "gtest/gtest.h"

namespace my {
namespace project {
namespace {

// The fixture for testing class Foo.
class FooTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  FooTest() {
     // You can do set-up work for each test here.
  }

  ~FooTest() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST_F(FooTest, MethodBarDoesAbc) {
  const std::string input_filepath = "this/package/testdata/myinputfile.dat";
  const std::string output_filepath = "this/package/testdata/myoutputfile.dat";
  Foo f;
  EXPECT_EQ(f.Bar(input_filepath, output_filepath), 0);
}

// Tests that Foo does Xyz.
TEST_F(FooTest, DoesXyz) {
  // Exercises the Xyz feature of Foo.
}

}  // namespace
}  // namespace project
}  // namespace my

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
```



