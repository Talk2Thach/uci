// Name: Edward Xia
// #ID:  73387315
// Name: Yujie Ding
// #ID:  64314452

public class Lab1
{
	public static void main(String[] args)
	{
		// Create a new book with default values for all attributes
		Book book = new Book();
		// Set the appropriate fields for the book’s objects
		book.setTitle("Harry Potter and the Goblet of Fire");
		book.setPrice(12.99);
		book.setYearPublished(2000);
		book.setNumOfPages(734);
		book.setAuthor("J.K.", "Rowling", 1965, 7);
		// Prints out the state of the book.
		System.out.println(book.toString());

		// Test the copy constructor
		Book myBook = new Book(book);
		System.out.println(myBook.toString());

		// Test changing the state of the object
		myBook.getAuthor().setNumOfPublications(8);
		System.out.println(myBook.toString());
	}
}
