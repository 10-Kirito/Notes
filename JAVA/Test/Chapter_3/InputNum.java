
public class InputNum
{
	public static void main(String [] args){
		//创建一个键盘扫描器对象
		java.util.Scanner s = new java.util.Scanner(System.in);
		//接受用户的输入，从键盘上接受一个int类型的数据
		int inputUserNum = s.nextInt();

		int temp = s.nextInt();
		System.out.println("输入的两个数字为：" + inputUserNum + " " + temp);
		String str = s.next();
		System.out.println("输入的字符串为：" + str);
	}

}