#include <iostream>
#include "students.h"

void read_students(Student *students, std::size_t size)
{
    unsigned int i;
    for (i=0; i < size; i++) {
        std::cin >> students[i].student_id >> students[i].grade_option;
        std::cin.ignore();
        std::getline(std::cin, students[i].name);
    }
}

Student *find_student(Student *students, std::size_t size, int student_id)
{
    unsigned int i;
    for (i=0; i < size; i++) {
        if (students[i].student_id == student_id) {
            return &students[i];
        }
    }
    return NULL;
}
