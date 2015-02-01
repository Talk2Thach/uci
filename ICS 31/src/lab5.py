# Justin Lee 57005395 and Sheng Xia 73387315. ICS 31 Lab sec 11. Lab asst 5

#Part C
print('\n\n---------Part C---------\n\n')

from collections import namedtuple
Dish = namedtuple('Dish', 'name price calories')

#c.1
d1 = Dish('Burger',4.0,354)
d2 = Dish('Peking Duck',20, 2000)
d3 = Dish('Peking Duck',50, 2000)
print()

#c.2
def Dish_str(dish: Dish) -> str:
    '''Return a human readable string for dish'''
    return dish.name + " ($" + str(dish.price) + "): " + str(dish.calories) + " cal"

#c.3
def Dish_same(x: Dish,y: Dish)->bool:
    '''Return true if name and calories counts are equal
    '''
    return (x.name == y.name and x.calories == y.calories)

assert Dish_same(d1,d1) == True
assert Dish_same(d1,d2) == False
assert Dish_same(d2,d3) == True

#c.4
def Dish_change_price(dish: Dish, percentage_change: float) -> Dish:
    '''Input a dish and a percentage,
    then return a dish with price increase by that percentage.
    '''
    return dish._replace(price = dish.price * (1 + percentage_change / 100))

#c.5
def Dish_is_cheap(dish: Dish, price: float) -> bool:
    '''Return True if dish is cheaper than given price,
    otherwise return False.
    '''
    return dish.price < price

#c.6
DL = [Dish('Burger',4.0,354),
      Dish('Peking Duck',20, 2000),
      Dish('Peking Duck',50, 2000),
      Dish('Edward', 100, 5000),
      Dish('Justin', 100, 4000)]

DL2 = [Dish('French Fries',2.0, 500),
      Dish('Crispy Chicken',10, 500),
      Dish('Spicy Chicken',10, 600),
      Dish('Beef', 15, 100)]

DL3 = []
DL3.extend(DL + DL2)

def Dishlist_display(dish_list: list) -> str:
    '''Return a long human readable string for dish list
    '''
    result = ''
    for i in dish_list:
        result = result + Dish_str(i) + '\n'
    return result

assert(Dishlist_display(DL3)) == '''Burger ($4.0): 354 cal
Peking Duck ($20): 2000 cal
Peking Duck ($50): 2000 cal
Edward ($100): 5000 cal
Justin ($100): 4000 cal
French Fries ($2.0): 500 cal
Crispy Chicken ($10): 500 cal
Spicy Chicken ($10): 600 cal
Beef ($15): 100 cal
'''
print(Dishlist_display(DL3))

#c.7
def Dishlist_all_cheap(dish_list: list, price: float) -> bool:
    '''Return True if every dish in the list is cheaper than the price,
    otherwise return False.
    '''
    for i in dish_list:
        if not Dish_is_cheap(i, price):
            return False
    return True

assert(Dishlist_all_cheap(DL3, 30)==False)
assert(Dishlist_all_cheap(DL3, 150)==True)


#c.8
def Dishlist_change_price(dish_list: list, percentage_change: float) -> list:
    '''Return a new list of dishes with price changed by percentage'''
    result = []
    for i in dish_list:
        result.append(Dish_change_price(i, percentage_change))
    return result

#c.9
def Dishlist_prices(dish_list: list) -> list:
    '''Return a list containing the price of each dishes in the source list.
    '''
    result = []
    for i in dish_list:
        result.append(i.price)
    return result

#c.10
def Dishlist_average(dish_list: list) -> float:
    '''Return the average price of a list of dishes.
    '''
    price_list = Dishlist_prices(dish_list)
    return sum(price_list) / len(price_list)

assert Dishlist_average(DL3) == 34.55555555555556

#c.11
def Dishlist_keep_cheap(dish_list: list, price: float) -> list:
    '''Return a new list containing the dishes are cheaper the given price.
    '''
    result = []
    for i in dish_list:
        if Dish_is_cheap(i, price):
            result.append(i)
    return result

#c.12
DL4 = [Dish("1", 2, 3),
Dish("2", 4, 6),
Dish("3", 6, 9),
Dish("4", 8, 12),
Dish("5", 10, 15),
Dish("6", 12, 18),
Dish("7", 14, 21),
Dish("8", 16, 24),
Dish("9", 18, 27),
Dish("10", 20, 30),
Dish("11", 22, 33),
Dish("12", 24, 36),
Dish("13", 26, 39),
Dish("14", 28, 42),
Dish("15", 30, 45),
Dish("16", 32, 48),
Dish("17", 34, 51),
Dish("18", 36, 54),
Dish("19", 38, 57),
Dish("20", 40, 60),
Dish("21", 42, 63),
Dish("22", 44, 66),
Dish("23", 46, 69),
Dish("24", 48, 72),
Dish("25", 50, 75)]

def before_and_after():
    '''Print the original list,
    Ask user to input the percentage of price change
    Print the changed list'''
    global DL4
    percentage_change = float(input("Input the percentage of change(without %): "))
    print(Dishlist_display(DL4))
    DL4 = Dishlist_change_price(DL4, percentage_change)
    print('-------- Price Updated -------')
    print(Dishlist_display(DL4))

before_and_after()


#Part E
print('\n\n---------Part E---------\n\n')


Restaurant = namedtuple('Restaurant', 'name cuisine phone menu')
r1 = Restaurant('Thai Dishes', 'Thai', '334-4433', [Dish('Mee Krob', 12.50, 500),
                                                    Dish('Larb Gai', 11.00, 450)])
r2 = Restaurant('Taillevent', 'French', '01-44-95-15-01',
                                [Dish('Homard Bleu', 45.00, 750),
                                 Dish('Tournedos Rossini', 65.00, 950),
                                 Dish("Selle d'Agneau", 60.00, 850)])

#e.1
r3 = Restaurant('Pascal', 'French', '940-752-0107', [Dish('Escargots', 12.95, 250),
                                                     Dish('Poached Salmon', 18.50, 550),
                                                     Dish('Rack of Lamb', 24.00, 850)])

#e.2
def Restaurant_first_dish_name(restaurant: Restaurant) -> str:
    '''Return the name of first dish of a restaurant.'''
    return restaurant.menu[0].name

#e.3
def Restaurant_is_cheap(restaurant: Restaurant, price: float)->bool:
    '''Function that returns true if stated price is more than or equal to average price in restaurant
    '''
    result = 0
    for i in restaurant.menu:
        result += i.price
    return (result / len(restaurant)) <= price

#e.4
Restaurant_Collection = [r1,r2,r3]
Restaurant_Collection2 = [r1,r2,r3]

def Dish_raise_price(dish: Dish)->Dish:
    '''Returns the new dish with changed price'''
    return dish._replace(price=2.50)

def Menu_raise_price(menu: list)-> list:
    '''Returns the new menu with changed prices by calling Dish_raise_price function'''
    for i in range(len(menu)):
        menu[i] = Dish_raise_price(menu[i])
    return menu

def Restaurant_raise_price(restaurant: Restaurant)->Restaurant:
    '''Returns a new restaurant with changed menu by calling the Menu_raised_price function'''
    return restaurant._replace(menu=Menu_raise_price(restaurant.menu))

def Collection_raise_price(collection: list)-> list:
    '''Returns a new colelction with changed restaurants by calling the Restaurant_raise_price function'''
    for i in range(len(collection)):
        collection[i] = Restaurant_raise_price(collection[i])
    return collection

def Dish_change_price(dish: Dish, percentage_change: float)->Dish:
    '''Returns the new dish with changed price by percentage'''
    return dish._replace(price=dish.price * (1 + percentage_change / 100))

def Menu_change_price(menu: list, percentage_change: float)->list:
    '''Returns the new menu with changed prices by calling Dish_change_price function'''
    for i in range(len(menu)):
        menu[i] = Dish_change_price(menu[i], percentage_change)
    return menu

def Restaurant_change_price(restaurant: Restaurant, percentage_change: float)->Restaurant:
    '''Returns a new restaurant with changed menu by calling the Menu_change_price function'''
    return restaurant._replace(menu=Menu_change_price(restaurant.menu, percentage_change))

def Collection_change_price(collection: list, percentage_change: float)-> list:
    '''Returns a new colelction with changed restaurants by calling the Restaurant_change_price function'''
    for i in range(len(collection)):
        collection[i] = Restaurant_change_price(collection[i], percentage_change)
    return collection

#e.5
def Collection_select_cheap(collection: list, price: float) -> list:
    result = []
    for i in collection:
        if Restaurant_is_cheap(i):
            result.append(i)
    return result

# Part G
print('\n\n-------------- Part G --------------\n\n')

#Exercise 4.13
s = 'abcdefghijklmnopqrstuvwxyz'

print(s[1:2] == 'bc')
print(s[:13] == 'abcdefghijklmn')
print(s[14:] == 'opqrstuvwxyz')
print(s[1:-2] == 'bcdefghijklmnopqrstuvw')

#Exercise 4.14
log = '128.0.0.1 - - [12/Feb/2011:10:31:08 -0600] "GET /docs/test.txt HTTP/1.0"'
address = log[:14].split()[0]
assert address == '128.0.0.1'
date = log[15:41]
assert date == '12/Feb/2011:10:31:08 -0600'

#Exercise 4.19
first = 'Marlena'
last = 'Sigel'
middle = 'Mae'
print(last + ',', first, middle)
print(last + ',',  first, middle[0] + '.')
print(first, middle[0] + '.', last)
print((middle[0] + '. ')*2+ last)

#Exercise 4.23
def average():
    words = input("Enter a sentence: ").split()
    length = 0
    for i in words:
        length += len(i)
    return length/len(words)

#Part H
print('\n\n---------------- Part H ----------------\n\n')

Count = namedtuple('Count', 'letter number')
def letter_count(string: str, string_to_search: str) -> list:
    result = []
    for i in string_to_search:
        number = 0
        for j in string:
            if j in i:
                number += 1
        result.append(Count(i, number))
    return result

assert letter_count('The cabbage has baggage', 'abcd') == [Count(letter='a',number=5), Count(letter='b',number=3), Count(letter='c',number=1), Count(letter='d',number=0)]
