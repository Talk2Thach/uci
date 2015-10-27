// Name: Edward Xia
// #ID:  73387315
// Name: Yujie Ding
// #ID:  64314452

public class Author
{
	private String firstName;
	private String lastName;
	private int birthYear;
	private int numOfPublications;

	public Author()
	{

	}
	public Author(Author author)
	{
		this.firstName = author.getFirstName();
		this.lastName = author.getLastName();
		this.birthYear = author.getBirthYear();
		this.numOfPublications = author.getNumOfPublications();
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

	public int getBirthYear()
	{
		return birthYear;
	}
	public void setBirthYear(int birthYear)
	{
		this.birthYear = birthYear;
	}

	public int getNumOfPublications()
	{
		return numOfPublications;
	}
	public void setNumOfPublications(int numOfPublications)
	{
		this.numOfPublications = numOfPublications;
	}
}
