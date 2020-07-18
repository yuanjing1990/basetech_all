package Thread;

public class ThreadSync {
    public static int count = 0;
    public static final int MAX_COUNT = 100;

    public static void main(String[] args) {
        // testVolatile();
        testWait();
    }

    public static void testVolatile() {
        Thread t1 = new Thread() {
            @Override
            public void run() {
                while (count < MAX_COUNT) {
                    System.out.println("Thread1 count:" + count++);
                }
            }
        };
        Thread t2 = new Thread() {
            @Override
            public void run() {
                while (count < MAX_COUNT) {
                    System.out.println("Thread2 count:" + count++);
                }
            }
        };
        t1.start();
        t2.start();
    }

    public static void testWait() {
        Thread t1 = new Thread() {
            @Override
            public void run() {
                try {
                    wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };
        t1.start();
        System.out.print("Wait 10s:");
        for (int i = 0; i < 10; ++i) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.print(".");
        }
        System.out.println();
    }
}
