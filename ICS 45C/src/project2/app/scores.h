#ifndef __project2__scores__
#define __project2__scores__

#include "students.h"
#include "artifacts.h"

double read_score(Artifact* artifacts, const size_t size);
std::string grade(Student *student, double cutpoint_set[4]);

#endif /* defined(__project2__scores__) */
