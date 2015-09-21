import java.text.*;

public class PersonTest
{
	public static void main(String args[])
	{
		Person[] people = new Person[2];
		people[0] = new Employee("张三",50000);
		people[1] = new Student("李四","计算机科学");
		for(int i = 0; i < people.length; i++)
			{
				Person p = people[i];
				System.out.println(p.getName() + "," + p.getDescription());
			}
	}
}
abstract class Person
{
	public Person(String name)
	{
		m_strname = name;
	}
	public abstract String getDescription();
	public String getName()
	{
		return m_strname;
	}
	private String m_strname;
}
class Employee extends Person
{
	public Employee(String n,double s)
	{
		super(n);
		m_fsalary = s;
	}
	public double getSalary()
	{
		return m_fsalary;
	}
	public String getDescription()
	{
		NumberFormat formatter = NumberFormat.getCurrencyInstance();
		return "员工的工资是:"+formatter.format(m_fsalary);
	}
	public void raiseSalary(double byPercent)
	{
		double raise = m_fsalary * byPercent / 100;
		m_fsalary += raise;
	}
	private double m_fsalary;
}
class Student extends Person
{
	public Student(String n,String m)
	{
		super(n);
		m_strmajor = m;
	}
	public String getDescription()
	{
		return "学生的专业是:"+m_strmajor;
	}
	private String m_strmajor;
}