# EEE308-Project-mini-weather-station
Arduino Uno-Based Mini Weather Station with LCD Display and LED Alert
# Description
This file talks about the idea and the first steps in making a microcontroller-based mini weather station that works on the Arduino Uno. The equipment tracks temperature, humidity, and atmosphereric pressure in the environment. The recorded data is processed right away and shown on a 16x2 LCD panel, an Arduino Serial Monitor, and a Serial Plotter so you can see it in real time. Also, the three weather factors are put together into one equation to figure out how likely it is to rain, which is then shown on the LCD. A LED alert shows when the temperature above 20 degree.
# Objective
This project involves the design and implementation of a microcontroller based mini weather station using the Arduino Uno. This system measures ambient temperature and humidity using a DHT11 sensor. The microcontroller processes the received data and displays it on a 16x2 character LCD in real time. This system is not only storing data, but it also allows for simple temperature management. When the temperature exceeds(reaches) a specified threshold, LED lights up. The LED will remain ON. The main goal of this work is to show how to use basic concepts of embedded systems, such as connecting sensors, controlling digital input and output, and showing data in real time. In a wider perspective by taking all the scientific knowledge we learned during the theoretical sessions and applying it in a project to test our knowledge.
# Hardware Components
- Arduino Uno (Microcontroller Unit)
- DHT11 Temperature and Humidity Sensor
- BMP280 Atmospheric Pressure Sensor
- 16x2 LCD Display (I2C Backpack + Parallel Header Support)
- LED (Alert Indicator)
- 220Ω Resistor
- Breadboard
- 4 × 100nF Ceramic Capacitors
# Hardware Design Considerations
## Decoupling Capacitors
Three 100nF ceramic capacitors are connected between Vcc and GND of:
- DHT11 sensor (power stability)
- BMP280 sensor (noise suppression)
- LCD module (display stability)
These capacitors are used for decoupling and noise filtering. They stabilize the supply voltage via suppressing high frequency noise and transient fluctuations, ensuring reliable sensor readings and stable system operation.
## LCD Interface Flexibility
The LCD module supports both:
-I2C interface (via backpack)
-Parallel interface (via male header pins)
Using​‍​‌‍​‍‌​‍​‌‍​‍‌ the I2C interface as the default configuration helps minimize the number of pins used. But for enhancing the robustness of the system, the LCD can be also switched to the parallel mode operation, if the need arises. Such flexibility allows the system to continue working correctly even in the event of communication or hardware ​‍​‌‍​‍‌​‍​‌‍​‍‌problems.
## I2C​‍​‌‍​‍‌​‍​‌‍​‍‌ Address Conflict Consideration
Multiple I2C devices on the bus may cause problem of I2C address conflict if they are having the same default address. Both the BMP280 sensor and the LCD (with I2C backpack) in this project communicate with the microcontroller using I2C. Hence, we kept this point in mind while coming up with the design. The first solution that came to our mind was changing the LCD module to the one which has dual-interface capability(I2C and parallel), this way, if the problem arises, we can use an alternate way of connection. Actually, no address conflict happened eventually since each device had a different I2C address. So, the LCD was used in I2C mode successfully without a need for fallback to parallel communication. Such a contemplation has made the system design more robust and ​‍​‌‍​‍‌​‍​‌‍​‍‌versatile.
# System Architecture
## Microcontroller Unit
Arduino Uno acts as the main control unit that handling data acquisition, processing, and output control.
## Sensor Module
DHT11 for Temperature and humidity measurement
BMP280 for Atmospheric pressure measurement
## Display Module
A 16x2 LCD is used to display real time environmental data.
## Alert Module
An LED is used as a visual indicator when the temperature exceeds a predefined threshold.
## Serial Monitoring Module
Sensor data is transmitted to the Arduino Serial Monitor for real time numerical observation.
## Serial Plotter Module
Sensor data is visualized graphically using the Arduino Serial Plotter to analyze trends over time.
## Prediction Module
A simplified rule based model is used to estimate the probability of rainfall:

RainProb = 0.55RH + 0.30(1013 - P_atm) + 0.15(25 - T)

RH: Relative Humidity (%)
P_atm: Atmospheric Pressure (hPa)
T: Temperature (°C)
# Implementation
- DHT11 uses a single wire for communication.
- BMP280 uses I2C for communication.
- LCD operates in I2C mode (default) or 4-bit parallel mode (fallback).
- LED is connected to a digital output pin.
- Serial communication is configured for live monitoring.
### System Operation Flow
- Getting data from the sensors
- Processing the data
- Displaying data on LCD
- Sending data to Serial Monitor
- Sending formatted data to Serial Plotter
# Interpretation
A​‍​‌‍​‍‌​‍​‌‍​‍‌ very moist atmosphere greatly raises the chance of rain, on the other hand, light air pressure is a sign of unstable weather conditions. Besides, the cold will help the condensation process and indirectly will increase the chance of rain. The output is changed to percent (0% - 100%) and shown on both the LCD and Serial ​‍​‌‍​‍‌​‍​‌‍​‍‌Monitor.
# Design Update (Compared to Proposal)
The first project proposal included a dedicated Power Supply Module. The module was not required during the implementation because the Arduino powers the system directly. The design was better, though, because the Serial Monitor let you see numbers in real time and the Serial Plotter let you see graphs of the data. This change made the system easier to use and gave us a better idea of how it worked.
# Installation & Setup
1. Clone the repository:
https://github.com/aycaoztekin123-eng/mini-weather-station
2. Open in Arduino IDE
3. 3.Install required libraries:
4. DHT sensor library
5. Adafruit BMP280 library
6. Upload code to Arduino Uno
7. Open Serial Monitor and Serial Plotter
# Usage
- System starts when powered
- LCD displays real-time data
- Serial Monitor shows sensor values
- Serial Plotter shows graphical trends
- LED indicates high temperature
- Rain probability is calculated and displayed
# Results
The​‍​‌‍​‍‌​‍​‌‍​‍‌ system has worked to measure and visualize environmental data in real time and successfully capture it. Decoupling capacitors contribute to signal stability. Dual mode LCD interfaces help the system be reliable. The Serial Plotter can be really useful for comprehending the ​‍​‌‍​‍‌​‍​‌‍​‍‌data.
# Future Work
Wireless communication (Wi-Fi / Bluetooth), data logging system, advanced prediction using machine learning, mobile or web-based interface.
# Contributors
Sayme Ayça Öztekin, İbrahim Yasin Aşıcı.
