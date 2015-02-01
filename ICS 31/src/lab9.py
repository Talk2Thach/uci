#  Sheng Xia 73387315 and Yuxuan Liu 24427400.  ICS 31 Lab sec 11.  Lab asst 9.

from random import *
from collections import namedtuple

print("\n\n--------------- Part C ---------------\n\n")



#c.1
NUMBER_OF_STUDENTS = 200
NUMBER_OF_QUESTIONS = 20
NUMBER_OF_CHOICES = 4  # 3 choices is A/B/C, 4 choices is A/B/C/D, 5 is A/B/C/D/E
GLOBAL_CONSTANT='ABCDEFGHIJK'

def generate_answers() -> str:
    '''takes a length of questions and a number of choices and return a string contains all the
    answers'''
    result = ''
    possible_choices = (GLOBAL_CONSTANT)[0:NUMBER_OF_CHOICES]
    for i in range(NUMBER_OF_QUESTIONS):
        result += choice(possible_choices)
    return result

ANSWERS = generate_answers()

#c.2
Student = namedtuple('Student', 'name answers')

def random_students() -> [Student]:
    '''takes a length of students and return a list of students'''
    result=[]
    for i in range(NUMBER_OF_STUDENTS):
        result.append(Student("Student " + str(i), generate_answers()))
    return result
#print(random_students())

#c.3
print('----------------part c.3--------------------')
print('\n\n\n')

Student = namedtuple('Student', 'name answers scores total')

def random_students()->[Student]:
    result=[]
    for i in range(NUMBER_OF_STUDENTS):
        student_answers = generate_answers()
        student_scores = []
        for j in range(NUMBER_OF_QUESTIONS):
            if student_answers[j] == ANSWERS[j]:
                student_scores.append(1)
            else:
                student_scores.append(0)
        result.append(Student("Student " + str(i), student_answers,student_scores,sum(student_scores)))
    return result

def Mean_score(students:'list of students')->int:
    '''takes a list of students and return a number of average scores of the students'''
    if len(students) == 0:
        return 0
    total=0
    for i in students:
        total += i.total
    return total/len(students)

def student_total_score(student:'Student')->int:
    '''takes a student and return the total score field'''
    return student.total

sorted_studnet=random_students()
sorted_studnet.sort( key=student_total_score, reverse = True)

for i in range(10):
    print(sorted_studnet[i].name)
print('students mean score:', "{:.2f}".format(Mean_score(sorted_studnet)))
print('\n\n\n\n\n')

#c.4
print('----------------part c.4--------------------')
def generate_weighted_student_answer(Correct_answer:str)->str:
    '''takes a correct answer from the global constants ANSWERS and return a string'''
    possible_choice = GLOBAL_CONSTANT[0:NUMBER_OF_CHOICES]+ Correct_answer*randrange(2*NUMBER_OF_CHOICES)
    return choice(possible_choice)

def generate_answers2()->str:
    '''takes a length of questions and a number of choices and return a string contains all the
    answers'''
    result = ''
    for i in range(NUMBER_OF_QUESTIONS):
        result += generate_weighted_student_answer(ANSWERS[i])
    return result

def random_students2()->[Student]:
    '''takes a length of students and return a list of students'''
    result=[]
    for i in range(NUMBER_OF_STUDENTS):
        student_answers = generate_answers2()
        student_scores = []
        for j in range(NUMBER_OF_QUESTIONS):
            if student_answers[j] == ANSWERS[j]:
                student_scores.append(1)
            else:
                student_scores.append(0)
        result.append(Student("Student " + str(i), student_answers,student_scores,sum(student_scores)))
    return result
sorted_student2=random_students2()
sorted_student2.sort( key=student_total_score, reverse = True)

print('\n\n')
for i in range(10):
    print(sorted_student2[i].name)
print('students mean score:', "{:.2f}".format(Mean_score(sorted_student2)))

#c.5
print('\n\n----------------part c.5--------------------\n\n')
def question_weights(students:[Student])->'list of number':
    '''takes a list of students and return a list of number which contains the numbers of
    incorrect students' number'''
    result=[]
    for i in range(NUMBER_OF_QUESTIONS):
        total=0
        for j in students:
            if j.scores[i] == 0:
                total+=1
        result.append(total)
    return result

QUESTION_WEIGHTS=question_weights(sorted_student2)
#print(QUESTION_WEIGHTS)

def Student_weighted_score(student:'namedtuple of student')->'namedtuple of student':
    '''takes a Student record and the list of question weights and returns that Student record with its total field changed to reflect that student's score based
    on his or her correct answers and the corresponding question weights'''
    result=[]
    for i in range(len(student.scores)):
        new_score=student.scores[i]*QUESTION_WEIGHTS[i]*NUMBER_OF_QUESTIONS/sum(QUESTION_WEIGHTS)
        result.append(new_score)
    student=student._replace(scores=result)
    student=student._replace(total=sum(result))
    return student

def students_with_weighted_score(Stu: [Student]) -> [Student]:
    '''takes a list of students and change every student's scores field to weithted score, then return a new list of students '''
    result = []
    for i in range(len(Stu)):
        result.append(Student_weighted_score(Stu[i]))
    return result

students = students_with_weighted_score(random_students2())
students.sort(key=student_total_score, reverse=True)
for i in range(10):
    print(students[i].name)
print('students mean score:', "{:.2f}".format(Mean_score(students)))


print("\n\n--------------- Part D ---------------\n\n")
print('\n\n----------------exercise 6.21--------------------\n\n')
#6.21
def ticker(filename: str):
    '''takes a string of file name and print the information from file'''
    dic = {}
    result=[]
    b = open(filename,'r')
    for i in b:
        if i.strip() != '':
            result.append(i.strip())
    b.close()
    for i in range(len(result)):
        if i % 2 == 1: # 0 based index
            dic[result[i - 1]] = result[i]
    n = input('Enter Company name:')
    if n in dic:
        print("Ticker symbol:",dic[n])
    else:
        print("Unknown Company name")

ticker(input("Input file name of NASDAQ 100 list (e.g. nasdaq.txt): "))

#6.24
print('\n\n----------------exercise 6.24--------------------\n\n')
def names():
    '''takes no input and repeatedly asks user to enter the first name of student'''
    result = []
    dic = {}
    while True:
        x = input("Enter next name: ")
        if x != '':
            result.append(x)
        else:
            for i in result:
                if i in dic.keys():
                    dic[i] += 1
                else:
                    dic[i] = 1
            for i in dic.keys():
                if dic[i] == 1:
                    print("There is 1 student named",i)
                else:
                    print('There are {:d} students named {:s}'.format(dic[i],i))
            break

names()

#6.23
print('\n\n----------------exercise 6.23--------------------\n\n')
def scaryDict(file:'file')->'file':
    '''takes a file and return a file which contain all the words in original file'''
    infile=open(file,'r')
    result=[]
    result2=[]
    table = str.maketrans('`.,:;""?/!()-_[]',
                          '                ')
    for line in infile:
        a = line.translate(table).split()
        result.extend(a)
    outfile = open('dictionary.txt','w')
    for i in result:
        if len(i)>2 and str(i[0]) not in '0123456789' :
            result2.append(i.lower())
    x=sorted(list(set(result2)))
    for i in x:
        outfile.write(str(i)+'\n')
    infile.close()

scaryDict(input("input a file name (e.g. frankenstein.txt):"))
print("Output wrote to dictionary.txt")

#6.27
print('\n\n----------------exercise 6.27--------------------\n\n')
def index(filename:'file',lst:list):
    '''takes a file and a list of words returns every words' line number in thie file'''
    infile = open(filename, 'r')
    result = []
    dic = {}
    for line in infile:
        result.append(line)
    for i in lst:
        dic[i] = []
        for j in range(len(result)):
            if i in result[j]:
                dic[i].append(str(j + 1))
    for i in dic:
        print("{:10s} {}".format(i, ", ".join(dic[i])))
    infile.close()

index(input("Input a file name (e.g. raven.txt)"), ['raven','mortal','dying','ghost','ghastly','evil','demon'])
