# CMake Learning

## 0.CMake相关配置

> ATTENTION!!!!
>
> 我们在CMakeLists.txt文件当中所编辑的内容都是在给整个项目的构建设置目录依赖等，最后会生成一个Makefile文件，然后使用该文件来编译整个项目.

### 0.1 语言相关

***设置C++标准：***

```cmake
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
```

### 0.2 编译器相关

#### 0.2.1 CMake的三个链接选项(PRIVATE PUBLIC INTERFACE)

项目的结构如下：

```shell
kirito@kirito:~/test/test_private_interface_pubilc$ tree .
.
├── app.cpp
├── bar.cpp
├── bar.h
├── CMakeLists.txt
├── foo.cpp
└── foo.h

0 directories, 6 files
```

其中的代码分别为:

```cpp
// foo.h
int foo();

// foo.cpp
#include <foo.h>

int foo() {
    return 22;
}

// bar.h
#include <foo.h>

int bar();

// bar.cpp
#include <bar.h>
int bar() {
    return foo() + 1;;
}

// app.cpp
#include <bar.h>
#include <iostream>

int main() {
    std::cout << "From foo()" << foo() << std::endl;
    std::cout << "From bar()" << bar() << std::endl;
    return 0;
}


// CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

project(foobar)
set(CMAKE_SKIP_RPATH TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(${CMAKE_SOURCE_DIR})

add_library(foo SHARED foo.cpp)

add_library(bar SHARED bar.cpp)
target_link_libraries(bar INTERFACE foo)

add_executable(app app.cpp)

target_link_libraries(app bar)
```

CMake的三种依赖关系分别对应为:

***PRIVATE:*** 

`bar.h`没有包含`foo.h`, 只有`bar.cpp`包含了`foo.h`, 此时`app`仅仅只包含了`bar.h`,所以说`app`根本不知道`foo`的存在，只知道`bar`的存在，所以说对于`bar`来讲的话，只有自己才可以访问`foo`, 虽然`app`也依赖于`bar`但是仍然无法访问`foo`;

***INTERFACE:***

`bar.h`中包含了`foo.h`，但是`bar.cpp`并没有用到`foo`定义的符号。此时，由于`app` 包含了`bar.h`文件，所以说`app`也同样包含了`foo.h`，这样就可以引用`foo`的符号。换句话说，`bar`只是作为一个接口、界面，把`foo`传递给了`app`;

***PUBLIC：***

相当于PRIVATE加上INTERFACE，`bar.h`包含了`foo.h`, 而且`bar.cpp`也引用了`foo`的符号。此时，`app`包含了`foo.h`，可以引用`foo`的符号;(默认情况下就是PUBLIC)

#### 0.2.2 编译器当中的几个内置参数

***[`PROJECT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/PROJECT_SOURCE_DIR.html#variable:PROJECT_SOURCE_DIR)***：代表着我们项目的主路径，也就是CMakeLists.txt所在的路径;

### 0.3 CMake所用的函数

- [`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)

在当前的项目当中生成一个library。

- [`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory)

在当前的项目当中创建一个模块，该模块有自己的CMakeLists.txt文件以及源代码文件。

- [`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories)

指定编译所给定目标所需要包含的目录。

-  [`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)

Specify libraries or flags to use when linking a given target and/or its dependents.就是链接对应的库到给定的目标。

- [`message()`](https://cmake.org/cmake/help/latest/command/message.html)

```cmake
message(STATUS "Using protobuf ${Protobuf_VERSION}")
message(STATUS "${Protobuf_INCLUDE_DIRS}")
message(STATUS "${PROTOBUF_LIBRARIES}")
```

- [`get_filename_component()`](https://cmake.org/cmake/help/latest/command/get_filename_component.html)

该函数的作用是为了获取当前文件的全称当中的某些部分，比如说文件名字(`NAME`)、文件所在的路径(`PATH`)、文件的绝对路径(`ABSOLUTE`)、文件的相对路径(`DIRECTORY`):

```cmake
DIRECTORY = Directory without file name
NAME      = File name without directory
EXT       = File name longest extension (.b.c from d/a.b.c)
NAME_WE   = File name with neither the directory nor the longest extension
LAST_EXT  = File name last extension (.c from d/a.b.c)
NAME_WLE  = File name with neither the directory nor the last extension
PATH      = Legacy alias for DIRECTORY (use for CMake <= 2.8.11)
```

- [`aux_source_directory()`](https://cmake.org/cmake/help/latest/command/aux_source_directory.html#command:aux_source_directory)

```cmake
aux_source_directory(. DIR_SRCS)
add_executable(protobuf_test ${DIR_SRCS})
```



## 1. 创建最简单的项目

### 1.1 CMakeLists.txt

```cmake
# 使用cmake构建项目，首先需要声明cmake的版本
cmake_minimum_required(VERSION 3.22.1)
# 指明项目的名称
project(hello-world)
# 让cmake使用指定的源文件来创建一个可执行文件
add_executable(hello main.cpp)
```

### 1.2 Build and Run

```shell
kirito@kirito:~/test/json-learning$ ls
CMakeLists.txt  main.cpp
kirito@kirito:~/test/json-learning$ mkdir build
kirito@kirito:~/test/json-learning$ cd build
kirito@kirito:~/test/json-learning/build$ cmake ..
-- The C compiler identification is GNU 11.4.0
-- The CXX compiler identification is GNU 11.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/kirito/test/json-learning/build
kirito@kirito:~/test/json-learning/build$ cmake --build .
[ 50%] Building CXX object CMakeFiles/hello.dir/main.cpp.o
[100%] Linking CXX executable hello
[100%] Built target hello
kirito@kirito:~/test/json-learning/build$ ./hello
Hello, World!
```

另外还可以使用`-B`来指明我们构建的系统的文件夹：

```shell
kirito@kirito:~/test/json-learning$ cmake -B build
```

## 2. 怎么样才可以在源代码当中使用CMakeLists.txt当中的变量？

> One way to accomplish this is by using a configured header file. We create an input file with one or more variables to replace. These variables have special syntax which looks like `@VAR@`. Then, we use the [`configure_file()`](https://cmake.org/cmake/help/latest/command/configure_file.html#command:configure_file) command to copy the input file to a given output file and replace these variables with the current value of `VAR` in the `CMakelists.txt` file.

我们主要是需要使用到cmake当中的`configure_files()`函数:

```cmake
configure_file(<input> <output>
               [NO_SOURCE_PERMISSIONS | USE_SOURCE_PERMISSIONS |
                FILE_PERMISSIONS <permissions>...]
               [COPYONLY] [ESCAPE_QUOTES] [@ONLY]
               [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])
```

Copies an `<input>` file to an `<output>` file while performing [transformations](https://cmake.org/cmake/help/latest/command/configure_file.html#transformations) of the input file content.

If the input file is modified the build system will re-run CMake to re-configure the file and generate the build system again. The generated file is modified and its timestamp updated on subsequent cmake runs only if its content is changed.

我们在使用cmake进行构建的时候，我们会自动从input文件读取，生成output文件，其中`@var@`会将`var`替换为在CMakeLists.txt文件中声明的相应的变量。

注意，我们在构建之后会生成相对应的文件，比如说头文件之类的；如果我们构建的target当中需要使用到该头文件的话，需要我们指定包含目录：

```cmake
target_include_directories(hello PUBLIC "${PROJECT_BINARY_DIR}")
```

## 3. 如何创建自己的库并进行链接？

项目结构：

```shell
kirito@kirito:~/test/cmake_learning/cmake_2$ tree .
.
├── CMakeLists.txt
├── MathFunctions
│   ├── CMakeLists.txt
│   ├── MathFunctions.cxx
│   ├── MathFunctions.h
│   ├── mysqrt.cxx
│   └── mysqrt.h
├── TutorialConfig.h.in
└── tutorial.cxx

1 directory, 8 files
```

其中MathFunctions是我们自己创建的模块，我们想要在`Tutorial`模块当中调用该模块。

> 注意，其中我们是在`MathFunctions.cxx`当中引用`mysqrt`，所以说我们链接`MathFunctions`与`SqrtLibary`两个模块的时候应该设置为:
>
> ```cmake
> add_library(MathFunctions MathFunctions.cxx mysqrt.cxx)
> ...
> if(USE_MYMATH)
>     ...
>     add_library(SqrtLibrary mysqrt.cxx)
>     target_link_libraries(MathFunctions PRIVATE SqrtLibrary)
> endif()
> ```
>
> 而其余的链接的时候设置为public即可.	

最顶层的`CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(TutorialConfig.h.in TutorialConfig.h)

# 添加子目录:
# TODO 2: Use add_subdirectory() to add MathFunctions to this project
add_subdirectory(MathFunctions)

# add the executable
add_executable(Tutorial tutorial.cxx)

# TODO 3: Use target_link_libraries to link the library to our executable
target_link_libraries(Tutorial PUBLIC MathFunctions)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
# 指明编译器应该去该文件目录下去寻找头文件MathFunctions.h，因为我们在Tutroial模块当中引用了MathFunctions里面的内容，所以这里引入相应的目录
target_include_directories(Tutorial PUBLIC "${PROJECT_SOURCE_DIR}/MathFunctions")

# 指明编译器应该去该文件目录下，也即是build目录下去寻找生成的TutorialConfig.h头文件
# TODO 4: Add MathFunctions to Tutorial's target_include_directories()
# Hint: ${PROJECT_SOURCE_DIR} is a path to the project source. AKA This folder!
target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}")
```

里面的`CMakeLists.txt`:

```cmake
# TODO 14: Remove mysqrt.cxx from the list of sources

# TODO 1: Add a library called MathFunctions with sources MathFunctions.cxx
# and mysqrt.cxx
# Hint: You will need the add_library command
add_library(MathFunctions MathFunctions.cxx mysqrt.cxx)

# TODO 7: Create a variable USE_MYMATH using option and set default to ON
option(USE_MYMATH "Use tutorial provided math implementation" ON)

# TODO 8: If USE_MYMATH is ON, use target_compile_definitions to pass
# USE_MYMATH as a precompiled definition to our source files
if(USE_MYMATH)
    target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")
    # TODO 12: When USE_MYMATH is ON, add a library for SqrtLibrary with
		# source mysqrt.cxx
    add_library(SqrtLibrary mysqrt.cxx)
    # 注意，这里SqrtLibrry模块只能被MathFunctions模块进行使用，不被我们主模块Tutorial使用，所以说这里设置为PRIVATE
    # TODO 13: When USE_MYMATH is ON, link SqrtLibrary to the MathFunctions Library
    target_link_libraries(MathFunctions PRIVATE SqrtLibrary)
endif()
```

## 4. 如何查找系统当中的包？

主要是使用[`find_packages()`](https://cmake.org/cmake/help/v3.5/command/find_package.html)这条命令：

```cmake
cmake_minimum_required(VERSION 3.10)
project(protobuf_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Protobuf 3.20.3 REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")
message(STATUS "${Protobuf_INCLUDE_DIRS}")
message(STATUS "${PROTOBUF_LIBRARIES}")

aux_source_directory(. DIR_SRCS)

add_executable(protobuf_test ${DIR_SRCS})

target_include_directories(protobuf_test PRIVATE ${Protobuf_INCLUDE_DIRS})
target_link_libraries(protobuf_test ${Protobuf_LIBRARIES})
```

其中`find_package`命令具有两种模式：***MODULE***以及***CONFIG***.

- ***MODULE模式：***使用CMake自带的`Find.cmake`模块或者在`CMAKE_MODULE_PATH`变量当中指定的路径查找库；
- ***CONFIG模式：***CMake使用对应库自带的Config.cmake查找库，第三方库会在该文件当中声明相关的变量；

更多用法可以查看：https://cmake.org/cmake/help/v3.5/command/find_package.html

- 设置相应的版本：`find_package(Protobuf 3.20.3 REQUIRED)`;

