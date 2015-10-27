//Steven Kuo 87956327 10 AM Lab Section 2
//Edward Xia 73387315
import java.io.IOException;
import java.net.URL;
import java.net.URLConnection;
import java.util.Scanner;

public class MusicFileFromWeb extends MusicFile
{
	public void open(String indexFileName) throws IOException
	{
		URL remoteFileLocation = new URL(indexFileName);
		URLConnection connection = remoteFileLocation.openConnection();
		in = new Scanner(connection.getInputStream());
	}
}
