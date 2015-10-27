//Steven Kuo 87956327 10 AM Lab Section 2
//Edward Xia 73387315

import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public class MusicManager implements MusicManagerInterface
{
	private MusicList musicList;

	public MusicManager()
	{
		//Ask the user if the music file is on disk or on the Web
		Scanner userInput = new Scanner(System.in);
		String musicFileLocation = "";
		do {
			System.out.print("Music file on [disk] or [web]: ");
			musicFileLocation = userInput.nextLine().trim();
		} while ( (!musicFileLocation.equals("disk")) && (!musicFileLocation.equals("web")) );

		MusicFileInterface musicFile = null;
		switch (musicFileLocation) {
		case "disk":
			musicFile = new MusicFile();
			break;
		case "web":
			musicFile = new MusicFileFromWeb();
			break;
		}

		System.out.print("Please input the url: ");
		try
		{
			musicFile.open(userInput.nextLine());
		}
		catch (IOException e)
		{
			System.out.println("Error: Cannot open the file.");
			userInput.close();
			System.exit(1);
		}
		userInput.close();

		musicList = new MusicList();
		while (musicFile.hasMoreItems()) {
			musicList.addItem(new MusicItem(musicFile.readItem()));
		}
		musicFile.close();
	}



	// Prepares an index file from an incoming list of music items;
		// displays to the screen the media category counts
		// and a total count of items processed.
	public void makeIndexAndDisplayCounts()
	{
		IndexFile indexFile = new IndexFile();
		try
		{
			indexFile.open("index.txt");
		}
		catch (IOException e)
		{
			System.out.println("Error: Cannot open the file.");
			System.exit(1);
		}
		for (Bucket bucket : musicList.getBuckets()) {
			for (MusicItem item : bucket.getItems()) {
				indexFile.writeItem(item);
			}
		}
		indexFile.close();
		System.out.println(String.format("Index File: %s", (new File("index.txt")).getAbsolutePath()));
		System.out.println(String.format("Total: %d", musicList.getTotalItemCount()));
		System.out.println(String.format("Compact Media: %d", musicList.getCompactMediaItemCount()));
		System.out.println(String.format("Paper: %d", musicList.getPaperItemCount()));
		System.out.println(String.format("Vinyl: %d", musicList.getVinylItemCount()));
		System.out.println(String.format("Wax Cylinder: %d", musicList.getWaxCylinderItemCount()));
	}

}
