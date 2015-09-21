import java.io.*;
import java.util.*;
public class p3
{
	public static void main(String[] args)
	{
		try{
			LineNumberInputStream li = new LineNumberInputStream(
				new BufferedInputStream(
				new FileInputStream(args[0])));
			DataInput id = new DataInputStream(li);
				
			BufferedOutputStream db = new BufferedOutputStream(
				new FileOutputStream(args[1]));
			DataOutput od = new DataOutputStream(db);
			String str = id.readLine();
			Vector v = new Vector();
			while(str != null)
			{
				System.out.println(str);
				str = "Line "+ li.getLineNumber() + " " + str + "\n";
				v.add(str);
				//od.writeBytes("Line "+ li.getLineNumber() + " " + str + "\n");
				str = id.readLine();
			}
			int i = 0;
			Iterator it = v.iterator();
			while(i < v.size())
				System.out.print(((String)v.get(i++)).toUpperCase());
			while(it.hasNext())
			{
				String temp = (String)it.next();
				if(temp.indexOf(args[2]) != -1)
					System.out.print(temp);
			}
			db.flush();
		}catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}