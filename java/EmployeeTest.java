import java.util.*;

public class EmployeeTest
{
	public static void main(String args[])
	{
		Employee[] staff = new Employee[3];
		staff[0] = new Employee("张三",75000,1987,12,15);
		staff[1] = new Employee("李四",50000,1989,10,1);
		staff[2] = new Employee("王五",40000,1990,3,15);
		for(int i = 0; i < staff.length; i++)
			staff[i].raiseSalary(5);
		for(int i = 0; i < staff.length; i++)
			{
				Employee e = staff[i];
				System.out.println("姓名:"+e.getName()+",工资:"+e.getSalary()
				+",工作日期:"+e.getHireDay());
			}
	}
}
class Employee
{
	public Employee(String n,double s,int year,int month,int day)
	{
		m_name = n;
		m_salary = s;
		GregorianCalendar calendar = new GregorianCalendar(year,month-1,day);
		m_hireDay = calendar.getTime();
	}
	public String getName()
	{
		return m_name;
	}
	public double getSalary()
	{
		return m_salary;
	}
	public Date getHireDay()
	{
		return m_hireDay;
	}
	public void raiseSalary(double byPercent)
	{
		double raise = m_salary * byPercent / 100;
		m_salary += raise;
	}
	private String m_name;
	private double m_salary;
	private Date m_hireDay;
}