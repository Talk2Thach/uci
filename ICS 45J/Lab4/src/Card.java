// Ki Chan Min - 31225575
// Edward Xia  - 73387315


// Written by James Hardjadinata and Richert Wang
// Modified for ICS 45J Lab 4 Fall 2015

package com.example.flashcard45j;

import java.io.Serializable;

//This is the implementation for the card class.
//A card consists of a string type, string question, one of the types of answers, and the difficulty as an int variable.

// The Card class represents a FlashCard used for this application.
// All cards consists of a String question and a String question type (i.e. subject such as "Inheritance",
// "Exceptions", "Loops", etc). Each card has a correct Answer associated with it and a difficulty
// (between 1 - 3). For this lab, you can assume all Cards have a difficulty of "1".
public class Card implements Serializable {

	// *** Declare class variables here ***
	private String question;
	private Answer answer;
	private int difficulty;
	private String type;

	// Constructor taking in to necessary fields to assign to the Card's class variables.
	public Card(String question, Answer answer, int difficulty, String type) {
		// Provide your implementation here
		this.question = question;
		this.answer = answer;
		this.difficulty = difficulty;
		this.type = type;
	}

	// Copy constructor
	public Card(Card c) {
		this.question = c.question;
		this.answer = c.answer;
		this.difficulty = c.difficulty;
		this.type = c.type;
	}

	// Getter method returning the Card's Question.
	public String getQuestion() {
		return question;
	}

	// Getter method returning the Card's Answer
	public Answer getAnswer() {
		return answer;
	}

	// Getter method returning the Card's Difficulty
	public int getDifficulty() {
		return difficulty;
	}

	// Getter method returning the Card's Type
	public String getType() {
		return type;
	}

	// Checks if two cards are equal if they have the same question, question type, and answer.
	public boolean equals(Card card) {
		return this.question.equals(card.question) &&
				this.answer.equals(card.answer) &&
				this.difficulty == card.difficulty &&
				this.type.equals(card.type);
	}

	// The cardFactory method takes in a String array containing multiple pieces of information that is required
	// to construct specific cards.
	// Strings passed a form of: {question};{difficulty};{question type};{answer type};{answer};{case sensitive if applicable}.
	// You should use the card type to construct the appropriate Answer object.
	// Once all pieces are obtained, a new Card is constructed and returned.
	// If the answer type is unrecognizable, then throw an IllegalArgumentException()
	public static Card cardFactory(String[] args) throws IllegalArgumentException {
		if (args.length == 0 || args.length < 5) {
			throw new IllegalArgumentException();
		}
		String question = args[0];
		int difficulty = Integer.parseInt(args[1]);
		String type = args[2];
		switch (args[3]) { // answer type
		case "TF":
			switch (args[4]) { // answer
			case "true":
				return new Card(question, new TruthAnswer(true), difficulty, type);
			case "false":
				return new Card(question, new TruthAnswer(false), difficulty, type);
			default:
				throw new IllegalArgumentException();
			}
		case "SA":
			if (args.length < 6) {
				throw new IllegalArgumentException();
			}
			switch (args[5]) { // case sensitive
			case "true":
				return new Card(question, new ShortAnswer(args[4], true), difficulty, type);
			case "false":
				return new Card(question, new ShortAnswer(args[4], false), difficulty, type);
			default:
				throw new IllegalArgumentException();
			}
		case "MC":
			return new Card(question, new MultipleChoiceAnswer(args[4].split(",")), difficulty, type);
		default:
			throw new IllegalArgumentException();
		}
	}
}
