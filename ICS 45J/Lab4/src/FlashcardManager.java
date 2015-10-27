// Ki Chan Min - 31225575
// Edward Xia  - 73387315

// Written by James Hardjadinata and Richert Wang
// Modified for ICS 45J Lab 4 Fall 2015

package com.example.flashcard45j;

import java.util.*;
import java.io.*;
import java.net.URL;
import java.net.URLConnection;

public class FlashcardManager {
    private ArrayList<Card> cardList = new ArrayList<Card>(); // Need an ArrayList reference for Android intent passing.
    private Set<String> types = new HashSet<String>(); //A set of the card types within the game.

    // Each line a form of: {answer type};{difficulty};{question};{answer}.
    // This method takes in a File IO InputStream representing the cards.txt
    // file in your assets folder. It takes the file, and converts each line
    // in the file into specific cards using the Card.cardFactory to convert
    // the information into actual Card objects. Returns an ArrayList<Card>
    // representing the constructed Cards from the text file.
    public static ArrayList<Card> readQuestions(InputStream is) {
		Scanner in = new Scanner(is);

		ArrayList<Card> results = new ArrayList<Card>();
		while (in.hasNextLine())
		{
			String line = in.nextLine();
			results.add(Card.cardFactory(line.split(";")));
			System.out.println(line);
		}

		if (in != null) {
			in.close();
		}

		return results;
    }

    // Overloaded method that takes in a Uniform Resource Locator (url)
    // to a .txt file containing the information for constructing cards.
    // Returns an ArrayList<Card> representing the constructed Cards from
    // the text file.
    // If an error opening obtaining the file occurs, catch the IOException
    // and return an empty ArrayList of Cards.
    public static ArrayList<Card> readQuestions(String url) {
		try {
			URL remoteFileLocation = new URL(url);
			URLConnection connection = remoteFileLocation.openConnection();
			return FlashcardManager.readQuestions(connection.getInputStream());
		}
		catch (IOException e) {
			return new ArrayList<Card>();
		}
		catch (Exception e) {
			System.err.println(e.toString());
			return new ArrayList<Card>();
		}
    }

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////// DO NOT MODIFY METHODS BELOW THIS COMMENT ////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

    // Default Constructor.
    public FlashcardManager() {}

    //Constructor to be called for reading from an InputStream (file).
    //Calls updateCardTypes() since it mutates the card list.
    public FlashcardManager(InputStream is) {
        this.cardList.addAll(readQuestions(is));
        this.updateCardTypes();
    }

    //Returns a subset of the passed array which will only consist of the given difficulty.
    public void difficultySelectSubSet(int selectFlag) throws IllegalArgumentException {
        //If the difficulty argument is 0, then there is no selected difficulty and we take no subset.
        if(selectFlag == 0)
            return;

        //Otherwise, we set the card list to a subset of itself with the given difficulty.
        //We also call updateCardTypes() since we've mutated the card list.
        ArrayList<Card> filteredCardList = new ArrayList<Card>();
        for(Card card : cardList)
            if(card.getDifficulty() == selectFlag)
                filteredCardList.add(card);
        this.cardList = filteredCardList;
        updateCardTypes();
    }

    //Sorts the backing card list by the given parameters for sorting by difficulty and type.
    //This is a method that given (sortFlag,sortByType) will call the difficulty sort and type sort methods.
    //We first take the subset of the card list according to the chosen difficulty, then sort the subset by types.
    //This is currently unused in the program.
    public void settingsSort(int sortFlag, boolean sortByType) throws IllegalArgumentException {
        switch (sortFlag) {
            case 0:
                break;
            case 1:
                this.cardList = difficultySort(this.cardList, true);
                break;
            case 2:
                this.cardList = difficultySort(this.cardList, false);
                break;
            default:
                throw new IllegalArgumentException();
        }
        if (sortByType) {
            ArrayList<Card> finalSortedList = new ArrayList<Card>();
            Collections.sort(this.cardList, new Comparator<Card>() {
                public int compare(Card c1, Card c2) {
                    return c1.getType().compareTo(c2.getType());
                }
            });
            for (String type : types) {
                ArrayList<Card> subList = new ArrayList<Card>();
                for (Card card : this.cardList)
                    if (type.equals(card.getType()))
                        subList.add(card);
                subList = difficultySort(subList, sortByType);
                finalSortedList.addAll(subList);
            }
            this.cardList = finalSortedList;
        }
    }

    //Sort by difficulty - we check if sorting in ascending/descending, then sort using a lambda Comparator implementation.
    private ArrayList<Card> difficultySort(ArrayList<Card> cardList, boolean sortByAscendingDifficulty) {
        if(sortByAscendingDifficulty)
            Collections.sort(this.cardList, new Comparator<Card>() {
                public int compare(Card c1, Card c2) { return c1.getDifficulty() - c2.getDifficulty(); }
            });
        else
            Collections.sort(this.cardList, new Comparator<Card>() {
                public int compare(Card c1, Card c2) { return c2.getDifficulty() - c1.getDifficulty(); }
            });
        return cardList;
    }

    //The method for dynamically declaring any number of types, replaces the above counting method.
    //Must be called everytime the card list is updated!
    public HashMap<String,Integer> countCardTypes() {
        updateCardTypes(); // We are ensured that there will be no improper mappings for the returned map.
        HashMap<String,Integer> typeCounts = new HashMap<String,Integer>();
        for(String type : types)
            typeCounts.put(type,0);

        for(Card card : cardList)
            typeCounts.put(card.getType(),typeCounts.get(card.getType())+1);

        return typeCounts;
    }

    //Method to update the backing set of types. Should be called everytime the backing card list is changed.
    //Creates a new type array just in case the card list does not retain the same cards.
    private void updateCardTypes() {
        Set<String> types = new HashSet<String>();
        for(Card card: cardList)
            types.add(card.getType());
        this.types = types;
    }

    public Set<String> getTypes() { return this.types; }

    public ArrayList<Card> getCardList() { return this.cardList; }

    //Replaces the card list and updates the backing set of card types.
    public void setCardList(ArrayList<Card> list) {
        this.cardList = list;
        this.updateCardTypes();
    }

    //Adds the given card list and updates the backing set of card types, checking and skipping duplicates.
    public void addCardList(ArrayList<Card> list) {
        boolean foundCopy = false;
        for(Card card : list) {
            for(int i = 0; i < cardList.size(); i++)
                if(cardList.get(i).equals(card))
                    foundCopy = true;
            if(!foundCopy)
                cardList.add(card);
            foundCopy = false;
        }

        this.updateCardTypes();
    }
}
