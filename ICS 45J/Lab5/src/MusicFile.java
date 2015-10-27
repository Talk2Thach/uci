//Steven Kuo 87956327 10 AM Lab Section 2
//Edward Xia 73387315

import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;


public class MusicFile implements MusicFileInterface
{
	protected Scanner in = null;

	// Opens a sequential text file to accept
	// music info and parse it
	//
	// Throws IOException if music file cannot
	// be opened or other IOproblems occur
	public void open(String indexFileName) throws IOException
	{
		in = new Scanner(new FileInputStream(indexFileName));
	}

	// Are there more items in the file?
		// true = yes (not at end of file); false otherwise
	public boolean hasMoreItems()
	{
		return in.hasNextLine();
	}

	// Read and return one music item, as as ArrayList<String>
		// Number of attributes will varying depending on type of item
		//	read -- but first three are always the same:
		//	accession number, title, media code
		// Hint: Read in a line, then use string tokenizer to break it
		//	into fields, with ";" (and end of string) as the delimiter
	public ArrayList<String> readItem()
	{
		ArrayList<String> item = new ArrayList<String>();
		if (hasMoreItems()){
			String line = in.nextLine();
			String[] lineArray = line.split(";");
			for(int i = 0 ; i < lineArray.length; i++){
				item.add(lineArray[i].trim());
			}
		}
		return item;

	}

	// Close the file
	public void close()
	{
		in.close();
	}

}
