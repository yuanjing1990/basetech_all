package allobject.chapter10;

import java.io.*;
import java.util.*;

public class Config {
	public Map<String, String> m_item = new HashMap<String, String>();

	public Config(String file) {
		try {
			FileInputStream fis = new FileInputStream(file);
			BufferedInputStream bis = new BufferedInputStream(fis);
			DataInputStream dis = new DataInputStream(bis);
			BufferedReader br = new BufferedReader(new InputStreamReader(dis));
			String s;
			while ((s = br.readLine()) != null) {
				StringTokenizer st = new StringTokenizer(s, " ");
				m_item.put((String) st.nextElement(), (String) st.nextElement());
			}
			br.close();
		} catch (FileNotFoundException e) {
			System.out.println("File Not Found:" + file);
		} catch (IOException e) {
			System.out.println("File End!");
		}
	}

	public static void main(String args[]) {
		Config config = new Config(args[0]);
		Map<String, String> m = config.m_item;
		Set<String> s = m.keySet();
		Iterator<String> it = s.iterator();
		while (it.hasNext()) {
			String str = (String) it.next();
			System.out.println(str + ":" + m.get(str));
		}
	}
}
