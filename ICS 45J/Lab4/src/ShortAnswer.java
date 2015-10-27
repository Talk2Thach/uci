// Ki Chan Min - 31225575
// Edward Xia  - 73387315


// Written by James Hardjadinata and Richert Wang
// Modified for ICS 45J Lab 4 Fall 2015

package com.example.flashcard45j;

import java.io.Serializable;

// Class defining a ShortAnswer object for short answer questions.
// Contains a String representing the correct answer and a boolean field
// representing if the answer is case sensitive or not.
public class ShortAnswer implements Answer, Serializable {
	private String answer;
	private boolean caseSensitive;

    // Constructor that sets the answer and caseSensitive flag to the
    // class variables.
	public ShortAnswer(String answer, boolean caseSensitive) {
		this.answer = answer;
		this.caseSensitive = caseSensitive;
	}

	// Method that checks if the answer passed in the parameter is equal to the
	// correct answer (checking case sensitivity if necessary).
	public boolean checkAnswer(String answer) {
		if (caseSensitive) {
			return this.answer.equals(answer);
		} else {
			return this.answer.equalsIgnoreCase(answer);
		}
	}

	// Method that returns the correct answer
    public String toString() {
    	return this.answer;
    }

    // Method that checks if the Answer object has the correct answer.
    public boolean equals(Answer answer) {
    	return this.getClass().equals(answer.getClass()) && this.checkAnswer(answer.toString()) && answer.checkAnswer(this.answer);
    }
}
