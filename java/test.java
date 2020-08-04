import java.util.logging.Logger;

/**The first Thinking in Java example program.
*Lists system information on current machine.
*@author Bruce Eckel
*@author http://www.BruceEckel.com
*@version 1.0
*/

public class test{
/**Sole entry point to class & application
*@param args array of string arguments
*@return No return value
*@exception exceptions No exceptions thrown
*/
	public test(){
		System.out.println("Hello World.");
		Logger.getGlobal().log("Test");
	}
	public test(String str){
		System.out.println(str);
	}
	public static void main(String[] args){
		new test();
		new test("This is a test");
		test[] t_vec = new test[4];
		for(int i = 1; i <= 4; ++i)
		{
			t_vec[i-1] = new test();
			switch(i)
			{
				case 1:
					System.out.println(1);
					//break;
				case 2:
					System.out.println(2);
					//break;
				case 3:
					System.out.println(3);
					//break;
				default:
					System.out.println(4);
			}
		}
	}
}///:~