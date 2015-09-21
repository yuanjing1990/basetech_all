public class MaxOfThree
{
	public static void main(String args[])
	{
		int a = 5;
		int b = 6;
		int c = 7;
		if(a > b)
		{
			if(a > c)
			{
				System.out.println("三个数中最大的是："+a);
			}
			else
			{
				System.out.println("三个数中最大的是："+c);
			}
		}
		else
		{
			 if ( b > c)
			 {
			 	 System.out.println("三个数中最大的是："+b);
			 }
			 else
			 {
			 	 System.out.println("三个数中最大的是："+c);
			 }
		}
	}
}