import java.util.*;
/**外部接口类*/
public class HelloData
{
	/**主函数入口*/
	public static void main(String args[])
	{
		System.out.println(new Date());
		System.out.println("Hello World!");
		Properties p = System.getProperties();
		p.list(System.out);
		System.out.println("---------Memory Usage:");
		Runtime rt = Runtime.getRuntime();
		System.out.println("Total Memory = " + rt.totalMemory() + "Free Memory = " + rt.freeMemory());
	}
}