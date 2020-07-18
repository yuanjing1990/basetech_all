package Thread;

import java.util.concurrent.TimeUnit;
import java.util.*;

public class Priority {
    private static volatile boolean notStart = true;
    private static volatile boolean notEnd = true;

    public static void main(String[] args) {
        ArrayList<Job> jobs = new ArrayList<Job>();
        for (int i = 0; i < 10; ++i) {
            int priority = i < 5 ? Thread.MIN_PRIORITY : Thread.MAX_PRIORITY;
            Job job = new Job(priority);
            jobs.add(job);
            Thread thread = new Thread(job, "Thread:" + i);
            thread.setPriority(priority);
            thread.start();
        }
        System.out.println(Thread.currentThread().getId());
        notStart = false;
        try {
            TimeUnit.SECONDS.sleep(10);
        } catch (InterruptedException e) {
        }
        notEnd = false;
        for (Job job : jobs) {
            System.out.println("Job Priority : " + job.priority + ", Count : " + job.jobCount);
        }
    }

    static class Job implements Runnable {
        private int priority;
        private long jobCount;

        public Job(int priority) {
            this.priority = priority;
        }

        public void run() {
            while (notStart) {
                Thread.yield();
            }
            while (notEnd) {
                Thread.yield();
                jobCount++;
            }
        }
    }
}