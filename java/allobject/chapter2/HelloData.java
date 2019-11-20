package allobject.chapter2;

import java.util.*;

public class HelloData {
	public static void main(final String args[]) {
		System.out.println(new Date());
		System.out.println("Hello World!");
		final Properties p = System.getProperties();
		p.list(System.out);
		System.out.println("---------Memory Usage:");
		final Runtime rt = Runtime.getRuntime();
		System.out.println("Total Memory = " + rt.totalMemory() + "Free Memory = " + rt.freeMemory());
	}
}