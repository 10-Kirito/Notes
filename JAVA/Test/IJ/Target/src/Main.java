// 本程序的目的是测试Java中指针是被什么替换了
// 测试结果表明，在Java中对象其实就是指针，什么意思呢？
// 下面的程序中我们编写了一个返回引用可变对象的访问器方法。
// 我们返回的是一个对象，如果在C++中，我们此时通过d变量
// 是不能直接改变test对象中的date成员变量的。
// 但是在Java中这样做是可以的，就是我们呢通过d来接收到返回的
// 对象，然后我们改变d就相当于在改变test对象的成员变量
// 所以说，在Java中，我们可以将对象就当作是指针和变量的结合体!!

// 如果我们需要返回
import java.util.Date;

public class Main {
    public static void main(String[] args)
    {
        Test test = new Test();
        Date d = test.getDate();
        System.out.println(test.getDate());

        double ten = 10 * 365.25 * 24 * 60 * 60 * 1000;
        d.setTime(d.getTime() - (long)ten);

        System.out.println(test.getDate());
    }
}
class Test
{
    private Date date;
    public Test(){ date = new Date();}
    public Date getDate() {
        return date;
    }
}