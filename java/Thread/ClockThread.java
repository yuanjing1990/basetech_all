import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
public class ClockThread
{
	public static void main(String args[])
	{
		JFrame f = new ClockFrame();
		f.show();
	}
}
class ClockFrame extends JFrame
{
	public ClockFrame()
	{
		setSize(250,150);
		setTitle("ClockTest");
		
		addWindowListener(new WindowAdapter()
		{
			public void windowClosing(WindowEvent e)
			{
				System.exit(0);
			}
		});
		
		Container c = getContentPane();
		c.setLayout(new GridLayout(2,3));
		c.add(new ClockCanvas("San Jose","GMT-8"));
		c.add(new ClockCanvas("Taipei","GMT+8"));
	}
}

interface TimerListener
{
	void timeElapsed(Timer t);
}
class Timer extends Thread
{
	public Timer(int i,TimerListener t)
	{
		target = t;
		interval = i;
	}
	public void run()
	{
		try
		{
			while(!interrupted())
			{
				sleep(interval);
				target.timeElapsed(this);
			}
		}
		catch(InterruptedException e){}
	}
	private TimerListener target;
	private int interval;
}
class ClockCanvas extends JPanel implements TimerListener
{
	public ClockCanvas(String c,String tz)
	{
		city = c;
		calendar = new GregorianCalendar(TimeZone.getTimeZone(tz));
		Timer t = new Timer(1000,this);
		t.start();
		setSize(125,125);
	}
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		g.drawOval(0,0,100,100);
		double hourAngle = 2 * Math.PI * (seconds - 3 * 60 * 60)/(12 * 60 * 60);
		double minuteAngle = 2 * Math.PI * (seconds - 15 * 60) / (60 * 60);
		double secondAngle = 2 * Math.PI * (seconds - 15) / (60);
		g.drawLine(50,50,50 + (int)(30 * Math.cos(hourAngle)),50 + (int)(30 * Math.sin(hourAngle)));
		g.drawLine(50,50,50 + (int)(45 * Math.cos(minuteAngle)),50 + (int)(40 * Math.sin(minuteAngle)));
		g.drawLine(50,50,50 + (int)(45 * Math.cos(secondAngle)),50 + (int)(45 * Math.sin(secondAngle)));
		g.drawString(city,0,115);
	}
	public void timeElapsed(Timer t)
	{
		calendar.setTime(new Date());
		seconds = calendar.get(Calendar.HOUR) * 60 * 60 +
			calendar.get(calendar.MINUTE) * 60 +
			calendar.get(Calendar.SECOND);
		repaint();
	}
	private int seconds = 0;
	private String city;
	private int offset;
	private GregorianCalendar calendar;
	private final int LOCAL = 16;
}