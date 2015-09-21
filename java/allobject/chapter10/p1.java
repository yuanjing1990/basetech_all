import java.io.*;
import java.util.*;
public class p1
{
	public static void main(String[] args)
	{
		try{
			DataInput dis = new DataInputStream(
				new BufferedInputStream(
				new FileInputStream(args[0])));
			String str;
			Vector v = new Vector();
			while((str = dis.readLine())!=null)
			{
				v.add(str);
			}
			int i = v.size();
			while(i-- > 0)
				System.out.println((String)v.get(i));
		}catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}