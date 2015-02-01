# Sheng Xia 73387315 and Zixun Ai 63572173.  ICS 31 Lab sec 11.  Lab asst 1e and 1f.

################
# Assignment E #
################

print('Hello, Prof. Kay!')

print('1 <= 23 is', 1 <= 23)
print('14223334354 mod 3 =', 14223334354 % 3)
print('(1 + 1) * 2 / 3 ^ 4 =', (1 + 1) * 2 / 3 ** 4)



################
# Assignment F #
################

# Exercise 2.12
# =============

# a) The sum of fisrt seven positive intergers
1 + 2 + 3 + 4 + 5 + 6 + 7
# b) The average age of Sara (age 65), Fratima (57), and Mark (age 45)
(65 + 57 + 45) / 3
# c) 2 to the 20th power
2 ** 20
# d) The number of times 61 goes into 4356
4356 / 61
# e) The remainder when 4365 is divided by 61
4365 % 61


# Exercise 2.13
# =============

s1 = '-'
s2 = '+'
# (a) '-+'
s1 + s2
# (b) '–+'
s1 + s2
# (c) '+––'
s2 + s1 * 2
# (d) '+––+––'
(s2 + s1 * 2) * 2
# (e) '+––+––+––+––+––+––+––+––+––+––+'
(s2 + s1 * 2) * 10 + s2
# (f) '+–+++––+–+++––+–+++––+–+++––+–+++––'
(s2 + s1 + s2 * 3 + s1 * 2) * 5


# Exercise 2.14
# =============

s = 'abcdefghijklmnopqrstuvwxyz'
s.index('a')
s.index('c')
s.index('z')
s.index('y')
s.index('q')


# Exercise 2.15
# =============

s = 'goodbye'
# (a) The first character of string s is 'g'
s[0] == 'g'
# (b) The seventh character of s is g
s[6] == 'g'
# (c) The first two characters of s are g and a
s[0] == 'g' and s[1] == 'a'
# (d) The next to last character of s is x
s[-2] == 'x'
# (e) The midle character of s is d
s[(len(s) // 2)] == 'd'
# (f) The first and last characters of string s are equal
s[0] == s[-1]
# (g) The last 4 characters of string s match the string 'tion'
s[-5:-1] == 'tion'


# Exercise 2.16
# =============

# (a) Assign 6 to variable a and 7 to variable b.
a = 6
b = 7
# (b) Assign to variable c the average of variables a and b.
c = (a + b) / 2
# (d) Assign to variables first, middle and last the strings 'John', 'Fitzgerald', and 'Kennedy'.
first = 'John'
middle = 'Fitzgerald'
last = 'Kenndy'
# (e) Assign to variable fullname the concatenation of string variables first, middle, and last. Make sure you incorporate blank spaces appropriately.
fullname = first + ' ' + middle + ' ' + last


# Exercise 2.17
# =============

# (a) The sum of 17 and -9 is less than 10.
(17 + -9) < 10
# (c) c is no more than 24.
c < 24
# (d) 6.75 is between the values of integers a and b.
(a < 6.75 and b > 6.75) or (a > 6.75 and b < 6.75)
# (e) The length of string middle is larger than the length of string first and smaller than the length string last.
len(middle) > len(first) and len(middle) < len(last)


# Exercise 2.21
# =============
s = 'top'
s[::-1]
# s[start:end:step]
# s[::-1] is an abberevation for s[-1:(-len(s)-1):-1]
# because the step is -1, it slices in the reverse order one by one character
# and because we didn't decare the start and end, it just goes through the whole string

