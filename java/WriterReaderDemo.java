import java.io.*;
import java.util.Arrays;
public class WriterReaderDemo
{
	/* 
	*  按处理对象可以分为：字节流和字符流
	*	 字节流的基类为InputStream和OutputStream，一次处理一个字节
	*	 字符流的基类为Reader和Writer，一次处理一个字符（2个字节）
	*
	*  按数据流向可以分为：输入流和输出流
	*	 输入流的基类为InputStream和Reader
	*	 输出流的基类为OutputStream和Writer
	*
	*  直接与数据源对接的为节点流，主要有：
	*	 FileInputStream,FileOutputStream,FileReader,FileWriter 处理文件
	*	 ByteArrayInputStream,ByteArrayOutputStream,CharArrayReader,CharArrayWriter 处理数组
	*	 StringReader,StringWriter 处理字符串
	*	 PipedInputStream,PipedOutputStream,PipedReader,PipedWriter 处理管道
	*
	*  处理流和节点流一起使用，套接在节点流上，可以多层嵌套，方便处理节点流，处理流主要有：
	*	 BufferedInputStream,BufferedOutputStream,BufferedReader,BufferedWriter提供缓冲功能
	*	 InputStreamReader,OutputStreamWriter提供了字符流和字节流的转化
	*	 DataInputStream,DataOutputStream提供了基础数据类型的读写
	*
	*/
	public static void main(String[] args)
	{
		try{
			demoFileIO();

			demoStringIO();

			demoArrayIO();
			// DataInputStream dis1 = new DataInputStream(new StringBufferInputStream(s));
			// System.out.println("Get String From Dis1:" + dis1.readLine());
			
			// LineNumberInputStream li = new LineNumberInputStream(
			// 	new BufferedInputStream(
			// 	new FileInputStream(s)
			// ));
			// DataInputStream dis2 = new DataInputStream(li);
			// PrintStream ps = new PrintStream(
			// 	new FileOutputStream(args[0]));
			// String s1;
			// while(null != (s1 = dis2.readLine()))
			// 	ps.println("Line" + li.getLineNumber() + s1);
			// ps.close();
		}catch(IOException e)
		{
			e.printStackTrace();
		}
	}

	static void demoFileIO() throws IOException {
		String name ="test.txt";
		String str1 = "This is test!";

		//直接使用节点流FileWriter和FileReader读写文件
		FileWriter fw = new FileWriter(name);
		System.out.println(String.format("FileWriter write \"%s\" to File:\"%s\"...", str1, name));
		fw.write(str1);
		fw.close();
		FileReader fr = new FileReader(name);
		int c;
		System.out.println(String.format("FileReader read from File:\"%s\"...,content:", name));
		while((c = fr.read()) != -1)
			System.out.print((char)c);
		System.out.println("\n");
		fr.close();

		//处理流BufferedWriter和BufferedReader读写文件示例
		// BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(name,true)));
		BufferedWriter bw = new BufferedWriter(new FileWriter(name,true));
		System.out.println(String.format("BufferedWriter append \"%s\" to File:\"%s\"...", str1, name));
		bw.newLine();
		bw.write(str1);
		bw.close();

		String str2;
		BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(name)));
		// BufferedReader br = new BufferedReader(new FileReader(name));
		System.out.println(String.format("BufferedReader read from File:\"%s\"...,content:", name));
		while((str2 = br.readLine()) != null)
			System.out.println(str2);
		System.out.println();
		br.close();

		//处理流DataInputStream和DataOutputStream读写示例
		int[] data = {1,2,3,4};
		DataOutputStream dos = new DataOutputStream(new FileOutputStream(name));
		System.out.println(String.format("DataOutputStream write data:%s to file:%s...", Arrays.toString(data), name));
		for(int i:data) {
			dos.writeInt(i);
		}
		dos.close();

		DataInputStream dis = new DataInputStream(new FileInputStream(name));
		try {
			while((c = dis.readInt()) != -1)
				System.out.println(c);
		}catch(EOFException e) {
		}
		dis.close();
	}

	static void demoStringIO() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String s = br.readLine();
		System.out.println(s);
		
		StringReader sr = new StringReader(s);
		System.out.print("Read String by StringReader:");
		int c = 0;
		while((c = sr.read()) != -1)
			System.out.print((char)c);
		System.out.println();

		StringWriter sw = new StringWriter(20);
		sw.write(s);
		System.out.println(String.format("Write String by StringWriter:%s",sw.getBuffer()));
	}

	static void demoArrayIO() throws IOException {
		char[] data = {'a','b','3','4'};
		CharArrayReader car = new CharArrayReader(data);
		int c;
		while((c = car.read()) != -1)
			System.out.print((char)c);
		System.out.println();

		CharArrayWriter caw = new CharArrayWriter(10);
		caw.write(data);
		System.out.println(Arrays.toString(caw.toCharArray()));

		String str = "test ByteArrayInputStream";
		// ByteArrayInputStream bais = new ByteArrayInputStream(str.getBytes());
		WriterReaderDemo.myFilter bais = new myFilter(new ByteArrayInputStream(str.getBytes()));
		while((c = bais.read()) != -1)
			System.out.print((char)c);
		System.out.println();
		bais.close();

		ByteArrayOutputStream baos = new ByteArrayOutputStream(100);
		baos.write(str.getBytes());
		System.out.println(baos.toString());
	}

	static void demoFilterUsage() {
		
	}

	//自定义filter类，完成自动转化所有小写转化成大写字母
	static class myFilter extends FilterInputStream {
		public myFilter(InputStream fr) {
			super(fr);
		}

		@Override
		public int read() throws IOException {
			int r = in.read();
			if(Character.isLowerCase((char)r))
				r = Character.toUpperCase((char)r);
			return r;
		}
	}
}
