import java.awt.event.*;
import javax.swing.*;
public class SwingTest extends JFrame
{
	/**
	 *
	 */
	private static final long serialVersionUID = -4806845269405973805L;

	public SwingTest() {
		setTitle("Test");
		setBounds(30,30,100,100);
		addWindowListener(new WindowAdapter(){
			@Override
			public void windowClosing(WindowEvent e){
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
