import java.io.*;
public class ExciseIO {
	public static void main(String[] args) {
		praticeKeybdIO(args);
	}

	//从标准输入读取字符，直到读到‘q’结束读取
	static void praticeKeybdIO(String[] args) {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		do{
			try{
				char c = (char)br.read();
				if(c == 'q')
					return;
			}catch(IOException e){
				e.printStackTrace();
			}
		}while(true);
	}
}
