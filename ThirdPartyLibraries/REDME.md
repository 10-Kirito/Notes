# C++ Third Part Library

# 0. pkg-config 介绍

> [!TIP]
>
> `pkg-config` 是一个在 Linux 和类 Unix 系统上使用的软件包配置工具。它提供了一种简便的方式来查询已安装的软件包的元数据，例如编译器标志、链接标志和其他相关的配置选项。`pkg-config` 是开发软件时常用的一个工具，特别是当您需要在您的代码中使用外部库时。
>
> 使用 `pkg-config`，您可以：
>
> 1. 查询已安装的软件包的版本信息。
> 2. 获取编译时所需的头文件路径。
> 3. 获取链接时所需的库文件路径。
> 4. 获取编译器和链接器标志，以便正确地编译和链接您的代码。
>
> `pkg-config` 主要通过名为 `.pc` 的文件来存储软件包的配置信息。这些文件通常位于系统的标准配置目录中，例如 `/usr/lib/pkgconfig` 或 `/usr/local/lib/pkgconfig`。
>
> 总的来说，`pkg-config` 可以帮助开发人员更轻松地管理软件包依赖关系，并确保他们的代码正确地编译和链接所需的外部库

比如说[JSON](https://github.com/nlohmann/json):

```cmake
#...
# Install a pkg-config file, so other tools can find this.
CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/pkg-config.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
)
#...
```

再比如[Protobuf](https://github.com/protocolbuffers/protobuf)

```c++
# you can find the *.pc file after you compile the source codes:
# protobuf.pc
prefix=/usr/local
exec_prefix=${prefix}
libdir=${exec_prefix}/lib
includedir=${prefix}/include

Name: Protocol Buffers
Description: Google's Data Interchange Format
Version: 3.20.3
Libs: -L${libdir} -lprotobuf
Libs.private: -lz 

Cflags: -I${includedir}
Conflicts: protobuf-lite
```

So you can type these commands to find the header directories and library directories to compile projects:

```shell
# help
kirito@kirito:~$ pkg-config --help
# pkg-config show all the pre-processor and compile flags
kirito@kirito:~$ pkg-config --cflags protobuf
-I/usr/local/include
# pkg-config show the lib directories and the lib
kirito@kirito:~$ pkg-config --libs protobuf
-L/usr/local/lib -lprotobuf
```

Nice!!!



# 1.Json

> https://github.com/nlohmann/json





# 2.Protobuf

> https://github.com/protocolbuffers/protobuf
>
> https://cmake.org/cmake/help/latest/module/FindProtobuf.html



# 3.muduo

> https://github.com/chenshuo/muduo







# 4.mysqlcppconnect

> https://dev.mysql.com/doc/connector-cpp/1.1/en/connector-cpp-connect-options.html
