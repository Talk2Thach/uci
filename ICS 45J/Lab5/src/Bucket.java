//Steven Kuo 87956327 10 AM Lab Section 2
//Edward Xia 73387315
import java.util.LinkedList;

public class Bucket implements BucketInterface
{
	//one bucket can contain multiple music items
	private LinkedList<MusicItem> itemsBucket;

	public Bucket()
	{
		// TODO Auto-generated constructor stub
		itemsBucket = new LinkedList<MusicItem>();
	}


	// Add the music item into the this bucket,
		// in alphabetical order by title
	public void addItem(MusicItem itemToAdd)
	{
		if (itemsBucket.size() == 0) {
			itemsBucket.add(itemToAdd);
		} else {
			//find the node to add the MusicItem to
			for(int i = 0;i < itemsBucket.size();i++)
			{
				if(itemToAdd.getTitle().compareTo(itemsBucket.get(i).getTitle()) < 0)
				{
					itemsBucket.add(i, itemToAdd);
					return;
				}
			}
			itemsBucket.addLast(itemToAdd);
		}
	}

	// Accessor -- get the list
	public LinkedList<MusicItem> getItems()
	{
		return itemsBucket;
	}

}
