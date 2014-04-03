#!/usr/bin/env python3

# Edward Xia - 73387315

class Directional:
    def __init__(self: object, interval: int):
        """Init the class"""
        self.interval = interval

    def execute(self: object, data: []) -> list:
        """Generate the analysis data"""
        indicators = []
        for i in range(len(data)):
            indicator = 0
            if i == 0:
                indicators.append(indicator)
            else:
                for j in range(self.interval):
                    if i - j - 1 >= 0:
                        if float(data[i - j]["Close"]) > float(data[i - j - 1]["Close"]):
                            indicator += 1
                        if float(data[i - j]["Close"]) < float(data[i - j - 1]["Close"]):
                            indicator -= 1
                    else:
                        break
                indicators.append(indicator)
        for i in range(len(indicators)):
            if indicators[i] > 0:
                indicators[i] = "+{:d}".format(indicators[i])
            else:
                indicators[i] = "{:d}".format(indicators[i])
        return indicators

class SimpleMovingAverage:
    def __init__(self: object, interval: int):
        """Init the class"""
        self.interval = interval

    def execute(self: object, data: []) -> list:
        """Generate the analysis data"""
        indicators = []
        for i in range(len(data)):
            if i + 1 < self.interval:
                indicators.append("")
            else:
                indicators.append("{:.2f}".format(sum(
                    list(map(lambda x: float(x["Close"]), (data[i - self.interval + 1:i + 1]) ))
                ) / self.interval))
        return indicators
