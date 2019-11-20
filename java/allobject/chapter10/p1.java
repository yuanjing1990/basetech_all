package allobject.chapter10;

import java.io.*;
import java.util.*;

public class p1 {
	public static void main(String[] args) {
		try {
			BufferedReader br = new BufferedReader(new FileReader(args[0]));
			String str;
			ArrayList<String> v = new ArrayList<>();
			while ((str = br.readLine()) != null) {
				v.add(str);
			}
			br.close();
			int i = v.size();
			while (i-- > 0)
				System.out.println((String) v.get(i));
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}