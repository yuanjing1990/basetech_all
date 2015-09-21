class Circle
{
public Circle(){System.out.println("Create Circle!");}
}
class Rect
{
	static {
		System.out.println("Rect Loading...");
	}
	public static void main(String[] argv)
	{
		System.out.println("Rect Main");
	}
}
public class review
{
	static{
		Circle cr = new Circle();
		System.out.println("Before Main...");
	}
	public static void main(String[] argv)
	{
		System.out.println("Hello World");
	}
}