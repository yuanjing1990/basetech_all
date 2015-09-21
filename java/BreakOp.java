public class BreakOp
{
	public static void main(String args[])
	{
		int n;
		for(n = 1; n <=10; n++)
			{
				if(n % 2 == 0) /*break*/continue;
				System.out.println("n="+n);
			}
	}
}