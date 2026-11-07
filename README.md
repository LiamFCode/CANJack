# CANJack
A vehicle security research tool that interfaces with the headlight wiring of any car manufactured since 2007 to intercept, capture, and replay electrical signals.

This project is powered by an Arduino Uno with a CANBus shield, and an ESP32 for storage. It splices into the CANBus wires from the headlight of practically any car made since 2007, reading every electrical signal on the network. This enables decoding to reverse engineer the signal protocol, as well as signal replay to create a man in the middle style attack. This works because there is no authentication or verification on this network, so as long as the signal is formatted correctly it is executed. This allows for the car to be unlocked, the immobilizer to be deactivated, and the engine to be started, and all through pulling back the paneling just behind the headlight and splicing into the wires through 2 t-tap connectors.<br>

## Implementation
To use this tool you must first clone the repository, then flash the ```unoCapture.cpp``` and ```unoReplay.cpp``` files to the Arduino Uno, and the ```esp32Logger.cpp``` file to the ESP32, then mount the CANBus shield and follow the wiring instructions below for the ESP32. Lastly, connect the high and low pins on the shield to their respective wires and connect the serial port to a laptop with SavvyCAN to decode the signals and program the signal to replay.
## License
MIT License

Copyright (c) 2026 LiamFCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
