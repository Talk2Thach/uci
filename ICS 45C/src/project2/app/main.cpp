#include <iostream>
#include "artifacts.h"
#include "students.h"
#include "scores.h"

int main(int argc, const char * argv[]) {
    std::size_t artifacts_size = 0, students_size = 0, scores_size = 0, cutpoint_sets_size = 0;

    std::cin >> artifacts_size;
    Artifact *artifacts = new Artifact[artifacts_size];
    read_artifacts(artifacts, artifacts_size);

    std::cin >> students_size;
    Student *students = new Student[students_size];
    read_students(students, students_size);

    unsigned int student_id;
    std::cin >> scores_size;
    for (unsigned int i = 0; i < scores_size; i++) {
        std::cin >> student_id;
        find_student(students, students_size, student_id)->score = read_score(artifacts, artifacts_size);
    }

    delete [] artifacts;

    std::cout << "TOTAL SCORES" << std::endl;
    for (unsigned int i = 0; i < students_size; i++) {
        std::cout << students[i].student_id << ' ' << students[i].name << ' ' << students[i].score << std::endl;
    }

    std::cin >> cutpoint_sets_size;
    double cutpoint_set[4];
    for (unsigned int i = 1; i <= cutpoint_sets_size; i++) {
        for (unsigned int j = 0; j < 4; j++) {
            std::cin >> cutpoint_set[j];
        }
        std::cout << "CUTPOINT SET " << i << std::endl;
        for (unsigned int l = 0; l < students_size; l++) {
            std::cout << students[l].student_id << ' ' << students[l].name << ' ' << grade(&students[l], cutpoint_set) << std::endl;
        }
    }
    delete [] students;
    return 0;
}
