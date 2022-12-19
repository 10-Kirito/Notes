import java.util.*;
public class OutputTest
{
	public static void main(String [] args){
		double num = 3333333.33333;
		System.out.printf("%,.2f\n",num);

		String name = "Kirito";
		System.out.printf("%s\n",name);

		System.out.printf("%tc",new Date());

	}

}