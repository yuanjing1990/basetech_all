//<applet code=Applet1.class width=200 height=100></applet>
import java.awt.*;
import java.applet.*;
public class Applet1 extends Applet
{
	static boolean flag = false;
	Button btn = new Button("Button");
	public void init()
	{
		add(btn);
	}
	public void paint(Graphics g)
	{
		if(!flag)
			return;
		g.drawString("First applet",10,10);
		g.draw3DRect(0,0,100,20,true);
	}
	public boolean action(Event env,Object arg)
	{
		if(env.target.equals(btn))
		{
			flag = !flag;
			repaint();
		}else
			return super.action(env,arg);
		return true;
	}
}