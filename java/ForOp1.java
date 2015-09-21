public class ForOp1
{
	public static void main(String args[])
	{
		int n;
		long result;
		for(n = 10, result = 1; n > 0; n--)
			result *= n;
		System.out.println("10! = "+result);
	}
}