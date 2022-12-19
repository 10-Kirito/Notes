import java.util.*;
import java.io.*;
public class Main {
    public static void main(String[] args)
    {
        System.out.println("Hello world!");
        double y = Math.pow(2,2);
        System.out.println(y);
        System.out.println(new Date());
        String  a = "hello";
        String  b = "hello";
        String  c = null;
        String  d = "";
        System.out.println(System.identityHashCode(a));
        System.out.println(System.identityHashCode(b));
        // 此处identityHashCode函数返回的是指定对象的哈希代码
        a.equals(b);
        System.out.println(a.hashCode());
        System.out.println(b.hashCode());
        System.out.println(System.identityHashCode(""));
        System.out.println(System.identityHashCode(c));
        // System.out.println(c.length());
        System.out.println(d.length());

        // 测试int类型和integer类型的不同
        Integer e = new Integer(100);
        Integer f = 100;
        // 相当于调用Integer f = new Integer(100);
        int temp = e.intValue();

        System.out.println(System.identityHashCode(e));
        // int 类型的哈希值是和字符串的不一样的处理方法
        System.out.println(e.hashCode());
        System.out.println(temp);

        // 测试java的输入对象，Scanner
        Scanner in = new Scanner(System.in);
        int num = in.nextInt();
        System.out.println(num);

        int [] array = new int[in.nextInt()];
        System.out.println(array.length);
        // System.out.println();

        String str = "Hello,world!";
        int [] codePoints = str.codePoints().toArray();

        for(int i: codePoints)
            System.out.println(i);

    }
}