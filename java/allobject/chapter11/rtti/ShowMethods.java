package allobject.chapter11.rtti;

import java.lang.reflect.*;
import java.util.*;

public class ShowMethods {
	static final String usage = "usage:\n"
		    + "ShowMethods qulified class name \n"
			+ "To show all methods in class or :\n"
			+ "ShowMethods qualified class name word\n"
			+ "To search for methods involving 'word'";

	public static void main(String[] args) {
		if (args.length < 1) {
			System.out.println(usage);
			System.exit(0);
		}
		try {
			Class<?> c = Class.forName(args[0]);
			Method[] m = c.getMethods();
			Constructor<?>[] ctor = c.getConstructors();
			if (args.length == 1) {
				for (int i = 0; i < ctor.length; ++i)
					// System.out.println(StringQualifiers.strip(ctor[i].toString()));
					System.out.println(ctor[i].toString());
				for (int i = 0; i < m.length; ++i)
					// System.out.println(StringQualifiers.strip(m[i].toString()));
					System.out.println(m[i].toString());
			} else {
				for (int i = 0; i < m.length; ++i)
					if (m[i].toString().indexOf(args[1]) != -1)
						System.out.println(StringQualifiers.strip(m[i].toString()));
				// System.out.println(m[i].toString());
				for (int i = 0; i < ctor.length; ++i)
					if (ctor[i].toString().indexOf(args[1]) != -1)
						System.out.println(StringQualifiers.strip(ctor[i].toString()));
				// System.out.println(ctor[i].toString());
			}
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}
}

class StringQualifiers {
	private StringTokenizer st;

	public StringQualifiers(String qualified) {
		st = new StringTokenizer(qualified, " ,()");
	}

	public String strip() {
		String s = "", si;
		try {
			while (st.hasMoreTokens()) {
				si = st.nextToken();
				int i = si.lastIndexOf('.');
				if (i != -1)
					si = si.substring(i + 1);
				s += " " + si;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return s;
	}

	public static String strip(String qualified) {
		StringQualifiers sq = new StringQualifiers(qualified);
		return sq.strip();
	}
}