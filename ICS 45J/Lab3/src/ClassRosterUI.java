// Daniel Miller Tromberg - 71808192
// Edward Xia             - 73387315

import java.util.Scanner;

public class ClassRosterUI
{
	public static final Scanner in = new Scanner(System.in);

	public static void printMenu()
	{
		System.out.println("----------");
		System.out.println("ac: Add Course");
		System.out.println("dc: Drop Course");
		System.out.println("as: Add Student");
		System.out.println("ds: Drop Student");
		System.out.println(" p: Print ClassRoster");
		System.out.println(" q: Quit Program");
		System.out.println("----------");
	}

	public static String getCommand()
	{
		String command;
		do {
			System.out.print("Enter Command: ");
			command = in.nextLine();
		} while ( !(command.equals("ac") ||
					command.equals("dc") ||
					command.equals("as") ||
					command.equals("ds") ||
					command.equals("p") ||
					command.equals("q") ));
		return command;
	}
}
