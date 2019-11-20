package allobject.chapter10;

import java.io.*;

public class iostream {
	public static void main(String args[]) {
		BufferedInputStream bis = new BufferedInputStream(System.in);
		// int c = 0;
		// while(true)
		// {
		// c = sbis.read();
		// if(c == -1)
		// break;
		// System.out.println((char)c);
		// }
		try {
			System.out.println(bis.read());
		} catch (IOException e) {
			System.out.println("IOException");
		}
	}
};