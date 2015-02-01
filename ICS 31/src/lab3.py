#  Sheng Xia 73387315 and Tianya Chen 59359881.  ICS 31 Lab sec 11.  Lab asst 3.

def Part(n: str):
  print()
  print()
  print('---------- Part (', n, ') ----------', sep='')
  print()

#########
Part('c')
#########

# c 3.36
def abbreviation(day: str) -> str:
  "Return abbreviation for a day"
  return day[0:2]
assert abbreviation("Tuesday") == "Tu"
print(abbreviation(input('Please input the day (e.g. Tuesday): ')))

# c 3.43
def distance(time: float) -> float:
  "Return distance"
  return time * 340.29 / 1000
assert distance(3) == 1.0208700000000002
assert distance(6) == 2.0417400000000003
print(distance(float(input('Please input the time: '))))

# c 3.35
import math
def points(x1: float, y1: float, x2: float, y2: float):
  "Print slope and distance"
  if x1 == x2:
    print("The slope is infinity and distance is", abs(y2 - y1))
  else:
    slope = (y2 - y1) / (x2 - x1)
    distance = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
    print('The slope is', slope, 'and the distance is', distance)
x1=int(input("Please input x1: "))
y1=int(input("Please input y1: "))
x2=int(input("Please input x2: "))
y2=int(input("Please input y2: "))
points(x1, y1, x2, y2)

# c 3.44
import turtle
def polygon(n: int):
  "Draw polygons"
  if  n >= 3:
    s = turtle.Screen()
    t = turtle.Turtle()
    for i in range(n):
      t.forward(100)
      t.left(360 / n)
    s.exitonclick()
  else:
    print("Sides < 3, not draw anything.")

polygon(int(input("How many sides does the polygon have? ")))

#########
Part('d')
#########

# d 3.32
def pay(wage: int, hour: int) -> int:
  "Calculate the wage"
  return (min(hour, 40) * wage) + (max((hour - 40), 0) * wage * 1.5)
assert pay(10, 10) == 100
assert pay(10, 35) == 350
assert pay(10, 45) == 475

wage = int(input("Please input the wage for an hour: "))
hour = int(input("Please input the hours:  "))
print('The total wages for', hour, 'hour(s) is', pay(wage, hour))

#########
Part('e')
#########

# e
from collections import namedtuple
Restaurant = namedtuple('Restaurant', 'name cuisine phone dish price')
# Restaurant attributes: name, kind of food served, phone number, best dish, price of that dish
RC = [
    Restaurant("Thai Dishes", "Thai", "334-4433", "Mee Krob", 12.50),
    Restaurant("Nobu", "Japanese", "335-4433", "Natto Temaki", 5.50),
    Restaurant("Nonna", "Italian", "355-4433", "Stracotto", 25.50),
    Restaurant("Jitlada", "Thai", "324-4433", "Paht Woon Sen", 15.50),
    Restaurant("Nola", "New Orleans", "336-4433", "Jambalaya", 5.50),
    Restaurant("Noma", "Modern Danish", "337-4433", "Birch Sap", 35.50),
    Restaurant("Addis Ababa", "Ethiopian", "337-4453", "Yesiga Tibs", 10.50) ]

# e.1
def restaurant_price(restaurant: Restaurant):
  return restaurant.price

assert restaurant_price(RC[0]) == 12.50
assert restaurant_price(RC[1]) == 5.50

# e.2
RC.sort(key=restaurant_price)
print(RC)
print()

# e.3
RC1 = [
    Restaurant("Thai Dishes", "Thai", "334-4433", "Mee Krob", 12.50),
    Restaurant("Nobu", "Japanese", "335-4433", "Natto Temaki", 5.50),
    Restaurant("Nonna", "Italian", "355-4433", "Stracotto", 25.50),
    Restaurant("Jitlada", "Thai", "324-4433", "Paht Woon Sen", 15.50),
    Restaurant("Nola", "New Orleans", "336-4433", "Jambalaya", 5.50),
    Restaurant("Noma", "Modern Danish", "337-4433", "Birch Sap", 35.50),
    Restaurant("Addis Ababa", "Ethiopian", "337-4453", "Yesiga Tibs", 10.50) ]
def costliest(restaurant_list: list):
  restaurant_list.sort(key=restaurant_price)
  return restaurant_list[-1].name

assert costliest(RC1) == 'Noma'
print(costliest(RC1))
print()

# e.4
RC2 = [
    Restaurant("Thai Dishes", "Thai", "334-4433", "Mee Krob", 12.50),
    Restaurant("Nobu", "Japanese", "335-4433", "Natto Temaki", 5.50),
    Restaurant("Nonna", "Italian", "355-4433", "Stracotto", 25.50),
    Restaurant("Jitlada", "Thai", "324-4433", "Paht Woon Sen", 15.50),
    Restaurant("Nola", "New Orleans", "336-4433", "Jambalaya", 5.50),
    Restaurant("Noma", "Modern Danish", "337-4433", "Birch Sap", 35.50),
    Restaurant("Addis Ababa", "Ethiopian", "337-4453", "Yesiga Tibs", 10.50) ]
def costliest2(restaurant_list: list):
  return sorted(restaurant_list, key=restaurant_price, reverse=True)[0].name

assert costliest2(RC2) == 'Noma'
print(costliest2(RC2))
print()

#########
Part('f')
#########

# f
from collections import namedtuple
Book = namedtuple('Book', 'author title genre year price instock')
BSI = [Book('Charles Dickens', 'A Tale of Two Cities', 'Social criticism', 1859, 3.6, 100),
       Book('J. R. R. Tolkien', 'The Lord of the Rings', 'Fiction', 1954, 14.79, 200),
       Book('Antoine de Saint-Exupéry', 'The Little Prince', 'Novel', 1943, 8.99, 300),
       Book('Agatha Christie', 'And Then There Were None', 'Fiction', 1939, 6.29, 400),
       Book('J. R. R. Tolkien', 'The Hobbit', 'Fiction', 1937, 14.99, 500),
       Book('Ljubomir Perkovic', 'Introduction to Computing Using Python', 'Technology', 2011, 77, 600)]

# f.1
print('BSI -> titles:')
for item in BSI:
  print(item.title)
print()

# f.2
print('BSI -> titles(alphabetical order):')
def book_title(book: Book):
  return book.title
for item in sorted(BSI, key=book_title):
  print(item.title)
print()

# f.3
for i in range(len(BSI)):
  BSI[i] = BSI[i]._replace(price = BSI[i].price * 1.10)
print('BSI price up:')
print(BSI)
print()

# f.4
print('Book in technology genre:')
for item in BSI:
  if item.genre == "Technology":
    print(item.title)
print()

# f.5
books_published_before_2000 = []
books_published_2000_or_later = []
for item in BSI:
  if item.year < 2000:
    books_published_before_2000.append(item)
  else:
    books_published_2000_or_later.append(item)
number_before_2000 = len(books_published_before_2000)
number_2000_or_later = len(books_published_2000_or_later)
if number_before_2000 == number_2000_or_later:
  print('Same! (', number_2000_or_later, ' vs ', number_before_2000, ')', sep='')
elif number_before_2000 < number_2000_or_later:
  print('More books 2000 or later (', number_2000_or_later, ' vs. ', number_before_2000, ')', sep='')
else:
  print('More books before 2000 (', number_before_2000, ' vs. ', number_2000_or_later, ')', sep='')

print()

# f.6
def inventory_value(book: Book):
  return book.price * book.instock

def top_value(book_list: list):
  return sorted(book_list, key=inventory_value, reverse=True)[0]

top_valued_book = top_value(BSI)
print('The highest-value book is', top_valued_book.title, 'by', top_valued_book.author, 'at a value of $', inventory_value(top_valued_book), '.')
print()

#########
Part('g')
#########
import turtle
import math
def draw_eye(x: int, y: int, color: str):
  t = turtle.Turtle()
  t.speed(0)
  t.pensize(3)
  t.penup()
  t.setx(50 * math.sqrt(3) + x)
  t.sety(50 + y)
  t.pendown()
  t.fillcolor('#FFFAF0')
  t.begin_fill()
  t.left(120)
  t.circle(100, 120)
  t.left(60)
  t.circle(100, 120)
  t.end_fill()
  t.penup()
  t.left(300)
  t.setx(x)
  t.sety(y)
  t.pendown()
  t.pensize(2)
  t.fillcolor('#FFFFFF')
  t.begin_fill()
  t.circle(50)
  t.end_fill()
  t.pensize(1)
  t.penup()
  t.left(90)
  t.forward(50)
  t.pencolor(color)
  for i in range(30):
    t.pendown()
    t.forward(50)
    t.penup()
    t.left(180)
    t.forward(50)
    t.left(192)
  t.dot(31, 'black')
  t.right(45)
  t.forward(10)
  t.dot(20, 'white')
  t.hideturtle()

def draw_nose(x: int, y: int, size: int):
  t = turtle.Turtle()
  t.speed(0)
  t.penup()
  t.setx(x + size)
  t.sety(y - size)
  t.pendown()
  t.pensize(3)
  t.setheading(90)
  t.fillcolor('#6495ED')
  t.begin_fill()
  t.circle(size, 180)
  t.setheading(240)
  t.forward(1.5 * math.sqrt(3) * size)
  t.setheading(270)
  t.circle((1 + 3 / 4 * math.sqrt(3)) * size, 180)
  t.setheading(120)
  t.forward(1.5 * math.sqrt(3) * size)
  t.end_fill()
  t.hideturtle()

def draw_mouse(x: int, y: int, size: int):
  t = turtle.Turtle()
  t.speed(0)
  t.penup()
  t.setx(x - size)
  t.sety(y)
  t.pendown()
  t.pensize(3)
  t.right(90)
  t.fillcolor('#FF69B4')
  t.begin_fill()
  t.circle(size, 180)
  t.left(90)
  t.forward(2 * size)
  t.end_fill()
  t.hideturtle()

def draw_face(eye_color, nose_size, mouse_size):
  s = turtle.Screen()
  draw_eye(110, 50, eye_color)
  draw_eye(-110, 50, eye_color)
  draw_nose(0, 20, nose_size)
  draw_mouse(0, -140, mouse_size)
  s.exitonclick()

draw_face('gray', 20, 80)
draw_face('red', 15, 70)

