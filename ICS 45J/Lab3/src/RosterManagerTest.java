// Daniel Miller Tromberg - 71808192
// Edward Xia             - 73387315

import static org.junit.Assert.*;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class RosterManagerTest
{
	private RosterManager manager;

	@Before
	public void setUp() throws Exception
	{
		manager = new RosterManager();
	}


	@After
	public void tearDown() throws Exception
	{
	}

	private Course randomCourse() {
		return new Course("" + Math.random(), "" + Math.random());
	}

	@Test
	public void testAddCourse()
	{
		for (int i = 0; i < 10; ++i) {
			Course c = randomCourse();
			assertEquals(manager.getTotalCourses(), i);
			try
			{
				manager.addCourse(c);
			}
			catch (CourseLimitException e)
			{
				fail("It should not be full here");
			}
			catch (DuplicateCourseException e)
			{
				--i;
			}
			assertEquals(manager.getTotalCourses(), i + 1);
		}
	}

	@Test(expected=CourseLimitException.class)
	public void testAddCourseFull() throws CourseLimitException
	{
		for (int i = 0; i < 11; ++i) {
			Course c = randomCourse();
			assertEquals(manager.getTotalCourses(), i);
			try
			{
				manager.addCourse(c);
			}
			catch (DuplicateCourseException e)
			{
				--i;
			}
			assertEquals(manager.getTotalCourses(), i + 1);
		}
		assertEquals(manager.getTotalCourses(), 10);

	}

	@Test(expected=DuplicateCourseException.class)
	public void testAddCourseDuplicate() throws DuplicateCourseException, CourseLimitException
	{
		Course a = new Course("1", "1");
		Course b = new Course("1", "1");
		manager.addCourse(a);
		manager.addCourse(b);
		assertEquals(manager.getTotalCourses(), 1);
	}

	@Test
	public void testRemoveCourse() throws EmptyCourseListException, CourseNotFoundException
	{

		Course n = new Course("3", "3");
		try {
			manager.addCourse(n);
		} catch (Exception e) {
		}
		assertEquals(manager.getTotalCourses(), 1);
		manager.deleteCourse("3");
		assertEquals(manager.getTotalCourses(), 0);
	}

	@Test(expected=EmptyCourseListException.class)
	public void testRemoveCourseEmpty() throws EmptyCourseListException, CourseNotFoundException
	{
		manager.deleteCourse("0");
	}

	@Test(expected=CourseNotFoundException.class)
	public void testRemoveCourseNotFound() throws EmptyCourseListException, CourseNotFoundException
	{
		try {
			manager.addCourse(new Course("3", "3"));
		} catch (Exception e) {
		}
		manager.deleteCourse("0");
	}

	private Student randomStudent() {
		return new Student((int)(Math.random() * 1000000 + 1), "" + Math.random(), "" + Math.random());
	}

	@Test
	public void testAddStudent()
	{
		Course ics = new Course("ICS", "test");

		try {
			manager.addCourse(ics);
		} catch (Exception e) {
		}

		try {
			ics = manager.getCourse("ICS");
		} catch (Exception e){
			fail();
		}

		for (int i = 0; i < 50; ++i) {
			Student s = randomStudent();
			assertEquals(ics.getEnrolled(), i);
			try {
				manager.addStudent("ICS", s);
			} catch (StudentLimitException e) {
				fail("It should not be full here");
			} catch (DuplicateStudentException e) {
				--i;
			} catch (Exception e) {
				fail();
			}
			assertEquals(ics.getEnrolled(), i + 1);

		}

		assertEquals(ics.getEnrolled(), 50);

		// Testing ordering
		for (int i = 0; i < 49; ++i) {
			assertTrue(ics.getStudents()[i].compareTo(ics.getStudents()[i + 1]) < 1);
		}
	}

	@Test(expected=StudentLimitException.class)
	public void testAddStudentFull() throws EmptyCourseListException, CourseNotFoundException, StudentLimitException
	{
		Course ics = new Course("ICS", "test");

		try {
			manager.addCourse(ics);
		} catch (Exception e) {
			fail();
		}

		try {
			ics = manager.getCourse("ICS");
		} catch (Exception e){
			fail();
		}

		for (int i = 0; i < 51; ++i) {
			Student s = randomStudent();
			assertEquals(ics.getEnrolled(), i);
			try {
				manager.addStudent("ICS", s);
			} catch (DuplicateStudentException e) {
				--i;
			}
			assertEquals(ics.getEnrolled(), i + 1);
		}

		assertEquals(ics.getEnrolled(), 50);
	}

	@Test(expected=DuplicateStudentException.class)
	public void testAddStudnetDuplicate() throws EmptyCourseListException, CourseNotFoundException, StudentLimitException, DuplicateStudentException
	{
		Course ics = new Course("ICS", "test");

		try {
			manager.addCourse(ics);
		} catch (Exception e) {
			fail();
		}

		Student a = new Student(1, "hi", "there");
		Student b = new Student(1, "hi", "hello");

		manager.addStudent("ICS", a);
		manager.addStudent("ICS", b);
	}

	@Test
	public void testRemoveStudent() throws EmptyStudentListException, StudentNotFoundException, EmptyCourseListException, CourseNotFoundException
	{
		Course ics = new Course("ICS", "test");

		try {
			manager.addCourse(ics);
		} catch (Exception e) {
			fail();
		}
		try {
			ics = manager.getCourse("ICS");
		} catch (Exception e){
			fail();
		}
		Student a = new Student(1, "hi", "there");
		try {
			manager.addStudent("ICS", a);
		} catch (Exception e) {}
		assertEquals(ics.getEnrolled(), 1);
		manager.deleteStudent(1, "ICS");
		assertEquals(ics.getEnrolled(), 0);
	}

	@Test(expected=EmptyStudentListException.class)
	public void testRemoveStudentEmpty() throws EmptyStudentListException, StudentNotFoundException, EmptyCourseListException, CourseNotFoundException
	{
		Course ics = new Course("ICS", "test");

		try {
			manager.addCourse(ics);
		} catch (Exception e) {
			fail();
		}

		manager.deleteStudent(1, "ICS");
	}

	@Test(expected=StudentNotFoundException.class)
	public void testRemoveStudentNotFound() throws EmptyStudentListException, StudentNotFoundException, EmptyCourseListException, CourseNotFoundException
	{
		Course ics = new Course("ICS", "test");

		try {
			manager.addCourse(ics);
		} catch (Exception e) {
			fail();
		}

		Student a = new Student(1, "hi", "there");
		try {
			manager.addStudent("ICS", a);
		} catch (Exception e) {
			fail();
		}

		manager.deleteStudent(2, "ICS");

	}
}
