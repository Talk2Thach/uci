#!/usr/bin/env python3

# Edward Xia - 73387315

import indicators

class Directional:
    def __init__(self: object, interval: int):
        """Init the class"""
        self.interval = interval
        self.BUY = 2
        self.SELL = 0

    def set_threshold(self: object, buy: int, sell: int):
        """Set the buy and sell threshold"""
        self.BUY = buy
        self.SELL = sell

    def execute(self: object, data: [], data_indicators=None) -> []:
        """Generate the analysis data"""
        if data_indicators == None:
            data_indicators = indicators.Directional().execute(data)

        signals = []
        nonempty_signal = ""
        for i in range(len(data_indicators)):
            if i == 0:
                signals.append("")
            else:
                if int(data_indicators[i]) > self.BUY and nonempty_signal != "BUY":
                    signals.append("BUY")
                    nonempty_signal = "BUY"
                elif int(data_indicators[i]) < self.SELL and nonempty_signal != "SELL":
                    signals.append("SELL")
                    nonempty_signal = "SELL"
                else:
                    signals.append("")
        return signals

class SimpleMovingAverage:
    def __init__(self: object , interval: int):
        """Init the class"""
        self.interval = interval

    def execute(self: object, data: [], data_indicators=None) -> []:
        """Generate the analysis data"""
        if data_indicators == None:
            data_indicators = indicators.SimpleMovingAverage().execute(data)

        signals = []
        for i in range(len(data)):
            if i < self.interval:
                signals.append("")
            else:
                if float(data_indicators[i]) > float(data[i]["Close"]) and \
                   float(data_indicators[i - 1]) < float(data[i - 1]["Close"]):
                    signals.append("SELL")
                elif float(data_indicators[i]) < float(data[i]["Close"]) and \
                     float(data_indicators[i - 1]) > float(data[i - 1]["Close"]):
                    signals.append("BUY")
                else:
                    signals.append("")
        return signals
