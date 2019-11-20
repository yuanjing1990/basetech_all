package allobject.chapter2;

public class excise1 {
	public static void main(String args[]) {
		Test t = new Test();
		System.out.println("Test.a:" + t.a);
		System.out.println("Test.b:" + t.b);
	}
}

class Test {
	int a;
	char b;
}