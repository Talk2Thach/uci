# Sheng Xia 73387315 and Victor Zhang 46812269. ICS 31 Lab sec 11. Lab asst 6
# Some part is written by Justin Lee 57005395 in Lab 5

__author__ = 'dgk'

# RESTAURANT COLLECTION PROGRAM
# ICS 31, UCI, David G. Kay, Fall 2012

# Implement Restaurant as a namedtuple, collection as a list

##### MAIN PROGRAM (CONTROLLER)

def restaurants():  # nothing -> interaction
    """ Main program
    """
    print("Welcome to the restaurants program!")
    our_rests = Collection_new()
    our_rests = handle_commands(our_rests)
    print("\nThank you.  Good-bye.")

MENU = """
Restaurant Collection Program --- Choose one
 n:  Add a new restaurant to the collection
 r:  Remove a restaurant from the collection
 e:  Empty the collection list
 c:  Change the retaurants' prices in the collection to user-input percentage
 s:  Search the collection for selected restaurants
 sc: Search the collection for restaurants with specific cuisine
 sd: Search the collection for restaurants with specific dish
 p:  Print all the restaurants
 q:  Quit
"""

def handle_commands(C: list) -> list:
    """ Display menu, accept and process commands.
    """
    while True:
        response = input(MENU)
        if response=="q":
            return C
        elif response=='n':
            r = Restaurant_get_info()
            C = Collection_add(C, r)
        elif response== 'e':
            C = []
        elif response == 'c':
            n = float(input("Enter a percentage change number without %: "))
            C = Collection_change_price(C,n)
        elif response=='r':
            n = input("Please enter the name of the restaurant to remove:  ")
            C = Collection_remove_by_name(C, n)
        elif response=='p':
            print(Collection_str(C))
        elif response=='s':
            n = input("Please enter the name of the restaurant to search for:  ")
            for r in Collection_search_by_name(C, n):
                print(Restaurant_str(r))
        elif response == 'sc':
            n = input("Please enter the name of the cuisine:  ")
            for r in C:
                if n == r.cuisine:
                    print(r.name + ':\n    ' + Restaurant_avg_str(r) + "\n")
        elif response == 'sd':
            n = input("Please enter the name of the dish:  ")
            for r in Collection_search_by_dish(C, n):
                print(Restaurant_str(r))
        else:
            invalid_command(response)

def invalid_command(response):  # string -> interaction
    """ Print message for invalid menu command.
    """
    print("Sorry; '" + response + "' isn't a valid command.  Please try again.")



from collections import namedtuple
##### Dish
Dish = namedtuple('Dish', 'name price calories')

def Dish_str(dish: Dish) -> str:
    '''Return a human readable string for dish'''
    return dish.name + " ($" + str(dish.price) + "): " + str(dish.calories) + " cal"

def Dish_get_info() -> Dish:
    """ Prompt user for fields of Dish; create and return.
    """
    return Dish(
        input("Please enter the dish's name:  "),
        float(input("Please enter the price:  ")),
        int(input("Please enter the calories:  ")))

def Dish_change_price(dish: Dish, percentage_change: float)->Dish:
    '''Returns the new dish with changed price by percentage'''
    return dish._replace(price=dish.price * (1 + percentage_change / 100))

##### Menu
def Menu_enter(menu: list) -> list:
    while True:
        if input("Do you want to add a new dish(enter yes if you want)? ")=="yes":
            menu.append(Dish_get_info())
        else:
            return menu

def Menu_change_price(menu: list, percentage_change: float)-> list:
    '''Returns the new menu with changed prices by calling Dish_change_price function'''
    for i in range(len(menu)):
        menu[i] = Dish_change_price(menu[i], percentage_change)
    return menu

def Menu_display(dish_list: list) -> str:
    '''Return a long human readable string for dish list
    '''
    result = ''
    for i in dish_list:
        result = result + Dish_str(i) + '\n'
    return result

##### Restaurant
Restaurant = namedtuple('Restaurant', 'name cuisine phone menu')
# Constructor:   r1 = Restaurant('Taillevent', 'French', '01-11-22-33-44', 'Escargots', 23.50)

def Restaurant_avg_price(self: Restaurant) -> float:
    '''Return the average price of dishes in a restaurant'''
    summ = 0
    for i in self.menu:
        summ += i.price
    return summ/len(self.menu)

def Restaurant_avg_calories(self: Restaurant) -> float:
    '''Return the average calories of dishes in a restaurant'''
    summ = 0
    for i in self.menu:
        summ += i.calories
    return summ/len(self.menu)

def Restaurant_avg_str(self: Restaurant) -> str:
    '''Return a string that represent the average price and average calories.'''
    return "Average price:  ${:.2f}.  Average calories:  {:.1f}".format(Restaurant_avg_price(self), Restaurant_avg_calories(self))

def Restaurant_has_a_dish(r: Restaurant, name: str) -> bool:
    '''Return True if the Restaurant has a dish match the name, otherwise return False'''
    for i in r.menu:
        if name.lower().replace(" ","") in i.name.lower().replace(" ",""):
            return True
    return False

def Restaurant_str(self: Restaurant) -> str:
    return (
        "Name:     " + self.name + "\n" +
        "Cuisine:  " + self.cuisine + "\n" +
        "Phone:    " + self.phone + "\n" +
        "Menu:\n" + Menu_display(self.menu) + "\n" +
        Restaurant_avg_str(self))

def Restaurant_get_info() -> Restaurant:
    """ Prompt user for fields of Restaurant; create and return.
    """
    return Restaurant(
        input("Please enter the restaurant's name:  "),
        input("Please enter the kind of food served:  "),
        input("Please enter the phone number:  "),
        Menu_enter([]))

def Restaurant_change_price(restaurant: Restaurant, percentage_change: float)->Restaurant:
    '''Returns a new restaurant with changed menu by calling the Menu_change_price function'''
    return restaurant._replace(menu=Menu_change_price(restaurant.menu, percentage_change))

#### COLLECTION
# A collection is a list of restaurants

def Collection_change_price(C: list, new_price:float)->list:
    '''Return the new collection of restaurants after the original one's prices has been '''
    for i in range(len(C)):
        C[i] = Restaurant_change_price(C[i],new_price)
    return C

def Collection_new() -> list:
    ''' Return a new, empty collection
    '''
    return [ ]

def Collection_str(C: list) -> str:
    ''' Return a string representing the collection
    '''
    s = ""
    for r in C:
        s = s + Restaurant_str(r)
    return s

def Collection_search_by_name(C: list, name: str) -> list:
    """ Return list of Restaurants in input list whose name matches input string.
    """
    result = [ ]
    for r in C:
        if r.name == name:
            result.append(r)
    return result
    # alternative (using a list comprehension):
    # return [r for r in C if r.name == name]

def Collection_search_by_dish(C: list, name: str) -> list:
    '''Return a list of restaurants which has at least a dish that match the name
    '''
    result = [ ]
    for r in C:
        if Restaurant_has_a_dish(r, name):
            result.append(r)
    return result

def Collection_add(C: list, R: Restaurant) -> list:
    """ Return list of Restaurants with input Restaurant added at end.
    """
    C.append(R)
    return C

def Collection_remove_by_name(C: list, name: str) -> list:
    """ Given name, remove all Restaurants with that name from collection.
    """
    result = [ ]
    for r in C:
        if r.name != name:
            result.append(r)
    return result
    #    Alternative:
    #    return [r for r in self.rests if r.name != name]

restaurants()
