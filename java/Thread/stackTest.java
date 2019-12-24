public class stackTest {
	public static void main(String args[]) {
		stack s = new stack();
		Runnable producer = new Producer(s);
		Runnable customer = new Customer(s);
		Thread p1 = new Thread(producer);
		Thread p2 = new Thread(producer);
		Thread p3 = new Thread(producer);
		Thread c1 = new Thread(customer);
		Thread c2 = new Thread(customer);
		p1.start();
		p2.start();
		p3.start();
		c1.start();
		c2.start();
	}
}

class Producer implements Runnable {
	stack stackOne;

	public Producer(stack s) {
		stackOne = s;
	}

	public void run() {
		String strTemp = null;
		for (int i = 0; i < 20; i++) {
			strTemp = String.valueOf(i + 1);
			stackOne.push(strTemp + " in " + Thread.currentThread().getId());
			try {
				Thread.sleep((int) (Math.random() * 100));
			} catch (InterruptedException e) {
			}
		}
	}
}

class Customer implements Runnable {
	stack stackOne;

	public Customer(stack s) {
		stackOne = s;
	}

	public void run() {
		for (int i = 0; i < 30; i++) {
			String str = stackOne.pop();
			try {
				Thread.sleep((int) (Math.random() * 100));
			} catch (InterruptedException e) {
			}
		}
	}
}

class stack {
	int sip = 0;
	String[] data = new String[6];

	public synchronized void push(String strCell) {
		while (sip == data.length) {
			try {
				this.wait();
			} catch (InterruptedException e) {
			}
		}
		data[sip] = strCell;
		sip++;
		System.out.println("push " + strCell);
		this.notify();
	}

	public synchronized String pop() {
		while (sip == 0) {
			try {
				this.wait();
			} catch (InterruptedException e) {
			}
		}
		sip--;
		this.notify();
		System.out.println("pop " + data[sip] + " in thread:" + Thread.currentThread().getId());
		return data[sip];
	}
}