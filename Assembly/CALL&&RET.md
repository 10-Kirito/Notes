[TOC]

# CALL和RET指令

# 1. `ret`和`retf`

`ret`指令使用栈中的数据修改IP的内容，从而实现近转移；

`retf`指令用栈中数据，修改CS和IP的内容，从而实现远转移；

CPU执行`ret`指令的时候，进行下面两步操作：

```assembly
pop IP
#(IP) = ((SS)*16 + (SP))
#(SP) = (SP) + 2
```

CPU执行`retf`指令的时候，进行下面4步操作：

```assembly
pop IP
pop CS
# (IP) = ((SS)*16 + (SP))
# (SP) = (SP) + 2
# (CS) = (SS)*16 + (SP)
# (SP) = (SP) + 2
```

# 2. CALL

CPU执行`CALL`指令的时候。进行两步操作：

（1）将当前IP或者CS和IP压入栈中；

（2）转移；

`CALL`指令不能实现短转移，除此之外，`CALL`指令实现转移的方法和`JMP`指令的原理相同；

## 2.1 `CALL 标号`

（1）将当前的IP或者CS和IP压入栈中；

（2）转移；

CPU执行`CALL 标号`的时候，进行下面操作：

```assembly
push IP# 该指令执行之后，自会IP加一
jmp near ptr 标号
#(SP)  =(SP) - 2
#((SP)*16 + (SP)) = (IP)
#(IP) = (IP) + 16位位移
```

## 2.1 `call far ptr 标号`

CPU执行该指令的时候：

```assembly
PUSH CS
PUSH IP
JMP FAR PTR 标号
#(SP)=(SP)-2
#((SS)*16 + (SP))=(CS)
#(SP)=(SP)-2
#((SS)*16+(SP)) = (IP)
#(CS) = 标号所在段的段地址
#(IP) = 标号所在段的偏移地址
```

# 3. 子程序结构

## 3.1 子程序的设计方法

### 3.1.1 子程序定义伪操作

```ass
procedure name PROC Atrribute
······
procedure name ENDP
```

属性attribute是指类型属性，可以是NEAR和FAR。

- NEAR，如果调用程序和过程在同一个代码段中，则使用NEAR属性；
- FAR，如果调用程序和过程不在同一个代码段中的，则使用FAR属性（***最典型的比如说，DOS程序调用主程序，DOS程序和主程序肯定不在同一个代码段中，所以说主程序定义的时候，肯定是FAR属性***）；

### 3.1.2 子程序的调用和返回

*CALL指令和RETN指令*：

### 3.1.3 保护和恢复寄存器

调用程序和子程序是分别编制的，所以说使用的寄存器会发生冲突。解决这种问题的方法就是***保护现场***，即调用子程序之前将所关键的寄存器压栈，之后再弹栈以恢复数据。

可用的指令：

`PUSHA/POPA/PUSHAD/POPAD`

### 3.1.4 子程序的参数传送

- 通过寄存器传送变量
- 过程和调用程序在同一个源文件中，可直接访问源文件中的在数据段中定义的变量

这样的话，会导致子程序固化，即子程序只能操作哪一些数据，为了解决这些问题，引出下面两种方法：

- 通过地址表传达变量地址

该方法就是在主程序中建立一个地址表，就是将所要使用的数据存放到指定的地址中，然后将该地址表的首地址存放到指定的寄存器中，以实现一个传参的过程。

```ass
mov table,offset num
mov table+2,offset n
mov table+4,offset total
mov bx,offset table
call proadd
```

- 通过堆栈传送参数或者参数地址
