#!/usr/bin/env python3

# Edward Xia - 73387315

import urllib.request, urllib.error
import datetime
import csv

def request(symbol: str, start=datetime.date.today(), end=datetime.date.today()) -> 'str or None':
    try:
        url = "http://ichart.yahoo.com/table.csv?s={:s}&a={:d}&b={:d}&c={:d}&d={:d}&e={:d}&f={:d}&g=d"
        return urllib.request.urlopen(url.format(symbol,
                                                 start.month - 1, start.day, start.year,
                                                 end.month   - 1, end.day  , end.year)).read().decode("utf-8")
    except urllib.error.HTTPError:
        print("\nHTTP Error: You may inputted wrong infomation.\n")
        return None
    except:
        print("\nConnection Error\n")
        return None

def parse(data: str) -> [{}]:
    if data == None:
        raise Exception
    else:
        csv_lines = data.split("\n")
        if csv_lines[-1] == "":
            csv_lines.pop()

        columns = csv_lines[0].split(",")
        reader = csv.reader(csv_lines[1:], delimiter=",")

        entries = []
        for row in reader:
            entry = {}
            for i in range(len(columns)):
                entry[columns[i]] = row[i]
            entries.append(entry)
        return sorted(entries, key=lambda e: e["Date"])

