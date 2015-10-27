// Daniel Miller Tromberg - 71808192
// Edward Xia             - 73387315

import java.util.Scanner;

public class RosterManager
{
	private static final int maxCourses = 10;
	private Course[] courses = new Course[maxCourses];
	private int totalCourses;

	public Course[] getCourses()
	{
		return courses;
	}

	public int getTotalCourses()
	{
		return totalCourses;
	}


	public void run()
	{
		System.out.println("Welcome to Class Roster Manager!");
		System.out.println("Select an action based on the following menu:");
		String command;
		Scanner in = ClassRosterUI.in;

		do {
			ClassRosterUI.printMenu();
			command = ClassRosterUI.getCommand();
			try {
				if (command.equals("ac")) {
					System.out.print("Enter Course Code: ");
					String code = in.nextLine();
					System.out.print("Enter Course Name: ");
					String name = in.nextLine();
					this.addCourse(new Course(code, name));
				} else if (command.equals("dc")) {
					System.out.print("Enter Course Code: ");
					String code = in.nextLine();
					this.deleteCourse(code);
				} else if (command.equals("as")) {
					System.out.print("Enter course code for Student: ");
					String code = in.nextLine();
					this.getCourse(code);
					int id;
					do {
						System.out.print("Enter StudentID: ");
						id = in.nextInt(); in.nextLine(); // clears buffer
						if (id < 0) {
							System.out.println("ERROR: ID must be positive.");
						}
					} while (id < 0);
					System.out.print("Enter last name: ");
					String lastName = in.nextLine();
					System.out.print("Enter first name: ");
					String firstName = in.nextLine();
					Student s = new Student(id, lastName, firstName);
					this.addStudent(code, s);
				} else if (command.equals("ds")) {
					System.out.print("Enter course code for Student: ");
					String code = in.nextLine();
					this.getCourse(code);
					System.out.print("Enter StudentID: ");
					int id = in.nextInt(); in.nextLine(); // clears buffer
					this.deleteStudent(id, code);
				} else if (command.equals("p")) {
					this.printRoster();
				}
			} catch (CourseLimitException e) {
				System.out.println("ERROR: Roster manager is full.");
			} catch (DuplicateCourseException e) {
				System.out.println("ERROR: The course is already in roster.");
			} catch (EmptyCourseListException e) {
				System.out.println("ERROR: The roster is empty.");
			} catch (CourseNotFoundException e) {
				System.out.println("ERROR: Course not found.");
			} catch (StudentLimitException e) {
				System.out.println("ERROR: The course is full.");
			} catch (DuplicateStudentException e) {
				System.out.println("ERROR: This student is already enrolled.");
			} catch (EmptyStudentListException e) {
				System.out.println("ERROR: Student list is empty.");
			} catch (StudentNotFoundException e) {
				System.out.println("ERROR: Student not found.");
			} catch (Exception e) {
				System.out.println("ERROR: Unknown error.");
				e.printStackTrace();
			}
		} while (!command.equals("q"));
	}

	public void addCourse(Course c) throws CourseLimitException, DuplicateCourseException
	{
		if (totalCourses >= maxCourses) {
			throw new CourseLimitException();
		}

		for (int i = 0; i < totalCourses; ++i) {
			if (c.getCourseCode().equalsIgnoreCase(courses[i].getCourseCode())) {
				throw new DuplicateCourseException();
			}
		}

		courses[totalCourses] = c;
		++totalCourses;
	}

	public void deleteCourse(String courseCode) throws EmptyCourseListException, CourseNotFoundException
	{
		if (totalCourses == 0) {
			throw new EmptyCourseListException();
		}

		for (int i = 0; i < totalCourses; ++i) {
			if (courseCode.equalsIgnoreCase(courses[i].getCourseCode())) {
				for (int j = i; j < totalCourses - 1; ++j) {
					courses[j] = courses[j + 1];
				}
				--totalCourses;
				return;
			}
		}

		throw new CourseNotFoundException();
	}

	public Course getCourse(String courseCode) throws EmptyCourseListException, CourseNotFoundException
	{
		if (totalCourses == 0) {
			throw new EmptyCourseListException();
		}

		for (int i = 0; i < totalCourses; ++i) {
			if (courseCode.equals(courses[i].getCourseCode())) {
				return courses[i];
			}
		}

		throw new CourseNotFoundException();
	}

	public void addStudent(String courseCode, Student s) throws EmptyCourseListException, CourseNotFoundException, StudentLimitException, DuplicateStudentException
	{
		if (totalCourses == 0) {
			throw new EmptyCourseListException();
		}

		for (int i = 0; i < totalCourses; ++i) {
			if (courseCode.equals(courses[i].getCourseCode())) {
				courses[i].addStudent(s);
				return;
			}
		}

		throw new CourseNotFoundException();
	}

	public void deleteStudent(int id, String courseCode) throws EmptyCourseListException, CourseNotFoundException, EmptyStudentListException, StudentNotFoundException
	{
		if (totalCourses == 0) {
			throw new EmptyCourseListException();
		}

		for (int i = 0; i < totalCourses; ++i) {
			if (courseCode.equals(courses[i].getCourseCode())) {
				courses[i].removeStudent(id);
				return;
			}
		}

		throw new CourseNotFoundException();
	}

	public void printRoster()
	{
		System.out.println("********************");
		for (int i = 0; i < totalCourses; ++i) {
			System.out.println(String.format("%s: %s", courses[i].getCourseCode(), courses[i].getCourseName()));
			System.out.println(String.format("Enrolled: %d", courses[i].getEnrolled()));

			for (int j = 0, n = courses[i].getEnrolled(); j < n; ++j) {
				Student s = courses[i].getStudents()[j];
				System.out.println(String.format("\t%d | %s, %s", s.getStudentId(), s.getLastName(), s.getFirstName()));
			}
		}
		System.out.println("********************");
	}
}

