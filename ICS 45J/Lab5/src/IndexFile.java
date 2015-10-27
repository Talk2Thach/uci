//Steven Kuo 87956327 10 AM Lab Section 2
//Edward Xia 73387315


import java.io.IOException;
import java.io.PrintWriter;

public class IndexFile implements IndexFileInterface
{

	private PrintWriter writer = null;
	// Open index file with name indexFileName
	// for sequential writing
	//
	// Opens a sequential text file to accept
	// output; prints out report headings
	//
	// Throws IOException if index file cannot
	// be opened or other IO problems occur
	public void open(String indexFileName) throws IOException
	{
		writer = new PrintWriter(indexFileName);
		writer.println(String.format("%-49s %-11s %-6s %s", "TITLE" ,"ACCESSION #", "MEDIA" ,"ADDITIONAL INFORMATION"));
		writer.println("--------------------------------");
	}

	// Writes out the current line of the report,
	// contained in itemToWrite
	public void writeItem(MusicItem itemToWrite)
	{
		writer.println(String.format("%-49s %-11s %-6s %s",
			itemToWrite.getTitle(), itemToWrite.getAccessionNumber(), itemToWrite.getMedia(), itemToWrite.displaySupplementalInfo()));
	}


	// closes the index file
	public void close()
	{
		writer.close();
	}

}
