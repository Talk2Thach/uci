#!/usr/bin/env python3

# Edward Xia - 73387315

import datetime
import yahoo_finance
import indicators, strategies

class StockAnalytics:

    Strategies = {
        "D": "Directional",
        "S": "Simple moving average"
    }

    def __init__(self: object):
        """Init the class"""
        self.symbol = input("Please input a stock symbol: ").strip().upper()
        self.start_date = self._get_date("Please input the start date (YYYY-MM-DD): ")
        self.end_date = self._get_date("Please input the end date (YYYY-MM-DD): ")
        self.data = yahoo_finance.parse(yahoo_finance.request(self.symbol, self.start_date, self.end_date))
        if self.data == []:
            print("No data available for selected time period.")
            raise Exception

    def analyze(self: object):
        """Start an analyze"""
        format_str = "{:<10}  {:<10}  {:<10}  {:<10}"
        strategy = self._get_strategy()
        interval = self._get_interval()
        note = ""

        if strategy == "D":
            indicator_generator = indicators.Directional(interval)
            signal_generator = strategies.Directional(interval)
            buy_threshold = None
            sell_threshold = None
            while buy_threshold == None or buy_threshold > interval or buy_threshold <= 0:
                buy_threshold = self._get_threshold("Please input the buy threshold: ")
            while sell_threshold == None or sell_threshold >= buy_threshold:
                sell_threshold = self._get_threshold("Please input the sell threshold: ")
            signal_generator.set_threshold(buy_threshold, sell_threshold)
            note = ", buy above +{:d}, sell below {:d}".format(buy_threshold, sell_threshold)
        else:
            indicator_generator = indicators.SimpleMovingAverage(interval)
            signal_generator = strategies.SimpleMovingAverage(interval)

        self.indicators = indicator_generator.execute(self.data)
        self.signals = signal_generator.execute(self.data, self.indicators)
        print()
        print("SYMBOL: {:s}".format(self.symbol))
        print("STRATEGY: {:s} ({:d}-day){:s}".format(self.Strategies[strategy], interval, note))
        print(format_str.format("DATE", "CLOSE", "INDICATOR", "SIGNAL"))
        for i in range(len(self.data)):
            print(format_str.format(self.data[i]["Date"], self.data[i]["Close"], self.indicators[i], self.signals[i]))

    def _get_threshold(self: object, message: str) -> int:
        """Let user input the threshold"""
        valid = False
        while not valid:
            try:
                threshold = int(input(message))
                valid = True
            except:
                pass
        return threshold

    def _get_strategy(self: object) -> str:
        """Let user pick the strategy to use"""
        print("Available strategies:")
        for i in self.Strategies:
            print("{:s}: {:s}".format(i, self.Strategies[i]))
        valid = False
        while not valid:
            strategy = input("Please choose the strategy you want to use (D/S): ").strip().upper()
            if strategy in ["D", "S"]:
                valid = True
        return strategy

    def _get_interval(self: object) -> int:
        """Let user input the interval to analyze"""
        valid = False
        while not valid:
            try:
                interval = int(input("Please input the time interval(days) you want to analyze: "))
                if interval <= 1:
                    raise Exception
                valid = True
            except:
                pass
        return interval

    def _get_date(self: object, message: str) -> datetime.date:
        """Let user input a date"""
        valid = False
        while not valid:
            try:
                date_str = input(message).strip()
                date_list = date_str.split("-")
                if len(date_list) != 3:
                    raise Exception
                date = datetime.date(int(date_list[0]), int(date_list[1]), int(date_list[2]))
                valid = True
            except:
                print("\nSorry, invalid date.")
        return date

def _get_continue() -> str:
    """Ask user if want to do another analysis"""
    _continue = ""
    while _continue not in ["yes", "no", "y", "n"]:
        _continue = input("Do you want to do another analysis (y/n)? ").strip().lower()
    return _continue == "yes" or _continue == "y"

def interface():
    """main function"""
    try:
        _continue = True
        while _continue:
            StockAnalytics().analyze()
            print()
            _continue = _get_continue()
    except Exception:
        if _get_continue():
            interface()


if __name__ == '__main__':
    interface()
