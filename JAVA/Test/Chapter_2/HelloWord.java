//单行注释
/*
多行注释
*/

/**
*类的注释信息
*@version 1.0测试
*@author 
*该注释是可以被javadoc.exe解析识别并提取到帮助文档当中的。
*/
public class HelloWord{
	//main函数
	public static final double TEST = 5.21;
	public static void main(String[] args){
		System.out.println("Hello,Word!");
		System.out.println(TEST);
		test();
	}
	static int test(){
		System.out.println("测试Java的除法相关规则：");
		System.out.println(0.0/0);
		return 0;
	}
}


public class test {
	public static void main(String[] args) {
		System.out.println("test.main");

	}
}