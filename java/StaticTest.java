public class StaticTest {
	public static void main(String args[]) {
		Employee[] staff = new Employee[3];
		staff[0] = new Employee("����", 40000);
		staff[1] = new Employee("����", 60000);
		staff[2] = new Employee("����", 65000);
		for (int i = 0; i < staff.length; i++) {
			Employee e = staff[i];
			e.setId();
			System.out.println("������" + e.getName() + ",��ţ�" + e.getId() + ",���ʣ�" + e.getSalary());
		}
		int n = Employee.getNextId();
		System.out.println("��һ����Ч��ţ�" + n);
	}
}

class Employee {
	public Employee(String n, double s) {
		m_name = n;
		m_salary = s;
		m_id = 0;
	}

	public String getName() {
		return m_name;
	}

	public double getSalary() {
		return m_salary;
	}

	public int getId() {
		return m_id;
	}

	public void setId() {
		m_id = nextId;
		nextId++;
	}

	public static int getNextId() {
		return nextId;
	}

	public static void main(String args[]) {
		Employee e = new Employee("����", 50000);
		System.out.println(e.getName() + " " + e.getSalary());
	}

	private String m_name;
	private double m_salary;
	private int m_id;
	private static int nextId = 1;
}