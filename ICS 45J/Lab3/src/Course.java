// Daniel Miller Tromberg - 71808192
// Edward Xia             - 73387315

public class Course
{
	private static final int MAX = 50;
	private String courseCode;
	private String courseName;
	private int enrolled;
	private Student[] students = new Student[MAX];

	public Course(String courseCode, String courseName)
	{
		this.courseCode = courseCode;
		this.courseName = courseName;
	}

	private void insertStudentAt(Student s, int index) throws StudentLimitException {
		if (index >= MAX) {
			throw new StudentLimitException();
		}
		for (int i = this.enrolled; i > index; --i) {
			students[i] = students[i - 1];
		}
		students[index] = s;
		++this.enrolled;
	}

	public void addStudent(Student s) throws StudentLimitException, DuplicateStudentException
	{
		if (enrolled >= 50) {
			throw new StudentLimitException();
		}

		if (this.enrolled == 0) {
			this.insertStudentAt(s, 0);
			return;
		}

		for (int i = 0; i < this.enrolled; ++i) {
			int compared = s.compareTo(students[i]);
			if (compared == 0) {
				throw new DuplicateStudentException();
			} else if (compared < 0){
				this.insertStudentAt(s, i);
				return;
			}
		}

		this.insertStudentAt(s, this.enrolled);
	}

	public void removeStudent(int studentId) throws EmptyStudentListException, StudentNotFoundException
	{
		if (enrolled == 0) {
			throw new EmptyStudentListException();
		}

		for (int i = 0; i < enrolled; ++i) {
			if (studentId == students[i].getStudentId()) {
				for (int j = i; j < enrolled - 1; ++j) {
					students[j] = students[j + 1];
				}
				--enrolled;
				return;
			}
		}

		throw new StudentNotFoundException();
	}

	public String getCourseCode()
	{
		return courseCode;
	}

	public void setCourseCode(String courseCode)
	{
		this.courseCode = courseCode;
	}

	public String getCourseName()
	{
		return courseName;
	}

	public void setCourseName(String courseName)
	{
		this.courseName = courseName;
	}

	public int getEnrolled()
	{
		return enrolled;
	}

	public Student[] getStudents()
	{
		return students;
	}
}
