#  Sheng Xia 73387315 and Siyuan Ye 50942268.  ICS 31 Lab sec 11.  Lab asst 7.

print("\n\n---------- Part C ----------\n\n")

from random import randrange

def random_names(n: int) -> list:
    "Return a list of n random names"
    f_surnames = open("surnames.txt", "r")
    f_malenames = open("malenames.txt", "r")
    f_femalenames = open("femalenames.txt", "r")
    lastnames = []
    firstnames = []
    for line in f_surnames:
        lastnames.append(line.split()[0].lower().capitalize())
    f_surnames.close()
    for line in f_malenames:
        firstnames.append(line.split()[0].lower().capitalize())
    f_malenames.close()
    for line in f_femalenames:
        firstnames.append(line.split()[0].lower().capitalize())
    f_femalenames.close()

    result = []
    for i in range(n):
        result.append("{}, {}".format(lastnames[randrange(len(lastnames))], firstnames[randrange(len(firstnames))]))
    return result

print(random_names(10))

print("\n\n---------- Part D ----------\n\n")

#d

ALPHABET = "abcdefghijklmnopqrstuvwxyz"
def rotate_alphabet(n: int) -> str:
    '''Shift alphabet by n'''
    n = n % 26
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

#d.1
def Caesar_break(t: str) -> str:
    '''Try to Decrypt a string without a cipher'''
    table = str.maketrans('.,?!-$%"',"        ")
    word_list = t.translate(table).split()
    f_dictionary = open("wordlist.txt", "r")
    dictionary = []
    for line in f_dictionary:
        dictionary.append(line.strip().lower())
    f_dictionary.close()

    best_similarity = 0
    best_cipher = 0
    for i in range(26):
        possible_words_count = 0
        for word in word_list:
            if Caesar_decrypt(word, i) in dictionary:
                possible_words_count += 1
        similarity = possible_words_count / len(word_list)

        if similarity == 1:
            return Caesar_decrypt(t, i)
        elif similarity > best_similarity:
            best_similarity = similarity
            best_cipher = i
    return Caesar_decrypt(t, best_cipher)

assert Caesar_break(Caesar_encrypt("apple", randrange(26))) == "apple"
assert Caesar_break(Caesar_encrypt("hello world, hello cat.", randrange(26))) == "hello world, hello cat."

print("\n\n---------- Part E ----------\n\n")
#e
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

#e.1
def copy_file():
    '''Copy a file'''
    infile_name = input("Please enter the name of the file to copy: ")
    infile = open(infile_name, 'r')
    outfile_name = input("Please enter the name of the new copy:  ")
    outfile = open(outfile_name, 'w')
    for line in infile:
        outfile.write(line)
    infile.close()
    outfile.close()

print("Copy with no opitons")
copy_file()

#e.2 e.3 e.4
def copy_file(option: str):
    '''Copy a file with a option'''
    infile_name = input("Please enter the name of the file to copy: ")
    infile = open(infile_name, 'r')
    inlines = []
    for line in infile:
        inlines.append(line)
    infile.close()
    outfile_name = input("Please enter the name of the new copy:  ")
    outfile = open(outfile_name, 'w')

    if option == 'line numbers':
        format_string = '{:{:d}d}: {}'
        width = len(str(len(inlines)))
        for i in range(len(inlines)):
            outfile.write(format_string.format((i + 1), width, inlines[i]))
    elif option == 'Gutenberg trim':
        is_body = False
        outlines = []
        for line in inlines:
            if is_body:
                outlines.append(line)
                if line[:7] == '*** END':
                    is_body = False
                    for l in outlines:
                        outfile.write(l) # Only write to file when found an end.
                    outlines = []
            elif line[:9] == '*** START':
                outlines.append(line)
                is_body = True
    else:
        if option == 'statistics':
            stats(inlines)
        for line in inlines:
            outfile.write(line)

    outfile.close()

print("Copy with line numbers")
copy_file('line numbers')

print("Copy with Gutenberg trim")
copy_file('Gutenberg trim')

print('Copy with statistics')
copy_file('statistics')
