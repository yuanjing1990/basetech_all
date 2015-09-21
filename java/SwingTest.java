import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
public class SwingTest extends JFrame
{
	public SwingTest(){
		setTitle("Test");
		setBounds(30,30,100,100);
		addWindowListener(new WindowAdapter(){
			public void windowCloseing(WindowEvent e){
				System.exit(0);
			}
		});
		setVisible(true);
	}
	public static void main(String[] argv)
	{
		new SwingTest();
	}
}
