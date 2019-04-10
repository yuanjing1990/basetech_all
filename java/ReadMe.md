# Java Pratice

[TOC]

## JavaIO (WriterReaderDemo.java)
### 总览
![IO类结构](http://www.runoob.com/wp-content/uploads/2013/12/iostream2xx.png "io class")

- 按处理对象可以分为：`字节流`和`字符流`
 	- `字节流`的基类为`InputStream`和`OutputStream`，一次处理一个字节
    - `字符流`的基类为`Reader`和`Writer`，一次处理一个字符（2个字节）

- 按数据流向可以分为：`输入流`和`输出流`
	- `输入流`的基类为`InputStream`和`Reader`
	- `输出流`的基类为`OutputStream`和`Writer`

- 直接与数据源对接的为`节点流`，主要有：
	- `FileInputStream`,`FileOutputStream`,`FileReader`,`FileWriter` 处理文件
	- `ByteArrayInputStream`,`ByteArrayOutputStream`,`CharArrayReader`,`CharArrayWriter` 处理数组
	- `StringReader`,`StringWriter` 处理字符串
	- `PipedInputStream`,`PipedOutputStream`,`PipedReader`,`PipedWriter` 处理管道

- `处理流`和`节点流`一起使用，套接在节点流上，可以多层嵌套，方便处理节点流，`处理流`主要有：
	- `BufferedInputStream`,`BufferedOutputStream`,`BufferedReader`,`BufferedWriter` 提供缓冲功能
	- `InputStreamReader`,`OutputStreamWriter` 提供了字符流和字节流的转化
	- `DataInputStream`,`DataOutputStream` 提供了基础数据类型的读写

### 实例
 - Java IO库在java.io包内，使用下面的方法引入：
```Java
	import java.io.*;
```

#### 文件读写
```Java
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
```
#### 字符串读写
```Java
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
```
#### 数组读写
```Java
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
```

## 外部类和内部类的访问 (Outer.java)
### 概述
在定义内部类时常会遇到访问问题，比如静态方法访问内部类、非静态方法访问非静态的内部类等等情况，这里作个总结

- 非静态内部类中无法定义静态方法

- 静态方法中无法直接使用非静态的内部类

### 实例
#### 外部类的静态方法访问非静态内部类
```Java
// 静态方法中无法直接使用非静态的内部类
// public static Inner StaticGetInner(String str)
// {
// 	return new Inner(str);
// }
public static Inner StaticGetInner(String str)
{
	Outer outer = new Outer("StaticGetInner");
	Outer.Inner inner = outer.new Inner("StaticGetInner");
	return inner;
}
```
#### 外部类的非静态方法访问非静态内部类
```Java
public Inner GetInner(String str)
{
	return new Inner(str);
}
```
#### 外部类的静态方法访问静态内部类
```Java
public static StaticInner StaticGetStaticInner(String str)
{
	return new StaticInner(str);
}
```
#### 外部类的非静态方法访问静态内部类
```Java
public StaticInner GetStaticInner(String str)
{
	return new StaticInner(str);
}
```
#### 非静态内部类访问外部类非静态和静态方法
```Java
class Inner
{
Inner(String str)
{
	System.out.println("Create Inner Class "+str);
}
void innerNonStaticMethod()
{
	System.out.println("call innerNonStaticMethod ...");
	GetInner("innerNonStaticMethod");
	StaticGetInner("innerNonStaticMethod");
}
// 非静态内部类中无法定义静态方法
// public static void innerStaticMethod() {
// 	System.out.println("call innerStaticMethod ...");
// }
}
```
#### 静态内部类访问外部类非静态和静态方法
```Java
static class StaticInner {
	StaticInner(String str) {
		System.out.println("Create StaticInner Class "+str);
	}
	void staticInnerNonStaticMethod() {
		System.out.println("call staticInnerNonStaticMethod ...");
		//静态内部类无法直接使用外部类的非静态方法
		// GetInner("staticInnerNonStaticMethod");
		Outer outer = new Outer("staticInnerNonStaticMethod");
		outer.GetInner("staticInnerNonStaticMethod");
		StaticGetInner("staticInnerNonStaticMethod");
	}
	public static void staticInnerStaticMethod() {
		System.out.println("call staticInnerStaticMethod ...");
		//静态内部类无法直接使用外部类的非静态方法
		// GetInner("staticInnerStaticMethod");
		Outer outer = new Outer("staticInnerStaticMethod");
		outer.GetInner("staticInnerStaticMethod");
		StaticGetInner("staticInnerStaticMethod");
	}
}
```

