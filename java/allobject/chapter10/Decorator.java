import java.io.*;
import java.util.*;
public class Decorator
{
	public static void main(String[] args)
	{
		Work w = new DecoratePaint(new DecorateDig(new SquarePet()));
		w.insert();
	}
}
interface Work
{
	public void insert();
}
class SquarePet implements Work
{
	public void insert()
	{
		System.out.println("SquarePet Insert!");
	}
}
class Decorate implements Work
{
	private Work work;
	Decorate(){};
	Decorate(Work w){work = w;}
	public void insert()
	{
		work.insert();
	}
}
class DecoratePaint extends Decorate
{
	DecoratePaint(Work w){super(w);}
	public void insert()
	{
		addWork();
		super.insert();
	}
	private void addWork()
	{
		System.out.println("Additional Work \"Painting\"!");
	}
}
class DecorateDig extends Decorate
{
	DecorateDig(Work w){super(w);}
	public void insert()
	{
		super.insert();
		DigHole();
	}
	private void DigHole()
	{
		System.out.println("Dig a Hole for Pet!");
	}
}