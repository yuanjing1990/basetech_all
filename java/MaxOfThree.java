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
				System.out.println("�������������ǣ�"+a);
			}
			else
			{
				System.out.println("�������������ǣ�"+c);
			}
		}
		else
		{
			 if ( b > c)
			 {
			 	 System.out.println("�������������ǣ�"+b);
			 }
			 else
			 {
			 	 System.out.println("�������������ǣ�"+c);
			 }
		}
	}
}