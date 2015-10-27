//Steven Kuo 87956327 10 AM Lab Section 2
//Edward Xia 73387315

import java.util.ArrayList;

public class MusicList implements MusicListInterface
{
	ArrayList<Bucket> bucketArrayList;
	int totalItemCount;
	int paperItemCount;
	int compactMediaItemCount;
	int vinylItemCount;
	int waxCylinderItemCount;


	// Make a bucket for each of the 26 list locations;
		// Set counts of items to zero
	public MusicList()
	{
		bucketArrayList = new ArrayList<Bucket>();
		for (int i = 0; i < 26; ++i) {
			bucketArrayList.add(new Bucket());
		}
		totalItemCount = 0;
		paperItemCount = 0;
		compactMediaItemCount = 0;
		vinylItemCount = 0;
		waxCylinderItemCount = 0;
	}


	// Add an item into the correct bucket in the list
	// Bucket to use is one corresponding to first letter in title
	// Increment the appropriate media count
	public void addItem(MusicItem item)
	{
		//access the title's first letter and if it matches the Bucket, add the item to that bucket

		//MusicItem's title's first letter
		char titleFirstLetter = item.getTitle().toLowerCase().charAt(0);

		//find the bucket in the ArrayList to add the item to
		for(char ch = 'a'; ch <= 'z'; ch++)
		{
			//compare ch with title's first letter
			//if found, assign value to index
			if(ch == titleFirstLetter){
				//add the item to the correct Bucket
				bucketArrayList.get((int)ch-(int)'a').addItem(item);
				switch (item.getMedia()) {
				case MusicItemInterface.COMPACT:
					++compactMediaItemCount;
					break;
				case MusicItemInterface.PAPER:
					++paperItemCount;
					break;
				case MusicItemInterface.VINYL:
					++vinylItemCount;
					break;
				case MusicItemInterface.WAX_CYLINDER:
					++waxCylinderItemCount;
					break;
				}
				++totalItemCount;
				break;
			}
		}

	}


	public ArrayList<Bucket> getBuckets()
	{
		return bucketArrayList;
	}


	public int getTotalItemCount()
	{
		return totalItemCount;
	}


	public int getPaperItemCount()
	{

		return paperItemCount;
	}


	public int getCompactMediaItemCount()
	{

		return compactMediaItemCount;
	}


	public int getVinylItemCount()
	{

		return vinylItemCount;
	}


	public int getWaxCylinderItemCount()
	{

		return waxCylinderItemCount;
	}

}
