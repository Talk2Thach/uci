//Steven Kuo 87956327 10 AM Lab Section 2
//Edward Xia 73387315
import java.util.ArrayList;

public class MusicItem implements MusicItemInterface
{
	private ArrayList<String> item;

	public MusicItem(ArrayList<String> item)
	{
		this.item = item;
	}

	public String displaySupplementalInfo()
	{
		switch (this.getMedia()) {
		case PAPER:
			return String.format("# of pages: %s", item.get(3));
		case COMPACT:
			return String.format("# of tracks: %s | Year released: %s", item.get(3), item.get(4));
		case VINYL:
			return String.format("Label: %s | RPM: %s", item.get(3), item.get(4));
		case WAX_CYLINDER:
			return String.format("Maker: %s", item.get(3));
		default:
			return "";
		}
	}


	public String getAccessionNumber()
	{
		return item.get(0);
	}


	public String getTitle()
	{
		return item.get(1);
	}


	public String getMedia()
	{
		return item.get(2);
	}

}
