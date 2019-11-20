package Thread;

import java.util.concurrent.*;
import java.util.concurrent.atomic.*;

public class ThreadTest
{
	public AtomicInteger cntProduct = new AtomicInteger(0);
	public static ThreadTest thdTest = new ThreadTest();
	public static void main(String args[])
	{
		thdTest.cntProduct.set(0);
		ExecutorService pool = Executors.newFixedThreadPool(5);
		pool.execute(thdTest.new Consumer(1));
		pool.execute(thdTest.new Consumer(2));
		pool.execute(thdTest.new Consumer(3));
		pool.execute(thdTest.new Productor(1));
		pool.execute(thdTest.new Productor(2));
		pool.shutdown();
	}
	class Consumer implements Runnable {
		int mId;
		public Consumer(int id) {
			mId = id;
		}
		public void run() {
			while(true) {
				try{
					Thread.sleep(2000);
				}catch(InterruptedException e) {
					e.printStackTrace();
				}
				synchronized(cntProduct) {
					if(cntProduct.intValue() == 0) {
						try {
							System.out.println(String.format("Consume%d have no product,wait...",mId));
							cntProduct.wait();
						}catch(InterruptedException e) {
							e.printStackTrace();
						}
						continue;
					}
					cntProduct.decrementAndGet();
					System.out.println(String.format("Consume%d a product,left product number:%d",mId,cntProduct.intValue()));
				}
			}
		}
	}
	class Productor implements Runnable {
		int mId;
		public Productor(int id) {
			mId = id;
		}
		public void run() {
			while(true) {
				try{
					Thread.sleep(1000);
					if(cntProduct.intValue() >= 10)
						Thread.sleep(20000);
				}catch(InterruptedException e) {
					e.printStackTrace();
				}
				synchronized(cntProduct) {
					cntProduct.incrementAndGet();
					cntProduct.notifyAll();
					System.out.println(String.format("Product%d a product,left product number:%d",mId,cntProduct.intValue()));
				}
			}
		}
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
