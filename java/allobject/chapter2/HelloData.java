import java.util.*;
/**�ⲿ�ӿ���*/
public class HelloData
{
	/**���������*/
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