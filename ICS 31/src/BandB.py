AVAILABLE_BEDROOMS = []
RESERVATIONS = []
LAST_COMFORMATION_NUMBER = 0

from collections import namedtuple
from datetime import datetime

Reservation = namedtuple('Reservation', 'id room_number arrival_date departure_date guest_name')

# s.1
def Bedrooms_add(room_number: int):
    if room_number in AVAILABLE_BEDROOMS:
        print("Sorry, can't add room {:d} again; it's already on the list.".format(room_number))
    else:
        AVAILABLE_BEDROOMS.append(room_number)

def Bedrooms_list():
    print("Number of bedrooms in service: ", len(AVAILABLE_BEDROOMS))
    print("------------------------------------")
    for i in sorted(AVAILABLE_BEDROOMS): # s.6
        print(i)

# s.2
def Bedrooms_delete(room_number: int):
    if not room_number in AVAILABLE_BEDROOMS:
        print("Sorry, can't delete room {:d}; it is not in service now".format(room_number))
    else:
        AVAILABLE_BEDROOMS.remove(room_number)
        delete_list = []
        for i in RESERVATIONS:
            if i.room_number == room_number:
                print("Deleting room {:d} forces cancellation of this reservation:".format(room_number))
                print("    {:s} arriving {:10s} and departing {:10s} (Conf. #{:d})".format(i.guest_name, date_str(i.arrival_date), date_str(i.departure_date), i.id))
                delete_list.append(i)
        for i in delete_list:
            RESERVATIONS.remove(i)

# s.3
def date_str(date: datetime) -> str:
    return "{:2d}/{:2d}/{:4}".format(date.month, date.day, date.year)

def datestr_to_datetime(d: str) -> datetime:
    d_list = d.split('/')
    return datetime(int(d_list[2]), int(d_list[0]), int(d_list[1]))

def Reservation_is_possible(i, arrival_date: datetime, departure_date: datetime) -> bool:
    return not Reservation_is_impossible(i, arrival_date, departure_date)

def Reservation_is_impossible(i, arrival_date: datetime, departure_date: datetime) -> bool:
    return ((i.arrival_date < arrival_date and i.departure_date >= arrival_date) or (i.departure_date >= departure_date and i.arrival_date < departure_date))

def Reservations_add(reservation_str: str):
    global LAST_COMFORMATION_NUMBER
    parameters= reservation_str.split()
    room_number = int(parameters[0])
    arrival_date = datestr_to_datetime(parameters[1])
    departure_date = datestr_to_datetime(parameters[2])
    name = ' '.join(parameters[3:])

    if not room_number in AVAILABLE_BEDROOMS:
        print("Sorry; can't reserve room {:d}; room not in service".format(room_number))
        return
    elif arrival_date > departure_date:
        print("Sorry, can't reserve room {:d} ({:10s} to {:10s});".format(room_number, date_str(arrival_date), date_str(departure_date)))
        print("    can't leave before you arrive.")
        return
    elif arrival_date == departure_date:
        print("Sorry, can't reserve room {:d} ({:10s} to {:10s});".format(room_number, date_str(arrival_date), date_str(departure_date)))
        print("    can't arrive and leave on the same day.")
        return
    else:
        for i in RESERVATIONS:
            if i.room_number == room_number and Reservation_is_impossible(i, arrival_date, departure_date):
                print("Sorry, can't reserve room {:d} ({:10s} to {:10s});".format(room_number, date_str(arrival_date), date_str(departure_date)))
                print("   it's already booked (Conf. #{:d})".format(i.id))
                return
        LAST_COMFORMATION_NUMBER += 1
        r = Reservation(LAST_COMFORMATION_NUMBER, room_number, arrival_date, departure_date, name)
        RESERVATIONS.append(r)
        print("Reserving room {:3d} for {:s} -- Confirmation #{:d}".format(r.room_number, r.guest_name, r.id))
        print("    (arriving {:10s}, departing {:10s})".format(date_str(r.arrival_date), date_str(r.departure_date)))

def Reservations_delete(id: int):
    for i in RESERVATIONS:
        if i.id == id:
            RESERVATIONS.remove(i)
            return
    print("Sorry, can't cancel reservation; no confirmation number", id)

def Reservation_str(r: str) -> str:
    return "{:3d} {:3d} {:10s} {:10s} {:s}".format(r.id , r.room_number, date_str(r.arrival_date), date_str(r.departure_date), r.guest_name)

def Reservations_sort(r_list: [Reservation]) -> [Reservation]:
    return sorted(r_list, key=lambda r: r.arrival_date) # s.6

def Reservations_list():
    print('Number of reservations: ', len(RESERVATIONS))
    print('No. Rm. Arrive      Depart     Guest')
    print('------------------------------------------------')
    for i in Reservations_sort(RESERVATIONS):
        print(Reservation_str(i))

def Reservations_list_by_bedroom(number: int):
    result=[]
    for i in RESERVATIONS:
        if number == i.room_number:
            result.append(i)
    print("Reservations for room {:d}:".format(number))
    for i in Reservations_sort(result):
        print("   {:10s} to {:10s}:  room {:d}".format(date_str(i.arrival_date), date_str(i.departure_date), i.room_number))

def Reservations_list_by_guest(name:str):
    result=[]
    for i in RESERVATIONS:
        if name == i.guest_name:
            result.append(i)
    print("Reservations for {:s}:".format(name))
    for i in Reservations_sort(result):
        print("   {:10s} to {:10s}:  {:s}".format(date_str(i.arrival_date), date_str(i.departure_date), i.guest_name))

def Reservations_list_by_arrival(date: str):
    a_datetime = datestr_to_datetime(date)
    print("Guests arriving on {:s}:".format(date))
    for i in RESERVATIONS:
        if a_datetime == i.arrival_date:
            print("  {:s} (room {:d})".format(i.guest_name, i.room_number))

def Reservations_list_by_departure(date: str):
    d_datetime = datestr_to_datetime(date)
    print("Guests departing on {:s}:".format(date))
    for i in RESERVATIONS:
        if d_datetime == i.departure_date:
            print("  {:s} (room {:d})".format(i.guest_name, i.room_number))

def Bedrooms_list_by_available_between(parameter: str):
    date_list = parameter.split()
    arrival_date = datestr_to_datetime(date_list[0])
    departure_date = datestr_to_datetime(date_list[1])
    print("Bedrooms free between {:10s} to {:10s}:".format(date_str(arrival_date), date_str(departure_date)))
    for i in AVAILABLE_BEDROOMS:
        available = True
        for j in RESERVATIONS:
            if i == j.room_number and (Reservation_is_impossible(j, arrival_date, departure_date) and j.departure_date != departure_date):
                available = False
        if available:
            print("   {:d}".format(i))

def Bedrooms_list_by_unavailable_between(parameter: str):
    date_list = parameter.split()
    arrival_date = datestr_to_datetime(date_list[0])
    departure_date = datestr_to_datetime(date_list[1])
    print("Bedrooms occupied between {:10s} to {:10s}:".format(date_str(arrival_date), date_str(departure_date)))
    for i in AVAILABLE_BEDROOMS:
        unavailable = False
        for j in RESERVATIONS:
            if i == j.room_number and (Reservation_is_impossible(j, arrival_date, departure_date) and j.departure_date != departure_date):
                unavailable = True
        if unavailable:
            print("   {:d}".format(i))

f = open(input("Please input a file:"), "r")
for line in f:
    line = line.lstrip()
    command = line[0:2].upper()
    parameter = line[2:].strip()
    if command == "AB":
        Bedrooms_add(int(parameter))
    elif command == "BL":
        Bedrooms_list()
    elif command == "PL":
        print(parameter)
    elif command == "**":
        "Do nothing"
    elif command == "BD":
        Bedrooms_delete(int(parameter))
    elif command == "NR":
        Reservations_add(parameter)
    elif command == "RL":
        Reservations_list()
    elif command == "RD":
        Reservations_delete(int(parameter))
    elif command == "RB":
        Reservations_list_by_bedroom(int(parameter))
    elif command == "RC":
        Reservations_list_by_guest(parameter)
    elif command == "LA":
        Reservations_list_by_arrival(parameter)
    elif command == "LD":
        Reservations_list_by_departure(parameter)
    elif command == "LF":
        Bedrooms_list_by_available_between(parameter)
    elif command == "LO":
        Bedrooms_list_by_unavailable_between(parameter)
f.close()
f = open(input("Please input a output file name: "), "w")
for i in AVAILABLE_BEDROOMS:
    f.write("AB {:d}\n".format(i))
for i in RESERVATIONS:
    f.write("NR {:3d} {:10s} {:10s} {:s}\n".format(i.room_number, date_str(i.arrival_date), date_str(i.departure_date), i.guest_name))
f.close()

# s.6
"""
Out program can take same input and give same output as the assignment webpage shown from stage 1 to 5 except we sorted the bedroom number and reservations as described in stage 6.
"""
# Example input file
"""
** This is a sample command file for the Anteater BandB, Stage V
** First, add some bedrooms:
AB 501
AB 502
AB 503
AB 504
** Now make some reservations
NR 503 12/10/2012 12/15/2012 I. Joliet
nr 502  1/10/2013  1/15/2013 I. Joliet
nr 502 12/10/2012 12/14/2012 K. Leavenworth
nr 502 12/10/2013 12/14/2013 K. Leavenworth
nr 504  2/15/2013 12/14/2013 C. S. Quentin
RL
** List reservations for a bedroom
RB 502
** List reservations for two guests
RC K. Leavenworth
RC C. S. Quentin
** List everyone arriving December 10, 2012
LA 12/10/2012
** List everyone (i.e. nobody) arriving December 9
LA 12/9/2012
** List everyone departing December 14, 2013
LD 12/14/2013
** List the free rooms when the hotel is empty
LF 12/20/2012 12/25/2012
** List the free rooms when some are reserved
LF 12/12/2012 12/20/2012
** List the free rooms on a single date
** (Remember that a room isn't occupied on the night of a departure)
LF 12/14/2012 12/14/2012
** List occupied rooms on various dates
LO 12/14/2012 12/14/2012
LO 12/12/2012 12/20/2012
LO 12/20/2012 12/25/2012
PL Thank you for abusing the Anteater BandB Reservation System!
** That's the end of the sample data for Stage V.
"""
# Example Output(print)
"""
** This is a sample command file for the Anteater BandB, Stage V
** First, add some bedrooms:
AB 501
AB 502
AB 503
AB 504
** Now make some reservations
NR 503 12/10/2012 12/15/2012 I. Joliet
nr 502  1/10/2013  1/15/2013 I. Joliet
nr 502 12/10/2012 12/14/2012 K. Leavenworth
nr 502 12/10/2013 12/14/2013 K. Leavenworth
nr 504  2/15/2013 12/14/2013 C. S. Quentin
RL
** List reservations for a bedroom
RB 502
** List reservations for two guests
RC K. Leavenworth
RC C. S. Quentin
** List everyone arriving December 10, 2012
LA 12/10/2012
** List everyone (i.e. nobody) arriving December 9
LA 12/9/2012
** List everyone departing December 14, 2013
LD 12/14/2013
** List the free rooms when the hotel is empty
LF 12/20/2012 12/25/2012
** List the free rooms when some are reserved
LF 12/12/2012 12/20/2012
** List the free rooms on a single date
** (Remember that a room isn't occupied on the night of a departure)
LF 12/14/2012 12/14/2012
** List occupied rooms on various dates
LO 12/14/2012 12/14/2012
LO 12/12/2012 12/20/2012
LO 12/20/2012 12/25/2012
PL Thank you for abusing the Anteater BandB Reservation System!
** That's the end of the sample data for Stage V.
"""
# Example Output(end-of-day file)
"""
AB 501
AB 502
AB 503
AB 504
NR 503 12/10/2012 12/15/2012 I. Joliet
NR 502  1/10/2013  1/15/2013 I. Joliet
NR 502 12/10/2012 12/14/2012 K. Leavenworth
NR 502 12/10/2013 12/14/2013 K. Leavenworth
NR 504  2/15/2013 12/14/2013 C. S. Quentin
"""

# s.6 optional
"""
To have consistency in conformation number, we can have a new command called RR (restore reservation), which also take a conformation number as argument
"""
