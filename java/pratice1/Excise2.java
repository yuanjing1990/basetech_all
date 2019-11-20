package pratice1;

import java.io.*;
import java.util.*;

public class Excise2 {
	public static void main(String[] args) {
		try {
			BufferedReader br = new BufferedReader(new FileReader(args[0]));
			Vector<String> vec = new Vector<String>();
			String tmp;
			while (null != (tmp = br.readLine())) {
				vec.add(tmp);
			}
			PrintWriter bw = new PrintWriter(new BufferedWriter(new FileWriter(args[1])));
			for (int i = 0; i < vec.size(); ++i) {
				bw.println(vec.get(i));
				System.out.println(vec.get(i));
			}
			bw.close();
			br.close();
			// System.out.println("Main");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}