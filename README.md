# Energy Consumption Monitoring System with ESP8266 and STC013 Sensor

![Project Image](link_to_project_image_placeholder.jpg)

This project involves creating an energy consumption monitoring system using an ESP8266 microcontroller and an STC013 sensor. The system collects data about electric current consumption and presents it on a website in real-time using an up and down chart. Additionally, the system displays the electric current on an LED board.

## Project Overview

The energy consumption monitoring system consists of two main components:

1. **ESP8266 Microcontroller**: The ESP8266 runs a `.ino` Arduino sketch that reads data from the STC013 sensor, processes it, and sends it to a web server.
2. **Website Interface**: A website interface fetches the API JSON data sent by the ESP8266 and displays it on an up and down chart. The website is designed to show real-time changes in energy consumption.

## Features

- Monitors energy consumption using the STC013 sensor and ESP8266 microcontroller.
- Displays real-time energy consumption data on a website.
- Provides an LED board to show the current electric current.
- Utilizes an up and down chart to visualize energy consumption trends.

## How to Use

1. **Hardware Setup**:
   - Connect the STC013 sensor to the ESP8266 microcontroller according to the sensor's datasheet.
   - Set up the LED board to display the electric current. The brightness of the LED can represent the current intensity.

2. **Upload Code to ESP8266**:
   - Upload the `.ino` file to the ESP8266 using the Arduino IDE or platform of your choice.
   - Make sure to adjust any necessary configuration parameters, such as Wi-Fi credentials and server URLs.

3. **Website**:
   - The website fetches API JSON data from the ESP8266.
   - Use the provided website files to host the website on a web server.
   - Replace the dummy links in the website code with actual image links.

4. **Real-Time Monitoring**:
   - Access the website to view real-time energy consumption data.
   - The up and down chart will visualize the changes in energy consumption over time.
   - The LED board will display the current electric current intensity.

## Project Images

![Image 1](dummy_image_link_1.jpg)
![Image 2](dummy_image_link_2.jpg)

## Resources

- [ESP8266 Documentation](https://esp8266.net/)
- [STC013 Sensor Datasheet](link_to_stc013_datasheet.pdf)

Feel free to contribute to the project by adding improvements, features, or optimizations!

[License](LICENSE)



[License](LICENSE)
