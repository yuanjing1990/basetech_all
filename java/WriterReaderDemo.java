import java.io.*;
public class WriterReaderDemo
{
	public static void main(String[] args)
	{
		try{
			DataInputStream dis = new DataInputStream(System.in);
			String s = dis.readLine();
			System.out.println(s);
			
			StringBufferInputStream sbis = new StringBufferInputStream(s);
			System.out.print("Get String From sbis:");
			int c = 0;
			while((c = sbis.read()) != -1)
				System.out.print((char)c);
			System.out.print("\n");
			
			DataInputStream dis1 = new DataInputStream(
				new StringBufferInputStream(s));
			System.out.println("Get String From Dis1:" + dis1.readLine());
			
			LineNumberInputStream li = new LineNumberInputStream(
				new BufferedInputStream(
				new FileInputStream(s)
			));
			DataInputStream dis2 = new DataInputStream(li);
			PrintStream ps = new PrintStream(
				new FileOutputStream(args[0]));
			String s1;
			while(null != (s1 = dis2.readLine()))
				ps.println("Line" + li.getLineNumber() + s1);
			ps.close();
		}catch(IOException e)
		{
			e.printStackTrace();
		}
	}
}