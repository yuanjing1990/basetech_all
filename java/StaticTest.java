public class StaticTest
{
	public static void main(String args[])
	{
		Employee[] staff = new Employee[3];
		staff[0] = new Employee("张三",40000);
		staff[1] = new Employee("李四",60000);
		staff[2] = new Employee("王五",65000);
		for(int i = 0; i < staff.length; i++)
			{
				Employee e = staff[i];
				e.setId();
				System.out.println("姓名："+e.getName()+",编号："+e.getId()+",工资："+e.getSalary());
			}
		int n = Employee.getNextId();
		System.out.println("下一个有效编号："+n);
	}
}

class Employee
{
	public Employee(String n,double s)
	{
		m_name = n;
		m_salary = s;
		m_id = 0;
	}
	public String getName()
	{
		return m_name;
	}
	public double getSalary()
	{
		return m_salary;
	}
	public int getId()
	{
		return m_id;
	}
	public void setId()
	{
		m_id = nextId;
		nextId++;
	}
	public static int getNextId()
	{
		return nextId;
	}
	public static void main(String args[])
	{
		Employee e = new Employee("张三",50000);
		System.out.println(e.getName()+" "+e.getSalary());
	}
	private String m_name;
	private double m_salary;
	private int m_id;
	private static int nextId = 1;
}