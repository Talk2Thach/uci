#  Sheng Xia 73387315 and Victor Zhang 46812269.  ICS 31 Lab sec 11.  Lab asst 6.
print("\n\n-------------------------Part C-----------------------------\n\n")

#c.1
from random import randrange

for i in range(50):
    print(randrange(11))

print("\n\n")
for i in range(50):
    print(randrange(1,7))
print("\n\n")

#c.2

def roll2dice() -> int:
    '''Return the sum of the two dice'''
    return randrange(1,7) + randrange(1,7)

for i in range(50):
    print(roll2dice())
print("\n\n")

#c.3

def distribution_of_rolls(n: int):
    '''Print the distribution of the result for the rolls of n times'''
    result = [0,0,0,0,0,0,0,0,0,0,0,0,0]
    format_string = "{:2d}:    {:2d} ({:4.1f}%) {}"
    for i in range(n):
        result[roll2dice()] += 1
    for i in range(2,13):
        print(format_string.format(i, result[i], (result[i] / n * 100), "*" * result[i]))
    print("-----------------------------")
    print("     ", n, "rolls")
distribution_of_rolls(200)

print("\n\n-------------------------Part D-----------------------------\n\n")

#d.1
ALPHABET = "abcdefghijklmnopqrstuvwxyz"
def rotate_alphabet(n: int) -> str:
    '''Shift alphabet by n'''
    n = n % 26 #d.3
    return ALPHABET[n:] + ALPHABET[0:n]

assert rotate_alphabet(0) == "abcdefghijklmnopqrstuvwxyz"
assert rotate_alphabet(1) == "bcdefghijklmnopqrstuvwxyza"
assert rotate_alphabet(27) == "bcdefghijklmnopqrstuvwxyza"

def Caesar_encrypt(t: str, n: int) -> str:
    '''Encrypt a string by a cipher(int) and return'''
    t = t.lower()
    table = str.maketrans(ALPHABET, rotate_alphabet(n))
    return t.translate(table)

assert Caesar_encrypt("test", 1) == "uftu"

def Caesar_decrypt(t: str, n: int) -> str:
    '''Decrypt a string by a cipher(int) and return'''
    t = t.lower()
    table = str.maketrans(rotate_alphabet(n), ALPHABET)
    return t.translate(table)

assert Caesar_decrypt(Caesar_encrypt("test", 1), 1) == "test"

print("\n\n-------------------------Part E-----------------------------\n\n")

#e.1

test_strings = [ "Four score and seven years ago, our fathers brought forth on",
  "this continent a new nation, conceived in liberty and dedicated",
  "to the proposition that all men are created equal.  Now we are",
  "   engaged in a great 		civil war, testing whether that nation, or any",
  "nation so conceived and so dedicated, can long endure.        " ]

def print_line_numbers(list_of_strings: list):
    '''Print the strings with line numbers'''
    longest = len(str(len(list_of_strings)))
    format_string = "{:{:d}d}: {}"
    for i in range(len(list_of_strings)):
        print(format_string.format((i + 1), longest, list_of_strings[i]))

print_line_numbers(test_strings)

#e2
print("\n\n------------ E.2 ---------------\n\n")
def stats(los: list) -> list:
    '''Print the stats of a list of strings'''
    lines_in_list = len(los)
    empty_lines = 0
    total_chars = 0
    for i in los:
        total_chars += len(i)
        if len(i.split()) == 0:
            empty_lines += 1
    average_char_per_line = total_chars/lines_in_list
    average_char_per_nline = total_chars/(lines_in_list - empty_lines)
    width_of_lines = len(str(lines_in_list)) + 2
    width_of_average_char = len("{:.1f}".format(average_char_per_nline))
    width = max(width_of_lines, width_of_average_char)
    format_string = "{:{:d}d}   {}"
    format_string2 = "{:{:d}.1f} {}"
    print(format_string.format(lines_in_list, (width - 2), "lines in the list"))
    print(format_string.format(empty_lines, (width - 2), "empty lines"))
    print(format_string2.format(average_char_per_line, width, "average characters per line"))
    print(format_string2.format(average_char_per_nline, width, "average characters per non-empty line"))

stats(test_strings)
print()
stats(["a","a","a","a","a","a","a","a","a","","a","a","a","a","a","a","a","a","a","a"])

#e.3
def list_of_words(los: list) -> list:
    '''Return a list of words from a list of strings'''
    result = []
    table = str.maketrans('.,?!-$%"',"        ")
    for i in los:
        result.extend(i.translate(table).split())
    return result

assert list_of_words(test_strings) == ['Four', 'score', 'and', 'seven', 'years', 'ago', 'our', 'fathers', 'brought', 'forth', 'on', 'this', 'continent', 'a', 'new', 'nation', 'conceived', 'in', 'liberty', 'and', 'dedicated', 'to', 'the', 'proposition', 'that', 'all', 'men', 'are', 'created', 'equal', 'Now', 'we', 'are', 'engaged', 'in', 'a', 'great', 'civil', 'war', 'testing', 'whether', 'that', 'nation', 'or', 'any', 'nation', 'so', 'conceived', 'and', 'so', 'dedicated', 'can', 'long', 'endure']
