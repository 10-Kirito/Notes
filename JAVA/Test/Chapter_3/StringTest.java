
public class StringTest
{
	public static void main(String [] args)
	{
		String greeting = "Hello!";
		String s = greeting.substring(0,3);
		System.out.println("1.测试提取字符串：");
		System.out.println("原来的字符串为："+greeting+"原来的字符串长度为:"+greeting.length());
		System.out.println("提取出来的字符串为："+s);
		System.out.println("\n");
		System.out.println("2.测试拼接字符串：");
		
		String s0 = "中国！";
		String s1 = "Hello,Word!";

		String s2 = s0 + s1;
		System.out.println("字符串s0:" + s0 + "和字符串s1:" +s1+ "拼接后为s2:"+s2);
		
		int num = 12;
		s2 = num + s0;
		System.out.println("字符串s2为："+s2);
		System.out.println("\n");
		System.out.println("3.测试定界符分割函数,静态join方法！");
		String temp = String.join(",","张三","李五");
		System.out.println(temp);
		System.out.println("\n");
		System.out.println("4.检测字符串是否相等");
		String a = "Hello!";
		String b = "Hello!";
		if(a==b)
			System.out.println("字符串a和字符串b存放的位置一样！");
		else
			System.out.println("字符串a和字符串b存放的位置不一样！");

		if(a.substring(0,3) == "Hel")
			System.out.println("字符串a和字符串b存放的位置一样！");
		else
			System.out.println("字符串a和字符串b存放的位置不一样！");

		if(a.substring(0,3).equals("Hel"))
			System.out.println("字符串a和字符串b相同");
		else
			System.out.println("字符串a和字符串b不相同");
		System.out.println("\n");
		if(a.substring(0,3).compareTo("Hel") == 0)
			System.out.println("5.测试compareTo方法\n字符串a和字符串b相同");
		else
			System.out.println("字符串a和字符串b不相同");
		System.out.println("\n");
		
		
		System.out.println("6.测试空串和null串");
		String zeroStr = "";
		System.out.println("该字符串的长度为："+zeroStr.length());
	}

}