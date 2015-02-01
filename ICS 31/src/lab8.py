#  Sheng Xia 73387315 and Qian Yuting 42376647.  ICS 31 Lab sec 11.  Lab asst 8.

from collections import namedtuple

# c
print('\n\n------------------ Part C ------------------\n\n')

Course = namedtuple('Course', 'dept num title instr units')
# Each field is a string except the number of units
ics31 = Course('ICS', '31', 'Intro to Programming', 'Kay', 4.0)
ics32 = Course('ICS', '32', 'Programming with Libraries', 'Thornton', 4.0)
wr39a = Course('Writing', '39A', 'Intro Composition', 'Alexander', 4.0)
wr39b = Course('Writing', '39B', 'Intermediate Composition', 'Gross', 4.0)
bio97 = Course('Biology', '97', 'Genetics', 'Smith', 4.0)
mgt1  = Course('Management', '1', 'Intro to Management', 'Jones', 2.0)

Student = namedtuple('Student', 'ID name level major studylist')
# All are strings except studylist, which is a list of Courses.
sW = Student('11223344', 'Anteater, Peter', 'FR', 'PSB', [ics31, wr39a, bio97, mgt1])
sX = Student('21223344', 'Anteater, Andrea', 'SO', 'CS', [ics31, wr39b, bio97, mgt1])
sY = Student('31223344', 'Programmer, Paul', 'FR', 'COG SCI', [ics32, wr39a, bio97])
sZ = Student('41223344', 'Programmer, Patsy', 'SR', 'PSB', [ics32, mgt1])

StudentBody = [sW, sX, sY, sZ]

# c.1
def Students_at_level(slist: [Student], level: str) -> [Student]:
    ''' Filter the students list with a specific level.'''
    result = []
    for s in slist:
        if s.level == level:
            result.append(s)
    return result

assert Students_at_level(StudentBody, 'FR') == [sW ,sY]
assert Students_at_level(StudentBody, 'SO') == [sX]

# c.2
def Students_in_majors(slist: [Student], mlist: [str]) -> [Student]:
    ''' Filter the students list by majors.'''
    result = []
    for s in slist:
        if s.major in mlist:
            result.append(s)
    return result

assert Students_in_majors(StudentBody, ['CS', 'PSB']) == [sW, sX, sZ]

# c.3
def Course_equals(c1: Course, c2: Course) -> bool:
    ''' Return True if the department and number of c1 match the department and
	     number of c2 (and False otherwise)
    '''
    return c1.dept == c2.dept and c1.num == c2.num

assert Course_equals(ics31, ics31)
assert not Course_equals(ics32, ics31)

def Course_on_studylist(c: Course, SL: 'list of Course') -> bool:
    ''' Return True if the course c equals any course on the list SL (where equality means matching department name and course number) and False otherwise.
    '''
    for i in SL:
        if Course_equals(c, i):
            return True
    return False

assert Course_on_studylist(ics31, sW.studylist)
assert not Course_on_studylist(ics31, sY.studylist)

def Student_is_enrolled(S: Student, department: str, coursenum: str) -> bool:
    ''' Return True if the course (department and course number) is on the student's studylist (and False otherwise)
    '''
    return Course_on_studylist(Course(department, coursenum, '', '', 0), S.studylist)

assert Student_is_enrolled(sW, 'ICS', '31')
assert not Student_is_enrolled(sW, 'ICS', '32')

def Students_in_class(slist: [Student], department: str, course_number: str) -> [Student]:
    ''' Filter the students by department name and course number.'''
    result = []
    for s in slist:
        if Student_is_enrolled(s, department, course_number):
            result.append(s)
    return result

assert Students_in_class(StudentBody, 'ICS', '31') == [sW, sX]

# c.4
def Student_names(slist: [Student]) -> [str]:
    ''' Return a list of name of given students list.'''
    return list(map(lambda s: s.name,
                           slist))

assert Student_names(StudentBody) == ['Anteater, Peter', 'Anteater, Andrea', 'Programmer, Paul', 'Programmer, Patsy']

# c.5
print('''\nA list of Students who are majors from the School of ICS (those majors are ['CS', 'CSE', 'BIM', 'INFX', 'CGS', 'SE', 'ICS'])\n''')
students_in_ics_majors = Students_in_majors(StudentBody, ['CS', 'CSE', 'BIM', 'INFX', 'CGS', 'SE', 'ICS'])
print(students_in_ics_majors)

print('''\nA list of the names of Students who are majors from the School of ICS\n''')
print(Student_names(students_in_ics_majors))

print('''\nThe number of Students who are majors from the School of ICS. This is called a reducing operation (or sometimes folding or accumulating)—it reduces a sequence down to a single value (e.g., by adding up the items)\n''')
print(len(students_in_ics_majors))

print('''\nA list of the names of seniors who are majors in the School of ICS\n''')
sr_students_in_ics_majors = Students_at_level(students_in_ics_majors, 'SR')
print(Student_names(sr_students_in_ics_majors))

print('''\nThe number of seniors who are majors from the School of ICS\n''')
print(len(sr_students_in_ics_majors))

print('''\nThe percentage of majors from the School of ICS who are seniors\n''')
print("{:.2f}%".format(len(sr_students_in_ics_majors) / len(students_in_ics_majors) * 100))

print('''\nThe number of freshmen who are majors from the School of ICS and enrolled in ICS 31\n''')
print(len(list(filter(lambda s: Student_is_enrolled(s, 'ICS', '31'),
                             Students_at_level(students_in_ics_majors, 'FR')))))

print('''\nThe average number of units that freshmen in ICS 31 are enrolled in\n''')
fr_in_ics31 = list(filter(lambda s: Student_is_enrolled(s, 'ICS', '31'),
                                 Students_at_level(StudentBody, 'FR')))
print(sum(list(map(lambda s: sum(list(map(lambda c: c.units,
                                                 s.studylist))),
                          fr_in_ics31))) / len(fr_in_ics31))
