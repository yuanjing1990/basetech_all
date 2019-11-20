package pratice1;

import java.io.*;
import java.util.*;

public class Excise1 {
	public static void main(String[] args) {
		try {
			BufferedReader dis = new BufferedReader(new FileReader(args[0]));
			ArrayList<String> vec = new ArrayList<>();
			// DataOutputStream dos = new DataOutputStream(
			// new BufferedOutputStream(
			// new FileOutputStream(args[1])));
			PrintStream ps = new PrintStream(new FileOutputStream(args[1]));
			String tmp;
			while (null != (tmp = dis.readLine()))
				vec.add(tmp.toUpperCase());
			for (int i = 0; i < vec.size(); ++i) {
				String t = vec.get(i).toString();
				if (t.indexOf(args[1]) != -1)
					System.out.println("Line" + Integer.toString(i + 1) + vec.get(i));
				// ps.println("Line" + Integer.toString(i+1) + vec.get(i));
			}
			// System.out.println("Hello World!");
			dis.close();
			ps.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}