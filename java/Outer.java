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
		void ShowOuterInfo()
		{
			System.out.println("Outer Class Is "+ m_str);
		}
	}
	public Inner GetInner(String str)
	{
		return new Inner(str);
	}
	public static void main(String argv[])
	{
		Outer outer = new Outer("Father");
		Outer.Inner inner = outer.GetInner("Test");
		inner.ShowOuterInfo();
	}
}