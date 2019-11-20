package allobject.chapter10;

import java.io.*;

public class p4 {
	public static void main(String[] args) {
		System.out.println("Hello World!");
		try {
			BufferedReader br = new BufferedReader(new FileReader(args[0]));
			BufferedWriter bw = new BufferedWriter(new FileWriter(args[1]));
			String str;
			while ((str = br.readLine()) != null) {
				if (str.indexOf(args[0]) != 0) {
					bw.write(str);
				}
				System.out.println(str);
			}
			br.close();
			bw.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}