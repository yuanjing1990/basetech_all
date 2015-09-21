import java.util.*;
interface shape
{
	void draw();
}
class circle implements shape
{
	static {
		System.out.println("Circle Loading!");
	}
	public void draw(){
		System.out.println("Circle Draw!");
	}
}
class rectangle implements shape
{
	static {
		System.out.println("Rectangle Loading!");
	}
	public void draw(){
		System.out.println("Rectangle Draw!");
	}
}
public class shapes
{
	public static void main(String[] argv)
	{
		try{
			circle s = circle.class.newInstance();
			if(rectangle.class.isInstance(s))
				System.out.println("S is instance of circle");
			s.draw();
			System.out.println(circle.class.getClass().toString());
		}catch(InstantiationException e){
		}catch(IllegalAccessException e){
		}
//		System.out.println("inside main");
//		new circle();
//		System.out.println("After creating circle!");
//		new rectangle();
//		System.out.println("After creating rectangle!");
//		try{
//			Class.forName("rectangle");
//		}catch(ClassNotFoundException e){
//			e.printStackTrace();
//		}
//		System.out.println("After Class.forName(\"rectangle!\")");
//		Vector s = new Vector();
//		s.addElement(new circle());
//		s.addElement(new rectangle());
//		Enumeration e = s.elements();
//		while(e.hasMoreElements())
//			((shape)e.nextElement()).draw();
//		System.out.println("Hello World!");
	}
}