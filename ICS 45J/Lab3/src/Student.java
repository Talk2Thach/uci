// Daniel Miller Tromberg - 71808192
// Edward Xia             - 73387315

public class Student
{
	private int studentId;
	private String firstName;
	private String lastName;

	public Student(int studentId, String lastName, String firstName)
	{
		this.studentId = studentId;
		this.lastName = lastName;
		this.firstName = firstName;
	}

	public int getStudentId()
	{
		return studentId;
	}
	public void setStudentId(int studentId)
	{
		this.studentId = studentId;
	}
	public String getFirstName()
	{
		return firstName;
	}
	public void setFirstName(String firstName)
	{
		this.firstName = firstName;
	}
	public String getLastName()
	{
		return lastName;
	}
	public void setLastName(String lastName)
	{
		this.lastName = lastName;
	}
	
	public int compareTo(Student student)
	{
		if (this.studentId == student.studentId) {
			return 0; // we cannot have two student with same ID
		}
		int result = this.lastName.compareTo(student.lastName);
		if (result == 0) {
			return (this.studentId < student.studentId) ? -1 : 1;
		} else {
			return result;
		}
	}
}
