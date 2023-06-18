# MPI并行计算

> 目录examples都是MPICH官方提供的简单示例文件，仅供参考!

# 1. MPI 相关知识介绍

## 1.1 通信子

在MPI编程中，**通信子**（communicator）是一个虚拟的进程组，它定义了一组进程的通信环境。MPI通信子是MPI的一个重要概念，它可以将一个MPI进程集合划分为一个或多个通信子，每个通信子中的进程可以相互通信。MPI标准定义了两种类型的通信子：

1. **Intracommunicator**（内部通信子）：它是同一集合内的所有进程的通信组，即用于进程间的通信和同步。MPI_COMM_WORLD就是一个Intracommunicator。
2. **Intercommunicator**（外部通信子）：它是由两个或多个Intracommunicator组成的通信组，用于不同MPI进程之间的通信和同步。

通信子是MPI编程的重要组成部分，它提供了一种机制，使得用户可以有效地控制和管理MPI进程之间的通信和同步，从而实现并行计算的目的。





# 2. MPI相关函数

## 2.1`MPI_Init(&argc, &argv)`

> 初始化MPI库。
>
> - `argc` 和 `argv` 分别是 main 函数的参数 argc 和 argv，这里通过引用传递给 MPI_Init 函数。
> - MPI_Init 函数必须是 MPI 库的第一个调用函数，它会初始化 MPI 运行时环境，***并创建默认的通信子 MPI_COMM_WORLD***。

## 2.2`MPI_Comm_size(MPI_COMM_WORLD, &numprocs)`

> 获取当前通信子中的进程数。
>
> - `MPI_COMM_WORLD` 是默认的通信子，包含了所有启动的进程。
> - `numprocs` 是一个***输出参数***，用来存储当前通信子中的进程数。

## 2.3`MPI_Comm_rank(MPI_COMM_WORLD, &myid)`

> 获取当前进程在当前通信子中的标识号。
>
> - `myid` 是一个输出参数，用来存储当前进程在当前通信子中的标识号。
> - MPI 会自动为**每个进程分配一个唯一的标识号**，该标识号从 0 开始，依次递增。

## 2.4`MPI_Get_processor_name(processor_name, &namelen)`

> 获取当前进程所在的处理器的名称。
>
> - `processor_name` 是一个输出参数，用来存储当前进程所在的处理器的名称。
> - `namelen` 是一个输出参数，用来存储处理器名称的长度。

## 2.5`MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMMWORLD)`

> 将进程0中的`n`值广播给所有的进程。
>
> - `&n` 是要广播的数据的地址。
> - `1` 表示要广播的数据的个数。
> - `MPI_INT` 表示要广播的数据的类型。
> - `0` 表示广播的源进程的标识号。
> - `MPI_COMM_WORLD` 表示广播的通信子，即所有进程。

## 2.6`MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD)`

> 将所有进程的`mypi`值进行相加，并将结果存储在进程0中的`pi`变量中。
>
> - `&mypi` 是要进行归约操作的数据的地址。
> - `&pi` 是归约操作的结果的存储位置。
> - `1` 表示要归约的数据的个数。
> - `MPI_DOUBLE` 表示要归约的数据的类型。
> - `MPI_SUM` 表示要进行的归约操作，即求和。
> - `0` 表示接收归约结果的进程的标识号。
> - `MPI_COMM_WORLD` 表示归约操作的通信子，即所有进程。

可以参考以下示例程序：

 [cpi.c](examples\cpi.c) 

## 2.7 MPI_Wtime()

> MPI_Wtime函数是MPI中的一个计时函数，用于获取当前时刻的时间戳，返回的时间单位是秒。MPI_Wtime在并行程序中常用于计算程序的执行时间或者统计不同部分的执行时间，以便优化程序的性能。
>
> MPI_Wtime可以用于不同进程间的时间同步，即在MPI程序中，不同进程可以通过MPI_Wtime获取到相同的时刻，以实现时间同步。MPI_Wtime是一个可重入的函数，可以多次调用，并且在程序中任何位置都可以使用。
>
> 需要注意的是，MPI_Wtime返回的时间可能受到系统时间和MPI实现的影响，因此在比较不同计时结果时需要谨慎。另外，MPI_Wtime返回的时间戳通常是一个较精确的值，但是也可能受到系统和MPI实现的限制而产生一定的误差。





# 3. MPI相关常量

## 3.1MPI_MAX_PROCESSOR_NAME

> MPI_MAX_PROCESSOR_NAME是MPI中的一个常量，它代表了MPI实现中处理器名（processor name）的最大长度。在调用MPI_Get_processor_name函数时，需要传递一个指向一个char类型的数组的指针以及一个整型变量的指针，用于接收处理器名和处理器名的长度。为了保证在接收处理器名时数组不会溢出，需要确保数组长度不小于MPI_MAX_PROCESSOR_NAME。MPI_MAX_PROCESSOR_NAME的值可以使用MPI_Comm_get_attr函数来获取，其定义在mpi.h头文件中。