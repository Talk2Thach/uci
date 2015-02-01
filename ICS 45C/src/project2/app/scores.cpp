#include <iostream>
#include "scores.h"

double read_score(Artifact* artifacts, size_t size)
{
    unsigned int i;
    double score;
    double total_score = 0;
    for (i = 0; i < size; i++) {
        std::cin >> score;
        total_score += score / artifacts[i].points * artifacts[i].weight;
    }
    return total_score;
}

std::string grade(Student *student, double cutpoint_set[4])
{
    if (student->grade_option == 'P') {
        if (student->score >= cutpoint_set[2]) {
            return "P";
        } else {
            return "NP";
        }
    } else if (student->score >= cutpoint_set[0]) {
        return "A";
    } else if (student->score >= cutpoint_set[1]) {
        return "B";
    } else if (student->score >= cutpoint_set[2]) {
        return "C";
    } else if (student->score >= cutpoint_set[3]) {
        return "D";
    } else {
        return "F";
    }
}
