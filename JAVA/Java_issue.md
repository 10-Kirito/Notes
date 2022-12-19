# Java学习过程相关问题：

##### **1.关于类中函数之间调用时的问题：**

![image-20220619160847164](.\pictures\5.png)

```java
public class HelloWord{
	//main函数
	public static void main(String[] args){
		final double TEST = 2.54;
		System.out.println("Hello,Word!");
		System.out.println(2.0-1.1);
		test();
	}
    //问题所在定义test函数的时候没有声明staic，导致上面图片所示问题！
	int test(){
		System.out.println("测试成功！");
		return 0;
	}
}
```

##### 2.编码问题（未解决！！）

```java
import java.util.*;
//测试输入流的一些方法
public class InputTest
{
	public static void main(String [] args){
		Scanner in = new Scanner(System.in);
		System.out.println("What's your name?");
		String name = in.nextLine();
		System.out.println("What's your age?");
		int age = in.nextInt();
		System.out.printf("Your name is %s.\nYour age is %d.",name,age);

	}
}
```

![image-20220726173843019](.\pictures\6.png)

**问题所在：每次输入中文的时候，输出就会报错！**
