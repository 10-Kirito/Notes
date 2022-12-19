/**
*测试javadoc功能
* @author 周鹏飞
* @version 1.0
* @since 1.0
*/
public class Myfirst{
	/**
	* 这是一个程序的入口
	* @param args 是main方法的参数
	*/
    public static void main(String[] args){
        int beernum = 99;
        String word = "bottles";

        while(beernum > 0){ if(beernum == 1) { word = "bottle"; }

            System.out.println(beernum + " " + word + "of beer on the wall"); 
            System.out.println(beernum + " " + word + "of beer."); 
            System.out.println("Take one down."); 
			System.out.println("Pass it around."); 
			beernum = beernum - 1;

            if(beernum > 0){
                System.out.println(beernum + " " + word + "of beer on the wall");
            }else {
                System.out.println("No more bottles of beer on the wall");
            }
        }
    }
}