public class Outer
{
	private String m_str;
	Outer(String str)
	{
		m_str = str;
	}
	class Inner
	{
		Inner(String str)
		{
			System.out.println("Create Inner Class "+str);
		}
		void innerNonStaticMethod()
		{
			System.out.println("call innerNonStaticMethod ...");
			GetInner("innerNonStaticMethod");
			StaticGetInner("innerNonStaticMethod");
		}
		// 非静态内部类中无法定义静态方法
		// public static void innerStaticMethod() {
		// 	System.out.println("call innerStaticMethod ...");
		// }
	}
	static class StaticInner {
		StaticInner(String str) {
			System.out.println("Create StaticInner Class "+str);
		}
		void staticInnerNonStaticMethod() {
			System.out.println("call staticInnerNonStaticMethod ...");
			//静态内部类无法直接使用外部类的非静态方法
			// GetInner("staticInnerNonStaticMethod");
			Outer outer = new Outer("staticInnerNonStaticMethod");
			outer.GetInner("staticInnerNonStaticMethod");
			StaticGetInner("staticInnerNonStaticMethod");
		}
		public static void staticInnerStaticMethod() {
			System.out.println("call staticInnerStaticMethod ...");
			//静态内部类无法直接使用外部类的非静态方法
			// GetInner("staticInnerStaticMethod");
			Outer outer = new Outer("staticInnerStaticMethod");
			outer.GetInner("staticInnerStaticMethod");
			StaticGetInner("staticInnerStaticMethod");
		}
	}
	public Inner GetInner(String str)
	{
		System.out.println("call GetInner ...");
		return new Inner(str);
	}
	public StaticInner GetStaticInner(String str)
	{
		System.out.println("call GetStaticInner ...");
		return new StaticInner(str);
	}

	// 静态方法中无法直接使用非静态的内部类
	// public static Inner StaticGetInner(String str)
	// {
	// 	return new Inner(str);
	// }
	public static Inner StaticGetInner(String str)
	{
		System.out.println("call StaticGetInner ...");
		Outer outer = new Outer("StaticGetInner");
		Outer.Inner inner = outer.new Inner("StaticGetInner");
		return inner;
	}
	public static StaticInner StaticGetStaticInner(String str)
	{
		System.out.println("call StaticGetStaticInner ...");
		return new StaticInner(str);
	}

	public static void main(String argv[])
	{
		Inner inner = Outer.StaticGetInner("StaticGetInner");
		inner.innerNonStaticMethod();
	}
}