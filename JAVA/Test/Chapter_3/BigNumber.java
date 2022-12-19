import java.math.*;

public class BigNumber
{
	public static void main(String [] args)
	{
		BigInteger a = BigInteger.valueOf(100);
		BigInteger b = new BigInteger("23231321315145464687879465413213548645313213551512131512");
		//int temp = 12315464648797895641321;报错整数太大
		System.out.print("整数测试：\n");
		System.out.println(a);
		System.out.println(b);
		//System.out.println(temp);
		System.out.print("浮点数测试：\n");
		BigDecimal c = new BigDecimal("1231454687745455345532154534354354135435");
		System.out.println(c);
	}
}