// Ki Chan Min - 31225575
// Edward Xia  - 73387315


// Written by James Hardjadinata and Richert Wang
// Modified for ICS 45J Lab 4 Fall 2015

package com.example.flashcard45j;

import java.io.Serializable;

// Class defining a TruthAnswer object for true/false questions.
// Contains a boolean field representing the correct value for this Answer
public class TruthAnswer implements Answer, Serializable {
	private boolean answer;

	// Constructor assigning the correct answer to the class field
	public TruthAnswer(boolean answer) {
		this.answer = answer;
	}

	// Method that checks if the answer passed in the parameter is equal to the
	// correct answer (checking case sensitivity if necessary).
	public boolean checkAnswer(String answer) {
		if (answer.equals("true")) {
			return this.answer == true;
		} else if (answer.equals("false")) {
			return this.answer == false;
		}
		return false;
	}

	// Method that returns the correct answer
    public String toString() {
    	return "" + this.answer;
    }

    // Method that checks if the Answer object has the correct answer.
    public boolean equals(Answer answer) {
    	return this.getClass().equals(answer.getClass()) && this.checkAnswer(answer.toString());
    }
}
