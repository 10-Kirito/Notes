import java.util.*;
import java.time.*;
public class TimeClass
{
	public static void main(String [] args)
	{
		System.out.println("----------4.1.1----------");
		
		System.out.println(new Date());	
		String time = new Date().toString();
		System.out.println(time);
		Calendar canlendar = Calendar.getInstance();
		System.out.println(canlendar.get(Calendar.HOUR));
		
		System.out.println("----------4.1.2----------");
		LocalDate newYearsEve = LocalDate.of(1999,12,31);
		System.out.println(newYearsEve.toString());
		LocalDate nowTime = LocalDate.now();
		System.out.println(nowTime.toString());
		int month = nowTime.getMonthValue();
		int today = nowTime.getDayOfMonth();
		System.out.printf("这一月是 %d ,这一天是第 %d 天！\n",month,today);
		DayOfWeek weekday = nowTime.getDayOfWeek();
		int value = weekday.getValue();
		System.out.println(value);

		System.out.println("----------程序清单4-1----------");
		LocalDate date = LocalDate.now();
		int month_4_1 = date.getMonthValue();
		int today_4_1 = date.getDayOfMonth();
		System.out.println("今天是：" + date);
		System.out.println("Mon Tue Wed Thu Fri Sat Sun");
		
		date = date.minusDays(today - 1);//修改日期到这一月的月初
		DayOfWeek weekday_4_1 = date.getDayOfWeek();
		int value_4_1 = weekday_4_1.getValue();
		for(int i = 1;i < value_4_1;i++)
			System.out.print("     ");
		while(date.getMonthValue() == month)
		{
			System.out.printf("%3d",date.getDayOfMonth());
			if(date.getDayOfMonth() == today)
				System.out.print("*");
			else
				System.out.print(" ");
			date = date.plusDays(1);//将日期加一天
			if(date.getDayOfWeek().getValue() == 1)
				System.out.println();
		}
		if(date.getDayOfWeek().getValue() != 1)
			System.out.println();
	}
}