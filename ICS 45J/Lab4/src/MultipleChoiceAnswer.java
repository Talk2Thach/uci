// Ki Chan Min - 31225575
// Edward Xia  - 73387315


// Written by James Hardjadinata and Richert Wang
// Modified for ICS 45J Lab 4 Fall 2015

package com.example.flashcard45j;

import java.io.Serializable;

// Class defining a MultipleChoiceAnswer Object for multiple choice questions.
// Contains a string representing the correct answer and a String array containing the list of possible answers
// given to the user.
// The convention for this answer type is that the first element of the array of answers is the correct answer.
public class MultipleChoiceAnswer implements Answer, Serializable {
	private String[] answers;

	// A constructor that takes in the possible answers and assigns the appropriate values to the
	// class variables.
	public MultipleChoiceAnswer(String[] answers) {
		this.answers = answers;
	}

	// Method that returns the correct answer
	public String toString() {
		return this.answers[0];
	}

	// Method that returns the String array containing the possible answers to the user.
	public String[] getAnswerChoices() {
		return answers;
	}

	// Method that checks if the answer passed in the parameter is equal to the
	// correct answer.
	public boolean checkAnswer(String answer) {
		return this.answers[0].equals(answer);
	}

    // Method that checks if the Answer object has the correct answer.
    public boolean equals(Answer answer) {
    	return this.getClass().equals(answer.getClass()) && this.checkAnswer(answer.toString());
    }
}
