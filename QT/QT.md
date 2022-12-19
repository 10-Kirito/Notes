# Qt Creator

## 1.创建第一个QT程序

### 1.1 基础知识

基类：**Qwidget**(父类)、**QMainWindow**(子类)、**QDialog**(子类)

### 1.2 创建第一个QT程序

```Q
#include "widget.h"

#include <QApplication>//包含一个应用程序类的头文件

//main程序入口  argc：命令行变量的数量 argv：命令行变量的数组；
//当我们使用键盘或者鼠标的时候，这些命令都会通过这些参数传送到QApplication中去；
int main(int argc, char *argv[])
{
    //a是应用程序对象，在Qt中，应用程序对象有且只有一个；
    //因为我们最终创建的应用程序只有一个；
    QApplication a(argc, argv);
    //创建父类对象，即最基本的空窗口；
    Widget w;

    //窗口对象 ，默认是不会显示的，必须要调用show方法来显示窗口；
    w.show();

    //让应用程序进入消息循环机制中；
    //就是让这个应用程序时刻去"聆听"事件，当点击叉号事件发生的时候，结束程序等等类似的；

    return a.exec();
}
```

### 1.3 工程文件

```properties
#qt包含模块：core核心模块以及gui图形界面的模块
QT       += core gui
#qt版本大于4的时候要加入qt widget 模块
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#源文件
SOURCES += \
    main.cpp \
    widget.cpp
#头文件 
HEADERS += \
    widget.h

FORMS += \
    widget.ui

TRANSLATIONS += \
    First_pro_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

```

在配置文件中修改程序名字：

```q
TARGET = HELLO #可以指定相应名字
```



**基本的模块：**

![image-20220911214448176](C:\Users\z1769\AppData\Roaming\Typora\typora-user-images\image-20220911214448176.png)

### 1.4 快捷键

//注释 Ctrl + /

//运行 Ctrl + R

//编译 Ctrl + B

//帮助文档 F1

//自动对齐 Ctrl + i

//同名之间的.h和.cpp切换 F4

## 2.如何查看帮助文档

### 2.1 查看我们经常使用的一个**按钮类**：

![image-20220911233306248](C:\Users\z1769\AppData\Roaming\Typora\typora-user-images\image-20220911233306248.png)

**Inherits**的意思是继承的意思，即其父类:

![image-20220911234355638](C:\Users\z1769\AppData\Roaming\Typora\typora-user-images\image-20220911234355638.png)

### 2.2 查看我们经常使用的网络通讯

![image-20220911233616593](C:\Users\z1769\AppData\Roaming\Typora\typora-user-images\image-20220911233616593.png)

如果我们用到了这个类的时候，我们需要在项目配置文件中写入network，如下图所示：

![image-20220911234121988](C:\Users\z1769\AppData\Roaming\Typora\typora-user-images\image-20220911234121988.png)

## 3.button控件的简单使用-怎么组合起来

### 3.1 显示按钮

我们导入QpushButton类，然后调用其显示函数，但是此时是以顶层方式弹出窗口控件（就是按钮是按钮，窗口是窗口）

比如下图所示：

![image-20220911235312067](C:\Users\z1769\AppData\Roaming\Typora\typora-user-images\image-20220911235312067.png)

这显然不是我们想要的效果，我们想要的是在主窗口之中，含有一个按钮。就是让**按钮对象依赖在主窗口**中！

我们需要给这个控件找一个父亲，就是将该控件和主窗口连接起来，父亲（widget）显示，其孩子（button）也可以显示。

![image-20220912000053938](C:\Users\z1769\AppData\Roaming\Typora\typora-user-images\image-20220912000053938.png)

### 3.2 显示文本

```d
QPushButton * btn = new QPushButton;
btn->setParent(this);
btn->setText("The first button!");
```

### 3.3 使用更加方便的重载函数

```d
QPushButton * btn1 = new QPushButton("Test!",this);
```

### 3.4 移动按钮控件

```d
btn1->move(300,0);
```

### 3.5 设置窗口的标题

```d
setWindowTitle("窗口");
```

### 3.5 按钮设置大小

**按钮也是可以调用其祖宗类的函数resize的！**

## 4.对象树

![image-20220912081043484](C:\Users\z1769\AppData\Roaming\Typora\typora-user-images\image-20220912081043484.png)

**设置父亲之后，就不需要再去管该控件的析构的调用了，它会自己调用相关的析构函数！（简化了内存回收机制）**

## 5.QT中的坐标系

**左上角为0，x向右增加，y向下增加！**

## 6.信号与槽

**关键在于我们如何实现组件与组件之间的通信！这就是信号与槽的主要功能！**

### 6.1 connect函数，将各个控件行为连接起来

```c++
connect(信号的发送者，发送的具体信号，信号的接收者，信号的处理(槽函数的使用))
```

信号槽的优点：松散耦合，信号的发送者以及信号的接收者本身是没有关联的，我们可以通过connect连接将二者耦合在一起！

这个信号的处理，我们需要去帮助文档里面去找！

### 6.2 自带的信号与槽函数

```c++
//实现功能点击我的按钮，关闭窗口
//参数一：信号的发送者 参数2：发送的信号（函数的地址）参数3：是信号的接收者 参数4：处理的槽函数Slot，就是对该信号该如何去处理
connect(btn2,&QPushButton::clicked,this,&QWidget::close);
```

### 6.3 自定义信号与槽

我们也可以自己去定义相应的信号与槽，我们去定义去实现相应的功能。

```c+
signals:
    void Hundry();
//自定义信号
//返回值是void,只需要声明，不需要实现
//可以有参数，可以去重载
```

```c++
public:
    explicit Student(QObject *parent = nullptr);
    void  treat();
//响应信号的槽
//返回void，需要声明，需要实现
//可以有参数，可以去重载
```

### 6.4 信号和槽发生重载

***如果我们定义的信号与槽函数发生重载的话，那么我们就需要利用函数指针来告诉主函数这个信号是哪一个信号，这个槽函数是哪一个槽函数！！***

```qt
//以下书写方式，主函数不能识别出具体是哪一个信号，所以说我们需要一个函数指针来进行绑定，来告诉主函数发送的信号是哪一个
void (Teacher::* teacherSignal)(QString) = &Teacher::Hundry;
void (Student::* studentSignal)(QString) = &Student::treat;
connect(zpf,teacherSignal,stu,studentSignal);
```

> 写的时候需要注意在函数指针的前面指明是哪一个里面的信号或者槽函数。

