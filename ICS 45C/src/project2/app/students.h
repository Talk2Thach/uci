#ifndef __project2__students__
#define __project2__students__

#include <string>

struct Student {
    int student_id;
    char grade_option;
    std::string name;
    double score;
};

void read_students(Student *students, std::size_t size);
Student *find_student(Student *students, std::size_t size, int student_id);

#endif /* defined(__project2__students__) */
