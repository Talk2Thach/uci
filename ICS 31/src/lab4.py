# Kaining Yang 41559503 and Sheng Xia 73387315.  ICS 31 Lab sec 11.  Lab asst 4.

def Part(n: str):
  print()
  print()
  print('---------- Part (', n, ') ----------', sep='')
  print()

#########
Part('c')
#########
#
#
# 3.17
#
#
print('---------- 3.17 ----------')
a, b, c = 3, 4, 5
if a < b:
  print('(a):OK')
if c < b:
  print('(b):OK')
if a + b == c:
  print('(c):OK')
if a ** 2 + b ** 2 == c ** 2:
  print('(d):OK')
#
#
# 3.18
#
#
print('---------- 3.18 ----------')
a, b, c = 3, 4, 5
if a < b:
  print('(a):OK')
else:
  print("(a):NOT OK")
if c < b:
  print('(b):OK')
else:
  print("(b):NOT OK")
if a + b == c:
  print('(c):OK')
else:
  print("(c):NOT OK")
if a ** 2 + b ** 2 == c ** 2:
  print('(d):OK')
else:
  print("(d):NOT OK")
#
#
# 3.19
#
#
print('---------- 3.19 ----------')
lst = ['January', 'February', 'March']
for i in lst:
  print(i[0:3])
#
#
# 3.20
#
#
print('---------- 3.20 ----------')
lst = [2, 3, 4, 5, 6, 7, 8, 9]
for i in lst:
  if i ** 2 % 8 == 0:
    print(i)

#########
Part('d')
#########

def is_vowel(n: str) -> bool:
  "Return True if character is a vowel and False otherwise"
  return n in "aeiouAEIOU"


assert is_vowel('a')
assert is_vowel("E")
assert not is_vowel("x")
#
#
# d.2
#
#
print('---------- d.2 ----------')
def print_nonvowels(n: str):
  "Print all non-vowel characters"
  print('Original word:', n)
  for i in n:
    if is_vowel(i)==False:
      print(i)

print_nonvowels("real")
print_nonvowels("abandon")
print_nonvowels("subway")
print_nonvowels("AEQUWBFE")
#
#
# d.3
#
#
print('---------- d.3 ----------')
def nonvowels(n: str) -> str:
  "Return a string containing all non-vowel characters"
  result = ""
  for i in n:
    if not is_vowel(i):
      result = result + i
  return result

assert nonvowels("rea l") == 'r l'
assert nonvowels("aba_ndon") == 'b_ndn'

#
#
# d.4
#
#
print('---------- d.4 ----------')
def consonants(n: str) -> str:
  "Return a string containing all the letters in the parameter string that are not vowels"
  result = nonvowels(n)
  result1 = ""
  for a in result:
    if (ord(a) >= 65 and ord(a) <= 91) or (ord(a) >= 97 and ord(a) <= 123):
      result1 = result1 + a
  return result1

assert consonants("nefhbw-_54u21233")=='nfhbw'
assert consonants("NEFHBW-_54U21233")=='NFHBW'
#
#
# d.5
#
#
print('---------- d.5 ----------')
def select_letters(x: str,y: str)->str:
  """Return all vowels if the first parameter is 'c',
     return all consonants if the first parameter is 'v',
     return an empty string if the first parameter is anything else."""
  result = ''
  if x == 'v':
    for i in y:
      if is_vowel(i):
        result = result + i
  if x == 'c':
    result = consonants(y)
  return result

assert select_letters('c','cehbdxaiwn123') == 'chbdxwn'
assert select_letters('v','cehbdxaiwn123') == "eai"
assert select_letters('a','cehbdxaiwn123') == ""


#
#
# d.6
#
#
print('---------- d.6 ----------')
def hide_vowels(n: str) -> str:
  "Replace all vowels with '-' and return the string."
  result = ""
  for i in n:
    if is_vowel(i):
      result = result + "-"
    else:
      result = result + i
  return result

assert hide_vowels("asderdgcyv") == '-sd-rdgcyv'
assert hide_vowels("addwecbxiohyb") == '-ddw-cbx--hyb'

#########
Part('e')
#########
#
#
# 3.22
#
#
print('---------- 3.22 ----------')
lst = eval(input("Enter list of words: "))
for i in lst:
  if i != 'secret':
    print(i)

#
#
# 3.23
#
#
print('---------- 3.23 ----------')
lst = eval(input("Enter list: "))
for i in lst:
  if i[0] in 'ABCDEFGHIJKLM':
    print(i)

#########
Part('f')
#########
from collections import namedtuple

Restaurant = namedtuple('Restaurant', 'name cuisine phone dish price')
# Restaurant attributes: name, kind of food served, phone number,
#	best dish, price of that dish

R1 = Restaurant("Taillevent", "French", "343-3434", "Escargots", 24.50)
R2 = Restaurant("La Tour D'Argent", "French", "343-3344", "Ris de Veau", 48.50)
R3 = Restaurant("Pascal", "French", "333-4444", "Bouillabaisse", 32.00)
R4 = Restaurant("Thai Touch", "Thai", "444-3333", "Mee Krob", 10.95)
R5 = Restaurant("Thai Dishes", "Thai", "333-4433", "Paht Woon Sen",  8.50)
R6 = Restaurant("Thai Spoon", "Thai", "334-3344", "Mussamun", 9.00)
R7 = Restaurant("McDonald's", "Burgers", "333-4443", "Big Mac", 3.95)
R8 = Restaurant("Burger King", "Burgers", "444-3344", "Whopper", 3.75)
R9 = Restaurant("Wahoo's", "Fish Tacos", "443-4443", "Mahi Mahi Burrito", 7.50)
R10 = Restaurant("In-N-Out Burger", "Burgers", "434-3344", "Cheeseburger", 2.50)
R11 = Restaurant("The Shack", "Burgers", "333-3334", "Hot Link Burger", 4.50)
R12 = Restaurant("Gina's", "Pizza", "334-4433", "Combo Pizza", 12.95)
R13 = Restaurant("Peacock, Room", "Indian", "333-4443", "Rogan Josh", 12.50)
R14 = Restaurant("Gaylord", "Indian", "333-3433", "Tandoori Chicken", 13.50)
R15 = Restaurant("Mr. Chow", "Chinese", "222-3333", "Peking Duck", 24.50)
R16 = Restaurant("Chez Panisse", "California", "222-3322", "Grilled Duck Breast", 25.00)
R17 = Restaurant("Spago", "California", "333-2222", "Striped Bass", 24.50)
R18 = Restaurant("Sriped Bass", "Seafood", "333-2233", "Cedar Plank Salmon", 21.50)
R19 = Restaurant("Golden Pagoda", "Chinese", "232-3232", "Egg Foo Young", 8.50)
R20 = Restaurant("Langer's", "Delicatessen", "333-2223", "Pastrami Sandwich", 11.50)
R21 = Restaurant("Nobu", "Japanese", "335-4433", "Natto Temaki", 5.50)
R22 = Restaurant("Nonna", "Italian", "355-4433", "Stracotto", 25.50)
R23 = Restaurant("Jitlada", "Thai", "324-4433", "Paht Woon Sen", 15.50)
R24 = Restaurant("Nola", "New Orleans", "336-4433", "Jambalaya", 5.50)
R25 = Restaurant("Noma", "Modern Danish", "337-4433", "Birch Sap", 35.50)
R26 = Restaurant("Addis Ababa", "Ethiopian", "337-4453", "Yesiga Tibs", 10.50)


RL = [R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15, R16,
	R17, R18, R19, R20, R21, R22, R23, R24, R25, R26]

#
#
# f.1
#
#
print('---------- f.1 ----------')
def alphabetical(n: list) -> list:
  'Return alphabetical sorted list of restaurants'
  return sorted(n)

#
#
# f.2
#
#
print('---------- f.2 ----------')
def alphabetical_names(n: str) -> list:
  'Return alphabetical sorted list of names of restaurants'
  lst = []
  for i in alphabetical(n):
    lst.append(i.name)
  return lst

#
#
# f.3
#
#
print('---------- f.3 ----------')
def all_Thai(n: list) -> list:
  'Return a list of Thai restaurants'
  lst = []
  for i in n:
    if i.cuisine == "Thai":
      lst.append(i)
  return lst
#
#
# f.4
#
#
print('---------- f.4 ----------')
def select_cuisine(n: list, m: str) -> list :
  'Return a list of restaruants which have the cuisine'
  lst = []
  for i in n:
    if i.cuisine == m:
      lst.append(i)
  return lst

#
#
# f.5
#
#
print('---------- f.5 ----------')
def select_cheaper(n: list, m: float) -> list:
  'Return a list of restaruants whose price are lower than m'
  lst = []
  for i in n:
    if i.price < m:
      lst.append(i)
  return lst

#
#
# f.6
#
#
print('---------- f.6 ----------')
def average_price(n:list)->float:
  'Return the average price of all restaruants in the list'
  sum = 0
  for i in n:
    sum = sum + i.price
  average = sum / len(n)
  return average

#
#
# f.7
#
#
print('---------- f.7 ----------')
print(average_price(select_cuisine(RL, 'Indian')))

#
#
# f.8
#
#
print('---------- f.8 ----------')
print(average_price(select_cuisine(RL, 'Thai') + select_cuisine(RL, 'Chinese')))

#
#
# f.9
#
#
print('---------- f.9 ----------')
print(alphabetical_names(select_cheaper(RL, 15.00)))

#########
Part('g')
#########
#
#
# 3.25
#
#
print('---------- 3.25 ----------')
n = int(input("Enter n:"))
for i in range(4):
  print(n * i)

#
#
# 3.26
#
#
print('---------- 3.26 ----------')
n = int(input("Enter n:"))
for i in range(n):
  print(i ** 2)
