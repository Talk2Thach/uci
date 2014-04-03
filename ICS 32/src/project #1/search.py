#/usr/bin/env python3

# Edward Xia - 73387315
# Chloe Chen - 11715667

import os, shutil

def recursive_search(directory=".", options={}):
    """Search file recursively and return a list of pathes"""
    results = []
    try:
        for path in os.listdir(directory):
            absolute_path = os.path.abspath(os.path.join(directory, path))
            if os.path.isfile(absolute_path):
                if ("match" in options and path == options["match"]) or \
                   ("endswith" in options and path.endswith(options["endswith"])) or \
                   ("size" in options and os.path.getsize(absolute_path) >= options["size"]):
                    results.append(absolute_path)
            elif os.path.isdir(absolute_path):
                results.extend(recursive_search(absolute_path, options))
    except:
        pass
    return results

def _get_directory() -> str:
    """Let user input directory"""
    try:
        directory = input("Please input the directory that you want to search: ").strip()
        os.listdir(directory)
    except:
        print("Directory does not exists or not readable by current user.")
        directory = _get_directory()
    return directory

def _get_search_options() -> { str: 'str or float' }:
    """Let user input search options"""
    method = _get_search_method()
    if method in ["match", "endswith"]:
        option = input("Please input a keyword: ")
    elif method in ["size"]:
        option = _get_search_size()
    return { method: option }

def _get_search_size() -> float:
    """Let user input size"""
    valid = False
    while not valid:
        try:
            size = float(input("Please input a size (in byte): "))
            valid = True
        except:
            print("Sorry, invaild size.")
    return size

def _get_search_method() -> str:
    """Let user input search method"""
    print("Methods to search:")
    print("   match:     match all the filenames exactly with a keyword.")
    print("   endswith:  match all the filenames end with a keyword.")
    print("   size:      match all the file equal to or larger than a size.")
    method = input("Please input your prefered way to search: ").strip().lower()
    while method not in ["match", "endswith", "size"]:
        print("\nSorry, invaild searching method.\n")
        method = _get_search_method()
    return method

def _get_task() -> str:
    """Let user input the task to perform"""
    print("Task to perform:")
    print("   path:       print pathes of files.")
    print("   firstline:  print first line of each file.")
    print("   duplicate:  duplicate files to make copys.")
    print("   touch:      touch the timestamp of files.")
    task = input("Please input your the task you want to perform: ").strip().lower()
    while task not in ["path", "firstline", "duplicate", "touch"]:
        print("\nSorry, invaild task to perform.\n")
        task = input("Please input your the task you want to perform: ").strip().lower()
    return task

def print_first_line(filename: str):
    """Return the first line of a file"""
    try:
        f = open(filename, "r")
        line = f.readline()
        print(line)
    except:
        pass
    f.close()

def duplicate_file(filename: str):
    """Duplicate a file"""
    try:
        shutil.copy(filename, filename + ".dup")
    except:
        pass

def touch_file(filename: str):
    """Update the timestamp for a file"""
    try:
        os.utime(filename, None)
    except:
        pass

def interface():
    """Main Interface"""
    directory = _get_directory()
    options = _get_search_options()
    for i in recursive_search(directory, options):
        print()
        print("File founded: {}".format(i))
        task = _get_task()
        if task == "path":
            print(i)
        elif task == "firstline":
            print_first_line(i)
        elif task == "duplicate":
            duplicate_file(i)
        elif task == "touch":
            touch_file(i)

if __name__ == '__main__':
    interface()
