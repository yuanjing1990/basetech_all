public class ForOp2
{
	public static void main(String args[])
	{
		int i,j,k;
		System.out.println("i	j	k");
		for(i = 0; i < 2; i++)
			for(j = 0; j < 2; j++)
				for(k = 0; k< 2; k++)
					{
						System.out.println(i+"	"+j+"	"+k);
						System.out.println();
					}
	}
}