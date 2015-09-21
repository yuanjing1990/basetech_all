import java.util.*;
interface Shape
{
	void draw();
}
class Circle implements Shape
{
	public void draw()
	{
		System.out.println("Circle.draw()");
	}
}
class Square implements Shape
{
	public void draw()
	{
		System.out.println("Square.draw()");
	}
}
class Triangle implements Shape
{
	public void draw()
	{
		System.out.println("Trangle.draw()");
	}
}
public class Shapes
{
	public static void main(String[] args)
	{
		Vector s = new Vector();
		s.addElement(new Circle());
		s.addElement(new Square());
		s.addElement(new Triangle());
		Enumeration e = s.elements();
		while(e.hasMoreElements())
		{
			try{
				Shape sp = (Shape)e.nextElement();
				sp.draw();
				System.out.println(sp.getClass().getSuperclass().toString());
			}
			catch(Exception ec)
			{
				ec.printStackTrace();
				System.out.println("Translater Error!");
			}
			
		}
	}
}