import java.io.*;
import java.util.*;
public class Excise1
{
	public static void main(String[] args)
	{
		try{
			LineNumberInputStream li = new LineNumberInputStream(
				new BufferedInputStream(
				new FileInputStream(args[0])));
			DataInputStream dis = new DataInputStream(
				li);
			Vector vec = new Vector();
//			DataOutputStream dos = new DataOutputStream(
//				new BufferedOutputStream(
//				new FileOutputStream(args[1])));
			PrintStream ps = new PrintStream(
				new FileOutputStream(args[1])
			);
			String tmp;
			while(null != (tmp = dis.readLine()))
				vec.add(tmp.toUpperCase());
			for(int i = 0; i < vec.size(); ++i)
			{
				String t = vec.get(i).toString();
				if(t.indexOf(args[1]) != -1)
					System.out.println("Line" + Integer.toString(i+1) + vec.get(i));
				//ps.println("Line" + Integer.toString(i+1) + vec.get(i));
			}
			//System.out.println("Hello World!");
		}catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}