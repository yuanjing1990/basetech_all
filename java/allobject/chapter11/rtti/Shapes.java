package allobject.chapter11.rtti;

import java.util.*;

interface Shape {
	void draw();
}

class Circle implements Shape {
	public void draw() {
		System.out.println("Circle.draw()");
	}
}

class Square implements Shape {
	public void draw() {
		System.out.println("Square.draw()");
	}
}

class Triangle implements Shape {
	public void draw() {
		System.out.println("Trangle.draw()");
	}
}

public class Shapes {
	public static void main(String[] args) {
		ArrayList<Shape> s = new ArrayList<>();
		s.add(new Circle());
		s.add(new Square());
		s.add(new Triangle());
		Iterator<Shape> it = s.iterator();
		while (it.hasNext()) {
			try {
				Shape sp = (Shape) it.next();
				sp.draw();
				System.out.println(sp.getClass().getSuperclass().toString());
			} catch (Exception ec) {
				ec.printStackTrace();
				System.out.println("Translater Error!");
			}
		}
	}
}