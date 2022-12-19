# Makefile study

> 参考文章https://seisman.github.io/how-to-write-makefile/overview.html#id2

## 零. 关于程序的编译和链接

1. 无论是C还是C++，都首先需要将源文件编译成中间代码文件，在windows下就是`.obj`文件，UNIX下是`.0`文件（Object File），这个动作叫做编译。然后将大量的Object File 合成执行文件，这个动作叫做链接（Link）。
2. 编译的时候，编译器需要的是语法的正确，函数与变量的声明的正确，只要全部的语法正确的话，编译器就可以编译出中间目标文件，一般来说，每一个源文件都应该对应一个中间文件（`.o`文件或者`.obj`文件）。
3. 链接的时候，主要链接函数和全局变量。所以我们可以使用这些中间文件（`.o`文件或者`.obj`文件）来链接我们的应用程序。链接器并不去管源文件怎么样，只管函数的中间目标文件（Object File），在大多的时候，可能会遇到编译之后有着大量的中间文件，这样的话，我们在链接的时候，就是在makefile中需要明显的指出中间目标文件名，这样的话很显然有点耗时，所以说我们需要给中间目标文件打一个包。在Windows中这种包叫做“库文件”（Library File），也就是`.lib`文件，在UNIX下，是Archive File，也就是`.a`文件。

## makefile介绍

***Makefile的规则：***

***makefile的规则，是由依赖关系规则和命令组成的。***

- makefile中的任何命令都要以Tab键开始的

```makefile
target...: prerequisites ...
	command
	...
```

- target :可以是一个.obj文件，也可以是一个可执行文件；
- prerequisites（先决条件，前提） :生成该target所需要的文件，比如说如果这个target文件是main.o，那么此处应该写生成该文件的前提文件；
- command :该target执行的命令（任意的shell命令）；
- ***如果prerequisitest中有一个文件比target文件要新的话，command所定义的命令就会被执行；***

Makefile 文件的示例：

***反斜杠`\`是换行符的意思，这样有利于makefile的阅读。***

```mak
edit : main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
    cc -o edit main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o

main.o : main.c defs.h
    cc -c main.c
kbd.o : kbd.c defs.h command.h
    cc -c kbd.c
command.o : command.c defs.h command.h
    cc -c command.c
display.o : display.c defs.h buffer.h
    cc -c display.c
insert.o : insert.c defs.h buffer.h
    cc -c insert.c
search.o : search.c defs.h buffer.h
    cc -c search.c
files.o : files.c defs.h buffer.h command.h
    cc -c files.c
utils.o : utils.c defs.h
   	cc -c utils.c
clean :
    rm edit main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
```

***当我们执行`make`的时候，就会生成可执行文件`edit`，main.o kbd.o command.o等等文件是该可执行文件的前提文件。***

```mak
edit : main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
    cc -o edit main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
```

***如果我们想要删除可执行文件和中间所有的生成文件，我们可以执行`make clean`命令。***

```mak
clean :
    rm edit main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
```

***中间makefile所写代码，指出着每一个.o文件的依赖文件，当然了这些.o文件又是edit文件的依赖文件。（本质上就是指出是有哪些文件生成的）***

```mak
files.o : files.c defs.h buffer.h command.h
    cc -c files.c
```

上面所讲述的仅仅是一些依赖文件是如何进行说明的，对于后面一行的指令并未做出过多的介绍。

在定义好文件依赖关系之后呢，后续的一行定义了怎么生成前面target文件的操作系统命令。（***一定要以一个`tab`键作为开头***）

这里需要注意的是，`clean`不是一个文件，他只不过是一个动作名字，其冒号后面什么也没有，那么`make`命令也就不会去寻找它的依赖性，也就不会去执行其后面所定义的命令，当然了，如果我们使用命令`make clean`那就会执行其后面所定义的命令。

***如果我们要执行类似于clean这些后面所定义的命令时，我们需要在make后面指出该target的名字，我们这个方法利用这些规则去定义一些和编译无关的命令，比如说清理文件、程序的打包或者程序的备份等等。***

## make命令是如何工作的

我们只输入`make`命令的情况下：

- make会在当前目录下找到名字为`Makefile`或者`makefile`的文件；
- 如果找到的话，它会去寻找文件中的第一个target文件，并将其作为最终的目标文件；
- 如果目标文件不存在，或者目标文件的依赖文件做出过修改的话，`make`就会执行后面定义的命令来重新生成这个文件，以保证文件的最新；
- 如果目标文件的依赖项文件也不存在，或者说，依赖项文件也刚刚做出过修改，那么同样的`make`会去执行后面的指令，来生成相关的文件；

`make`命令在执行的过程中，会去一层一层的去寻找文件的依赖关系，知道最终编译出第一个目标文件，寻找的过程中，如果出现错误，例如最后被依赖的文件找不到了，make会直接退出，并报错。***对于make所定义命令的错误，或者编译不成功，make根本不理睬。***

## makefile 中使用变量

```sh
edit : main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
    cc -o edit main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
```

在这里，我们可以看见这些`.o `文件被重复输入了两次，如果我们的工程中加入了一个新的文件，那么我们可能需要在很多的地方都要加入新的文件的说明，所以说，变量的引入就会显得尤为关键。

我们可以在文件中声明一个变量：在文件的一开始就定义：

```shell
objects = main.o kbd.o command.o display.o \
     insert.o search.o files.o utils.o
```

然后我们可以以`$(objects)`的方式来使用这个变量：

```shell
objects = main.o kbd.o command.o display.o \
    insert.o search.o files.o utils.o

edit : $(objects)
    cc -o edit $(objects)
main.o : main.c defs.h
    cc -c main.c
kbd.o : kbd.c defs.h command.h
    cc -c kbd.c
command.o : command.c defs.h command.h
    cc -c command.c
display.o : display.c defs.h buffer.h
    cc -c display.c
insert.o : insert.c defs.h buffer.h
    cc -c insert.c
search.o : search.c defs.h buffer.h
    cc -c search.c
files.o : files.c defs.h buffer.h command.h
    cc -c files.c
utils.o : utils.c defs.h
    cc -c utils.c
clean :
    rm edit $(objects)
```

## 让make自动推导

GNU的make很强大，它可以自动推导文件以及文件依赖关系后面的命令，于是我们就没必要去在每一个 `.o` 文件后都写上类似的命令，因为，我们的make会自动识别，并自己推导命令。

只要make看到一个 `.o` 文件，它就会自动的把 `.c` 文件加在依赖关系中，如果make找到一个 `whatever.o` ，那么 `whatever.c` 就会是 `whatever.o` 的依赖文件。并且 `cc -c whatever.c` 也会被推导出来，于是，我们的makefile再也不用写得这么复杂。我们的新makefile又出炉了。

```
objects = main.o kbd.o command.o display.o \
    insert.o search.o files.o utils.o

edit : $(objects)
    cc -o edit $(objects)

main.o : defs.h
kbd.o : defs.h command.h
command.o : defs.h command.h
display.o : defs.h buffer.h
insert.o : defs.h buffer.h
search.o : defs.h buffer.h
files.o : defs.h buffer.h command.h
utils.o : defs.h

.PHONY : clean
clean :
    rm edit $(objects)
```

这种方法，也就是make的“隐晦规则”。上面文件内容中， `.PHONY` 表示 `clean` 是个伪目标文件。

关于更为详细的“隐晦规则”和“伪目标文件”，我会在后续给你一一道来。

## 另类风格的makefiles

既然我们的make可以自动推导命令，那么我看到那堆 `.o` 和 `.h` 的依赖就有点不爽，那么多的重复的 `.h` ，能不能把其收拢起来，好吧，没有问题，这个对于make来说很容易，谁叫它提供了自动推导命令和文件的功能呢？来看看最新风格的makefile吧。

```
objects = main.o kbd.o command.o display.o \
    insert.o search.o files.o utils.o

edit : $(objects)
    cc -o edit $(objects)

$(objects) : defs.h
kbd.o command.o files.o : command.h
display.o insert.o search.o files.o : buffer.h

.PHONY : clean
clean :
    rm edit $(objects)
```

这种风格，让我们的makefile变得很简单，但我们的文件依赖关系就显得有点凌乱了。鱼和熊掌不可兼得。还看你的喜好了。我是不喜欢这种风格的，一是文件的依赖关系看不清楚，二是如果文件一多，要加入几个新的 `.o` 文件，那就理不清楚了。