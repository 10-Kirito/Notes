import java.util.*;
import java.io.*;
//测试输入流的一些方法
public class InputTest
{
	public static void main(String [] args){
		Scanner in = new Scanner(System.in);
		System.out.println("What's your name?");
		String name = in.nextLine();
		System.out.println("What's your age?");
		int age = in.nextInt();
		System.out.printf("Your name is %s.\nYour age is %d.\n",name,age);
		
		Console cons = System.console();
		String username = cons.readLine("User name: ");
		char [] passwd = cons.readPassword("Password: ");
		System.out.println(passwd);
	}
}