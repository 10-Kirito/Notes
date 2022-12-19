import java.util.*;
import java.nio.file.*;
import java.nio.charset.*;
import java.io.*;
public class FileInOut
{
	public static void main(String [] args) throws IOException
	{
		//Scanner in = new Scanner(Path.of("myfile.txt"),"UTF-8");
		
		//String temp = in.nextLine();	

		//System.out.printf("文件中第一行的内容为：%s",temp);
		String temp = "Hello,Word!";
		PrintWriter out = new PrintWriter("myfile.txt","UTF-8");
		out.println(temp);
		//out.flush();
		out.printf("你好！");
		out.close();
	}

}