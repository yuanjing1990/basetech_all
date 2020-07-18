package Thread;

import java.util.concurrent.*;
import java.util.concurrent.atomic.*;
import java.util.ArrayList;

public class ThreadTest {
    public AtomicInteger cntProduct = new AtomicInteger(0);
    public static ThreadTest thdTest = new ThreadTest();

    public static void main(String args[]) {
        thdTest.testProductor_Consumer();
    }

    public void testProductor_Consumer() {
        ExecutorService pool = Executors.newFixedThreadPool(5);
        pool.execute(thdTest.new Consumer(1));
        pool.execute(thdTest.new Consumer(2));
        pool.execute(thdTest.new Consumer(3));
        pool.execute(thdTest.new Productor(1));
        pool.execute(thdTest.new Productor(2));
        pool.shutdown();
    }

    // 生产者消费者模型：
    // 有一个共同的仓库，生产者每次想仓库中放进一个元素，消费者每次从仓库中拿出一个货物。 但是放元素时仓库的容量是有限的，取货物时仓库为空不能取。
    public ArrayList<String> productArray = new ArrayList<>();

    class Consumer implements Runnable {
        int mId;

        public Consumer(int id) {
            mId = id;
        }

        public void run() {
            while (true) {
                synchronized (productArray) {
                    if (productArray.size() == 0) {
                        try {
                            System.out.println(String.format("Consumer %d have no product to use, wait...", mId));
                            productArray.wait();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }

                    // productArray.size() may be 0 here
                    if (productArray.size() != 0) {
                        String elem = productArray.remove(productArray.size() - 1);
                        System.out.println(String.format("Consumer %d use a product %s", mId, elem));
                    }
                }
            }
        }
    }

    class Productor implements Runnable {
        int mId;
        int mCnt;

        public Productor(int id) {
            mId = id;
        }

        public void run() {
            while (true) {
                String product = String.format("Product(%d,%d)", mId, mCnt++);
                synchronized (productArray) {
                    productArray.add(product);
                    productArray.notifyAll();
                    System.out.println(String.format("Productor %d a product:%s", mId, product));
                }
                try {
                    Thread.sleep((int) (Math.random() * 1000.0));
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}

class subThread extends Thread {
    public subThread(String str) {
        super(str);
    }

    public void run() {
        for (int i = 0; i < 10; i++) {
            System.out.println(i + " " + getName());
            try {
                sleep((int) (Math.random() * 1000));
            } catch (InterruptedException e) {
            }
        }
        System.out.println("Finish:" + getName());
    }
}
