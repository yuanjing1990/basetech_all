class Valument
{
	boolean a;
	char b;
	byte c;
	short d;
	int e;
	long f;
	float g;
	double h;
	void print()
	{
		System.out.println("Data type	Initial value");
		System.out.println("boolean		 " + a);
		System.out.println("char		 " + b);
		System.out.println("byte		 " + c);
		System.out.println("short		 " + d);
		System.out.println("int 		 " + e);
		System.out.println("long		 " + f);
		System.out.println("float		 " + g);
		System.out.println("double		 " + h);
	}
}
public class InitVal
{
	public static void main(String[] args)
	{
		Valument value = new Valument();
		value.print();
	}
}
