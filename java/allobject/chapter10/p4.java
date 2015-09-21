import java.io.*;
public class p4
{
	public static void main(String[] args)
	{
		System.out.println("Hello World!");
		try{
			DataInputStream dis = new DataInputStream(
				new BufferedInputStream(
				new FileInputStream(args[0])));
			//File f = new File(args[0]);
			DataOutputStream dos = new DataOutputStream(
				new BufferedOutputStream(
				new FileOutputStream(args[1])));
			String str;
			while((str=dis.readLine()) != null)
			{
				if(str.indexOf(args[0])
				dos.writeBytes(str + "\n");
				System.out.println(str);
			}
			dos.close();
			
		}catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}