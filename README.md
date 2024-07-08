# Touch Pen implementation using light sensing
Resistance of photresistors varies with amount of light (of a particular frequency) falling on it. This property is exploited to implement a basic touch pen for MAX7219 LED screen.

## Circuit

1. A resistor of 1000 ohms and the photoresistor is connected in series other terminals of the 1k resistor connected to 5V and that of photo resistor to ground. Analog input is taken from joint of these two and fed into analog pin of Arduino.
2. MAX7219 is connected as standard.

## Comments
This basic implementation can be improved by optimising the algorithm and calibrating threshold values for different lightning conditions.