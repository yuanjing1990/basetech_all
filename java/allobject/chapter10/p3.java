package allobject.chapter10;

import java.io.*;
import java.util.*;

public class p3 {
	public static void main(String[] args) {
		try {
			LineNumberReader lr = new LineNumberReader(new FileReader(args[0]));
			BufferedReader br = new BufferedReader(lr);

			BufferedOutputStream db = new BufferedOutputStream(new FileOutputStream(args[1]));
			String str = br.readLine();
			ArrayList<String> v = new ArrayList<>();
			while (str != null) {
				System.out.println(str);
				str = "Line " + lr.getLineNumber() + " " + str + "\n";
				v.add(str);
				str = br.readLine();
			}
			br.close();
			int i = 0;
			Iterator<String> it = v.iterator();
			while (i < v.size())
				System.out.print(((String) v.get(i++)).toUpperCase());
			while (it.hasNext()) {
				String temp = (String) it.next();
				if (temp.indexOf(args[2]) != -1)
					System.out.print(temp);
			}
			db.flush();
			db.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}