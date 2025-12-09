# RFID-TEST

RFID system testing and development project for Arduino.

## Description

This repository contains code for testing and implementing RFID (Radio-Frequency Identification) systems on Arduino. The project is designed to work with common RFID modules like RC522 or PN532.

## Features

- RFID tag reading
- Data writing to RFID tags
- UID authentication
- Tag data management

## Hardware Requirements

- Arduino board (Uno, Mega, Nano, or compatible)
- RFID RC522 Module (or compatible RFID reader)
- Jumper wires
- Breadboard (optional)

## Wiring Connection

### RC522 to Arduino Uno: 

| RC522 Pin | Arduino Pin |
|-----------|-------------|
| SDA       | Pin 5      |
| SCK       | Pin 13      |
| MOSI      | Pin 11      |
| MISO      | Pin 12      |
| IRQ       | Not connected |
| GND       | GND         |
| RST       | Pin 9       |
| 3.3V      | 3.3V        |

**Important:** RC522 operates at 3.3V.  Do NOT connect to 5V! 

## Software Requirements

- Arduino IDE (version 1.8.0 or later)
- MFRC522 Library (install via Arduino Library Manager)

## Installation

1. Clone this repository:
```bash
git clone https://github.com/andhvic/RFID-TEST.git
```

2. Install the MFRC522 Library:
   - Open Arduino IDE
   - Go to **Sketch** → **Include Library** → **Manage Libraries**
   - Search for "MFRC522"
   - Install "MFRC522 by GithubCommunity"

3. Open the project: 
   - Open the `.ino` file in Arduino IDE

4. Select your Arduino board:
   - Go to **Tools** → **Board** → Select your Arduino model

5. Select the correct port:
   - Go to **Tools** → **Port** → Select your COM port

6. Upload the code:
   - Click the **Upload** button or press `Ctrl+U`

## Usage

1. Connect the RFID module to Arduino according to the wiring diagram above
2. Upload the code to your Arduino
3. Open Serial Monitor (Tools → Serial Monitor or `Ctrl+Shift+M`)
4. Set baud rate to **9600**
5. Place an RFID card or tag near the reader
6. The card UID and data will be displayed in the Serial Monitor

## Troubleshooting

**Problem:** RFID reader not detected
- Check wiring connections
- Ensure RC522 is connected to 3.3V (NOT 5V)
- Verify MFRC522 library is installed

**Problem:** No response when scanning cards
- Check if the RFID tag is compatible (13. 56MHz)
- Move the tag closer to the reader
- Ensure RST pin is properly connected

**Problem:** Upload failed
- Check if correct board is selected
- Verify correct COM port is selected
- Close Serial Monitor before uploading

## Contributing

Contributions are always welcome! Please create a pull request or open an issue for suggestions and improvements. 

## License

[Add license information here]

## Contact

- GitHub: [@andhvic](https://github.com/andhvic)

## Notes

This project is designed for educational and testing purposes. 
```
