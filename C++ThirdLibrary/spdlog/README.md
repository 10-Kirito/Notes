# Spdlog-Learning

> spdlog 是一个快速的 C++ 日志库，具有简单易用的接口和高性能。它支持多线程、异步日志、格式化输出等功能，并提供了灵活的配置选项。spdlog 提供了多种日志输出目标，包括控制台、文件、syslog 等。它是一个流行的日志库，被许多C++项目所采用。

# 1. How to install?

```shell
$ git clone https://github.com/gabime/spdlog.git
$ cd spdlog && mkdir build && cd build
$ cmake .. && make -j
$ sudo make install
```

> - 头文件下载位置为：`/usr/local/include/spdlog`;
>
> - 链接库下载位置为:`/usr/local/lib/libspdlog.a`;
>
> - pkg-config file and Cmake config file 下载位置:
>
> ```shell
> -- Installing: /usr/local/lib/pkgconfig/spdlog.pc
> -- Installing: /usr/local/lib/cmake/spdlog/spdlogConfigTargets.cmake
> -- Installing: /usr/local/lib/cmake/spdlog/spdlogConfigTargets-release.cmake
> -- Installing: /usr/local/lib/cmake/spdlog/spdlogConfig.cmake
> -- Installing: /usr/local/lib/cmake/spdlog/spdlogConfigVersion.cmake
> ```

# 2. How to use?

***CMake setting:***

```cmake
find_package(spdlog REQUIRED)
# ...
target_link_libraries(spdlog_example PRIVATE spdlog::spdlog)
```

## 2.1 Basic usage

```C++
#include "spdlog/spdlog.h"

int main() {
  spdlog::info("Welcome to spdlog!");
  spdlog::error("Some error message with arg: {}", 1);

  spdlog::warn("Easy padding in numbers like {:08d}", 12);
  spdlog::critical(
      "Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
  spdlog::info("Support for floats {:03.2f}", 1.23456);
  spdlog::info("Positional args are {1} {0}..", "too", "supported");
  spdlog::info("{:<30}", "left aligned");

  // spdlog::set_level(spdlog::level::debug); // Set global log level to debug
  spdlog::debug("This message should be displayed..");

  // change log pattern
  spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

  spdlog::info("Welcome to spdlog!");
  // Compile time log levels
  // Note that this does not change the current log level, it will only
  // remove (depending on SPDLOG_ACTIVE_LEVEL) the call on the release code.
  SPDLOG_TRACE("Some trace message with param {}", 42);
  SPDLOG_DEBUG("Some debug message");
}
```

The output:

```SHELL
kirito@kirito:~/learnings/spdlog-learning$ ./build/spdlog_example 
[2024-03-24 17:20:00.835] [info] Welcome to spdlog!
[2024-03-24 17:20:00.835] [error] Some error message with arg: 1
[2024-03-24 17:20:00.835] [warning] Easy padding in numbers like 00000012
[2024-03-24 17:20:00.835] [critical] Support for int: 42;  hex: 2a;  oct: 52; bin: 101010
[2024-03-24 17:20:00.835] [info] Support for floats 1.23
[2024-03-24 17:20:00.835] [info] Positional args are supported too..
[2024-03-24 17:20:00.835] [info] left aligned                  
[17:20:00 +08:00] [] [---I---] [thread 22079] Welcome to spdlog!
```

## 2.2 Basic file logger

### 1. one file output

```C++
#include "spdlog/sinks/basic_file_sink.h"
#include <iostream>
#include <spdlog/common.h>
#include <spdlog/logger.h>

int main(int, char **) {
  try {
    // create basic file logger(not rotated)
    auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/basix.txt");

    my_logger->info("Welcome to spdlog!");
    my_logger->error("Some error message with arg: {}", 1);
    my_logger->warn("Easy padding in numbers like {:08d}", 12);
  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log initialization failed" << ex.what() << std::endl;
  }
}
```

The output:

```shell
kirito@kirito:~/learnings/spdlog-learning$ tree -I build
.
├── basic-logger.cc
├── CMakeLists.txt
├── hello-world.cc
├── logs
│   └── basix.txt
└── rotating-logger.cc

1 directory, 5 files
```

`cat basix.txt`:

```txt
kirito@kirito:~/learnings/spdlog-learning$ cat logs/basix.txt 
[2024-03-24 17:22:15.550] [basic_logger] [info] Welcome to spdlog!
[2024-03-24 17:22:15.550] [basic_logger] [error] Some error message with arg: 1
[2024-03-24 17:22:15.550] [basic_logger] [warning] Easy padding in numbers like 00000012
```

### 2. many files output

> 轮转文件日志记录器是一种特殊类型的日志记录器，用于将日志消息写入到多个文件中，并根据一定的规则对这些文件进行轮转（也称为滚动或循环）。
>
> 通常，当日志文件达到一定大小或数量限制时，轮转文件日志记录器会关闭当前日志文件，并将新的日志消息写入到一个新的文件中。这样可以确保日志文件不会无限增长，同时也可以保留一定数量的旧日志文件以供参考。
>
> 轮转文件日志记录器通常具有以下特性：
>
> 1. **文件大小限制**：可以指定每个日志文件的最大大小。一旦当前日志文件达到指定的大小限制，轮转文件日志记录器将关闭当前文件，并开始写入到一个新的文件中。
> 2. **文件数量限制**：可以指定保留的旧日志文件数量。一旦达到指定数量的日志文件，轮转文件日志记录器将删除最早的日志文件，以保持总的日志文件数量不超过限制。
> 3. **自动轮转**：轮转文件日志记录器通常会自动处理日志文件的轮转，无需手动干预。一旦达到轮转条件，它会自动关闭当前日志文件，并开始写入到一个新的文件中。
> 4. **循环记录**：轮转文件日志记录器会循环使用一组预定义的日志文件名，以便在轮转时使用新的文件名。
>
> 通过使用轮转文件日志记录器，可以避免单个日志文件过大而导致存储问题，并且可以方便地管理和检查历史日志。

```C++
#include "spdlog/sinks/rotating_file_sink.h"
#include <cstdio>
#include <ctime>
#include <iostream>
#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <string>

std::string Time() {
  std::time_t now = std::time(nullptr);
  std::tm *nowtm = std::localtime(&now);

  char file_name[1024];
  sprintf(file_name, "%d-%d-%d-log.txt", nowtm->tm_year + 1900,
          nowtm->tm_mon + 1, nowtm->tm_mday);
  return std::string(file_name);
}

int main(int, char **) {
  try {

    std::string filename = "logs/" + Time();
    auto file_logger =
        spdlog::rotating_logger_mt("mylogger", filename, 1024, 10);
    for (int i = 0; i < 1000; ++i) {
      file_logger->info("Hello,world, {}", i);
    }
  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log initialization failed: " << ex.what() << std::endl;
  }
}
```

***The output:***

```C++
kirito@kirito:~/learnings/spdlog-learning$ tree -I build
.
├── basic-logger.cc
├── CMakeLists.txt
├── hello-world.cc
├── logs
│   ├── 2024-3-24-log.10.txt
│   ├── 2024-3-24-log.1.txt
│   ├── 2024-3-24-log.2.txt
│   ├── 2024-3-24-log.3.txt
│   ├── 2024-3-24-log.4.txt
│   ├── 2024-3-24-log.5.txt
│   ├── 2024-3-24-log.6.txt
│   ├── 2024-3-24-log.7.txt
│   ├── 2024-3-24-log.8.txt
│   ├── 2024-3-24-log.9.txt
│   └── 2024-3-24-log.txt
└── rotating-logger.cc
```

