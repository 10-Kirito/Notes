import java.util.*;

public class ArrayTest
{
	public static void main(String [] args)
	{
		int [] a = {17,19,21,31,37};
		int [] temp = a;

		temp[0] = 100000;

		System.out.println(Arrays.toString(a));
		System.out.println(Arrays.toString(temp));
	}
}