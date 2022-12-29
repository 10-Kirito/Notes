# AT&T汇编入门
# 一.基本语法

- ***label***，任何以冒号结尾的标识符，都会被认为是一个标号；
- ***symbol***，代表它所在的地址，也可以当作变量或者函数来使用；
- 全局symbol，可以使用`.global`来声明；
- 局部symbol，局部范围使用，开头以0-99为标号，通常和b指令结合；
- ***伪指令：***
- `.glign`对齐，填充数据实现对齐。ARM64系统中，第一个参数表示2^n大小；

| 伪指令            | 描述                                             |
| ----------------- | ------------------------------------------------ |
| `.byte`           | 把8位数当作数据插入汇编中                        |
| `.hword`          | 把16位数当作数据插入汇编中                       |
| `.long`/`.int`    | 把32位数当作数据段插入汇编中                     |
| `.quad`           | 把64位数当作数据插入汇编中                       |
| `.float`          | 把浮点数当作数据插入汇编中                       |
| `.ascii "string"` | 把string当作数据插入汇编中，末尾需要手动添加‘\0’ |
| `.asciz "string"` | 类似于.ascii，在string后自动插入'\0'             |
| `.rept`           | 重复定义                                         |
| `.equ`            | 赋值操作                                         |
| `.set`            | 赋值操作                                         |

- ***内存操作数的寻址方式：***
- AT&T汇编格式：`section:disp(base, index, scale)`
- Intel 汇编格式： `section:[base + index*scale + disp]`
- `movzbw #作0扩展的1字节复制到2字节`
- `movzbl #作0扩展的1字节复制到4字节`
- `movzbq #作0扩展的1字节复制到8字节`
- `movzwl #作0扩展的2字节复制到4字节`
- `movzwq #作0扩展的2字节复制到8字节`
- `movzlq #作0扩展的4字节复制到8字节`

# 二.实际使用

## 1. 汇编使用`prinf`

```h
.section .data
msg:
.ascii "hello world!%d\n"

.section .text
.global _start      # must be declared for linker
_start:
	movq $5,%rsi
    movq $msg, %rdi
    call printf

    movq $60, %rax     # 'exit' syscall number
    xor %rdi, %rdi     # set rdi to zero
    syscall
```

执行结果：



` ld hello3.o -o hello3 -lc -I /lib64/ld-linux-x86-64.so.2 `中的`-lc`是链接`libc.so`，-I是链接器的意思。

## 2. 理解`ld-linux.so.2`

`ld-linux.so.2`是Linux下的动态库加载器/链接器。他的工作就是将我们编写的	代码中包含的头文件里面的动态库链接进来。

对于`/lib/ld-linux.so.2`，ELF（***Executable and Linkable Format,可执行与可链接格式***）二进制文件（可执行文件）的内核处理程序将应用程序加载到内存中后，操作系统会将控制权移交给`/lib/ld-linux.so.2`，动态链接器所要做的事情主要是搜索并加载未解析的库，加载程序中任何引用的库，然后将控制权交给正在执行的二进制文件的起始地址。该解释器被定义为ELF文件的结构的一部分，位于程序标题的INERP部分。对于32位的`linux`二进制文件，这是32位解释器的典型名称。对于64位二进制文件，解释器的名字通常为`ld-linux-x86_64.so.2`。

我们可以使用`ldd`命令来查看一个可执行文件的依赖库：



可以使用`readelf -l 'test'`命令查看一个程序的程序头：

