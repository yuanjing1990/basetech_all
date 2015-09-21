import java.io.*;
import java.util.*;
import yj.tools;
public class Test
{
	public static void main(String args[])
	{
		System.out.println("Hello World!");
		Config c1 = new Config1(args[0]);
		c1.print();
		Config c2 = new Config2(args[0]);
		c2.print();
		Config c3 = new Config3(args[0]);
		c3.print();
	}
}
abstract class Config
{
	protected Map<String,String> m_item = new HashMap<String,String>();
	public void print()
	{
		Set<String> s = m_item.keySet();
		Iterator<String> it = s.iterator();
		while(it.hasNext())
		{
			String str = it.next();
//			System.out.println(str + ":" + m_item.get(str));
			tools.prtln(str + ":" + m_item.get(str));
		}
	}
}
class Config1 extends Config
{
	public Config1(String filename)
	{
		try{
		DataInputStream dis = new DataInputStream(
				new BufferedInputStream(
				new FileInputStream(filename)
			));
			String str;
			while((str = dis.readLine()) != null)
			{
				StringTokenizer st = new StringTokenizer(str," ");
				super.m_item.put((String)st.nextElement(),(String)st.nextElement());
			}
		}catch(FileNotFoundException e)
		{
			System.out.println("File Not Found:" + filename);
		}catch(IOException e)
		{
			System.out.println("IO Error!");
		}
	}
	public void print()
	{
		tools.prtln("Config1 Print:");
		tools.prtln("");
		super.print();
	}
}
class Config2 extends Config
{
	public Config2(String filename)
	{
//		InFile dis = new InFile(filename);
//		String str;
//		while((str = dis.readLine()) != null)
//		{
//			StringTokenizer st = new StringTokenizer(str," ");
//			super.m_item.put((String)st.nextElement(),(String)st.nextElement());
//		}
		try{
			BufferedReader in = new BufferedReader(
				new InputStreamReader(
				new FileInputStream(filename)));
			String str;
			while((str = in.readLine()) != null)
			{
				StringTokenizer s = new StringTokenizer(str," ");
				tools.prtln(s.nextToken() + ":" + s.nextToken());
			}
		}catch(FileNotFoundException e)
		{
			tools.prtln("File Not Found:" + filename);
		}catch(IOException e)
		{
			tools.prtln("IO Error!");
		}
	}
	public void print()
	{
		tools.prtln("Config2 Print:");
		tools.prtln("");
		super.print();
	}
}
class Config3 extends Config
{
	public Config3(String filename)
	{
		try{
			BufferedReader in = new BufferedReader(
				new FileReader(filename));
			String str;
			while((str = in.readLine()) != null)
			{
				StringTokenizer s = new StringTokenizer(str," ");
				tools.prtln(s.nextToken() + ":" + s.nextToken());
			}
		}catch(FileNotFoundException e)
		{
			tools.prtln("File Not Found:" + filename);
		}catch(IOException e)
		{
			tools.prtln("IO Error!");
		}
	}
	public void print()
	{
		tools.prtln("Config3 Print:");
		tools.prtln("");
		super.print();
	}
}