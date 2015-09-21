public class stackTest
{
	public static void main(String args[])
	{
		stack s = new stack();
		Runnable producer = new Producer(s);
		Runnable customer = new Customer(s);
		Thread p = new Thread(producer);
		Thread c = new Thread(customer);
		p.start();
		c.start();
	}
}
class Producer implements Runnable
{
	stack stackOne;
	public Producer(stack s)
	{
		stackOne = s;
	}
	public void run()
	{
		String strTemp = null;
		for(int i = 0; i < 20; i++)
		{
			strTemp = String.valueOf(i+1);
			stackOne.push(strTemp);
			System.out.println("Produce:"+i);
			try
			{
				Thread.sleep((int)(Math.random()*100));
			}
			catch(InterruptedException e){}
		}
	}
}
class Customer implements Runnable
{
	stack stackOne;
	public Customer(stack s)
	{
		stackOne = s;
	}
	public void run()
	{
		String strTemp = null;
		for(int i = 0; i < 20; i++)
		{
			strTemp = stackOne.pop();
			System.out.println("Customer:"+i);
			try
			{
				Thread.sleep((int)(Math.random()*100));
			}
			catch(InterruptedException e){}
		}
	}
}
class stack
{
	int sip = 0;
	String[] data = new String[6];
	public synchronized void push(String strCell)
	{
		while(sip == data.length)
		{
			try
			{
				this.wait();
			}
			catch(InterruptedException e){}
		}
		this.notify();
		data[sip] = strCell;
		sip++;
	}
	public synchronized String pop()
	{
		while(sip == 0)
		{
			try
			{
				this.wait();
			}
			catch(InterruptedException e){}
		}
		this.notify();
		sip--;
		return data[sip];
	}
}