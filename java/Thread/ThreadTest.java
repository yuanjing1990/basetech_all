public class ThreadTest
{
	public static void main(String args[])
	{
		Thread t1 = new subThread("First");
		Thread t2 = new subThread("Second");
		t1.start();
		t2.start();
	}
}
class subThread extends Thread
{
	public subThread(String str)
	{
		super(str);
	}
	public void run()
	{
		for(int i = 0; i < 10; i++)
			{
				System.out.println(i + " " + getName());
				try
				{
					sleep((int)(Math.random()*1000));
				}
				catch(InterruptedException e){}
			}
			System.out.println("Finish:"+getName());
	}
}
