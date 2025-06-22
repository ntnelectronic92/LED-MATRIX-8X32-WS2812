# LED Matrix 8x32 WS2812 Project

## Overview
This project implements an LED matrix display using WS2812 LEDs, controlled via an ESP8266 microcontroller. The display can show scrolling text and images, and it is accessible through a web server interface.

## Project Structure
```
LED-MATRIX-8X32-WS2812
├── src
│   ├── main.cpp          # Entry point of the application
│   ├── matrix.cpp        # LED matrix handling functions
│   ├── matrix.h          # Header for matrix functions
│   ├── webserver.cpp     # Web server functionality
│   ├── webserver.h       # Header for web server functions
│   ├── userdata.cpp      # User data management
│   ├── userdata.h        # Header for user data functions
│   └── config.h          # Configuration constants
├── platformio.ini        # PlatformIO configuration
└── README.md             # Project documentation
```

## Setup Instructions
1. **Install PlatformIO**: Ensure you have PlatformIO installed in your development environment.
2. **Clone the Repository**: Clone this repository to your local machine.
3. **Open in PlatformIO**: Open the project folder in PlatformIO.
4. **Install Dependencies**: PlatformIO will automatically install the required libraries specified in `platformio.ini`.
5. **Configure Wi-Fi Credentials**: Update the `config.h` file with your Wi-Fi SSID and password.
6. **Upload the Code**: Connect your ESP8266 board and upload the code using PlatformIO.

## Usage
- After uploading the code, open the Serial Monitor to view the IP address assigned to the ESP8266.
- Access the web server by entering the IP address in a web browser.
- You can change the displayed text and LED mode through the web interface.

## Features
- Scrolling text display
- Image display capabilities
- Web server for remote control
- User data management for saving preferences

## License
This project is licensed under the MIT License.