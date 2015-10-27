// Name: Edward Xia
// #ID:  73387315
// Name: Yujie Ding
// #ID:  64314452

public class Book
{
	private int numOfPages;
	private int yearPublished;
	private double price;
	private String title;
	private Author author;

	public Book()
	{
		this.author = new Author();
	}
	public Book(Book book)
	{
		this.numOfPages = book.getNumOfPages();
		this.yearPublished = book.getYearPublished();
		this.price = book.getPrice();
		this.title = book.getTitle();
		this.author = new Author(book.getAuthor());
	}

	public int getNumOfPages()
	{
		return numOfPages;
	}
	public void setNumOfPages(int numOfPages)
	{
		this.numOfPages = numOfPages;
	}

	public int getYearPublished()
	{
		return yearPublished;
	}
	public void setYearPublished(int yearPublished)
	{
		this.yearPublished = yearPublished;
	}

	public double getPrice()
	{
		return price;
	}
	public void setPrice(double price)
	{
		this.price = price;
	}

	public String getTitle()
	{
		return title;
	}
	public void setTitle(String title)
	{
		this.title = title;
	}

	public Author getAuthor()
	{
		return author;
	}
	public void setAuthor(Author author)
	{
		this.author = author;
	}
	public void setAuthor(String firstName, String lastName, int birthYear, int numOfPublications)
	{
		this.author.setFirstName(firstName);
		this.author.setLastName(lastName);
		this.author.setBirthYear(birthYear);
		this.author.setNumOfPublications(numOfPublications);
	}

	public String toString()
	{
		return
			"Title: " + this.title + "\n" +
			"Published in: " + this.yearPublished + "\n" +
			"Number of Pages: " + this.numOfPages + "\n" +
			"Price: " + this.price + "\n" +
			"Written by " + this.author.getFirstName() + " " + this.author.getLastName() +  ", who was born in " + this.author.getBirthYear() + " and has " + this.author.getNumOfPublications() + " publications\n";
	}
}
