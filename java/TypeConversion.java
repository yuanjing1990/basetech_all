public class TypeConversion
{
	public static void main(String args[])
	{
		char a = 1;
		byte b = 2;
		short c = 3;
		int d = 4;
		byte e;
		e = (byte)(a + b + c + d);
		short f;
		f = (short)(a + b + c + d);
		int g;
		g = a + b + c + d;
		double i;
		i = a + b + c + d;
		System.out.println("e = "+e);
		System.out.println("f = "+f);
		System.out.println("g = "+g);
		System.out.println("i = "+i);
	}
}