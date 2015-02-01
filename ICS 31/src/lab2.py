# Sheng Xia 73387315 and Zuozhi Wang 94292670.  ICS 31 Lab sec 11.  Lab Asst 2.

# c.1
hours = int(input('How many hours?'))
print('This many hours:', hours)
rate = int(input('How many dollars per hour?'))
print('This many dollars per hour:  $', rate, sep='')
print('Weekly salary:  $', hours * rate, sep='')

# c.2
name = input('Hello.  What is your name?  ')
print('Hello,', name)
print('It\'s nice to meet you.')
age = int(input('How old are you?  '))
print('Next year you will be', age + 1, 'years old.')
print('Good-bye!')

# d
KRONE_PER_EURO = 7.46
KRONE_PER_POUND = 8.81
KRONE_PER_DOLLAR = 5.50

print('Please provide this information:')
business_name = input('Business name:  ')
euros_amount = float(input('Number of euros:  '))
pounds_amount = float(input('Number of pounds:  '))
dollars_amount = float(input('Number of dollars:  '))
euros_in_krone = euros_amount * KRONE_PER_EURO
pounds_in_krone = pounds_amount * KRONE_PER_POUND
dollars_in_krone = dollars_amount * KRONE_PER_DOLLAR
total_in_krone = euros_in_krone + pounds_in_krone + dollars_in_krone

print('')
print('Copenhagen Chamber of Commerce')
print('Business name:  ', business_name)
print(euros_amount, 'euros is', euros_in_krone, 'krone')
print(pounds_amount, 'pounds is', pounds_in_krone, 'krone')
print(dollars_amount, 'dollars is', dollars_in_krone, 'krone')
print('')
print('Total krone:  ', total_in_krone)

# e
from collections import namedtuple
Book = namedtuple('Book', 'title author year price')
favorite = Book('Adventures of Sherlock Holmes',
                'Arthur Conan Doyle', 1892, 21.50)
another = Book('Memoirs of Sherlock Holmes',
               'Arthur Conan Doyle', 1894, 23.50)
still_another = Book('Return of Sherlock Holmes',
                     'Arthur Conan Doyle', 1905, 25.00)

# e.1
still_another.title
# e.2
another.price
# e.3
(favorite.price + another.price + still_another.price) / 3
# e.4
favorite.year < 1900
# e.5
still_another = still_another._replace(price = 26.00)
# e.6
still_another = still_another._replace(price = still_another.price * 1.20)

# f
Animal = namedtuple('Animal', 'name species age weight favorite_food')
an_animal = Animal('Jumbo', 'elephant', 50, 1000, 'peanuts')
another_animal = Animal('Perry', 'platypus', 7, 1.7, 'shrimp')
an_animal.weight < another_animal.weight

# g
booklist = [favorite, another, still_another]

# g.1
print(booklist[0].price < booklist[1].price)

# g.2
print(booklist[0].year > booklist[-1].year)

# h
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

# h.1
print(RC[2].name)

# h.2
print(RC[0].cuisine == RC[3].cuisine)

# h.3
print(RC[-1].price)

# h.4
RC.sort()
print(RC)

# h.5
print(RC[-1].dish)

# h.6
new_restaurant_list = RC[0:2]
new_restaurant_list.extend([RC[-2],RC[-1]])
print(new_restaurant_list)

# i & j
import turtle

# i 2.26
s = turtle.Screen()
t = turtle.Turtle()
for i in range(4):
  t.forward(100)
  t.left(90)
s.exitonclick()

# i 2.27
s = turtle.Screen()
t = turtle.Turtle()
t.left(60)
for i in range(2):
  t.left(60)
  t.forward(100)
  t.left(120)
  t.forward(100)
s.exitonclick()

# i 2.28
def draw_polygon_has_sides(n: int):
  s = turtle.Screen()
  t = turtle.Turtle()
  for i in range(n):
    t.forward(100)
    t.left(360 / n)
  s.exitonclick()

draw_polygon_has_sides(5)
draw_polygon_has_sides(6)
draw_polygon_has_sides(7)
draw_polygon_has_sides(8)

# i 2.29
s = turtle.Screen()
t = turtle.Turtle()
for i in range(3):
  t.circle(100)
  t.penup()
  t.left(60)
  t.forward(50)
  t.left(60)
  t.pendown()
s.exitonclick()

# i 2.32
s = turtle.Screen()
t = turtle.Turtle()
t.circle(109)
t.penup()
t.forward(120)
t.pendown()
t.circle(1)
s.exitonclick()

# j
import math
s = turtle.Screen()
t = turtle.Turtle()
t.pensize(3)
t.penup()
t.setx(50 * math.sqrt(3))
t.sety(50)
t.pendown()
t.left(120)
t.circle(100,120)
t.left(60)
t.circle(100,120)
t.penup()
t.left(300)
t.setx(0)
t.sety(0)
t.pendown()
t.pensize(2)
t.circle(50)
t.pensize(1)
t.penup()
t.left(90)
t.forward(50)
t.pencolor('gray')
for i in range(60):
  t.pendown()
  t.forward(50)
  t.penup()
  t.left(180)
  t.forward(50)
  t.left(186)
t.dot(31, 'black')
t.right(45)
t.forward(10)
t.dot(20, 'white')
t.penup()
t.forward(100)
s.exitonclick()
