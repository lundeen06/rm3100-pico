# RM3100 + Pico

This project implements a data collection system for the RM3100 magnetometer using a Raspberry Pi Pico microcontroller. The system captures magnetic field measurements in three axes and streams the data over USB.

## Features

- Continuous magnetic field measurements at 75Hz
- Three-axis (X, Y, Z) magnetic field data in microTesla (µT)
- Real-time data streaming over USB
- Data visualization tools
- Built-in LED status indicator
- Automatic sensor reconnection on failure

## Hardware Requirements

- Raspberry Pi Pico
- RM3100 Magnetometer
- I2C connection cables

## Pin Connections

| Pin Function | Pico GPIO | Physical Pin |
|--------------|-----------|--------------|
| I2C SDA      | GPIO 0    | Pin 1       |
| I2C SCL      | GPIO 1    | Pin 2       |
| LED          | GPIO 25   | Built-in LED|

## Software Dependencies

```bash
pip3 install -r requirements.txt
```

- Raspberry Pi Pico SDK
- Python 3.x with the following packages:
  - pyserial
  - pandas
  - matplotlib
  - numpy

## Building and Flashing

1. Set up the Pico SDK:
```bash
# Update the SDK path in CMakeLists.txt
set(PICO_SDK_PATH "~/pico-sdk")
```

2. Build the project:
```bash
mkdir build
cd build
cmake ..
make
```

3. Flash the compiled `rm3100_magnetometer.uf2` file to your Pico.

## Data Collection

1. Find your device port:
```bash
ls /dev/tty.*
```

2. Collect data using either method:

Using Python:
```bash
python record_data.py
```

Or using cu (Unix/Mac):
```bash
cu -l /dev/tty.usbmodem1101 -s 115200 > magnetometer_data.csv
```

## Data Format

The device outputs CSV data with the following columns:
- Timestamp(ms): Milliseconds since start
- M_x(µT): X-axis magnetic field
- M_y(µT): Y-axis magnetic field
- M_z(µT): Z-axis magnetic field
- M(µT): Total magnetic field magnitude

## Data Visualization

Run the plotting script to visualize the collected data:
```bash
python plots.py
```

This will generate:
- Time series plots for each axis and magnitude
- Basic statistical analysis
- Output plots saved as PNG files

## LED Status Indicators

- OFF: Normal operation
- Double Blink + 2s pause: Sensor initialization failure/connection lost

## Technical Details

- I2C Address: 0x23
- Sample Rate: 75 Hz
- Cycle Count: 200 (all axes)
- Scale Factor: 1/75 µT/LSB
- USB VID/PID: 0x2E8A/0x000A

## Troubleshooting

1. If the LED keeps blinking:
   - Check I2C connections
   - Verify sensor power supply
   - Confirm I2C address matches (0x23)

2. If no data appears:
   - Check USB connection
   - Verify correct port in data collection script
   - Ensure correct baud rate (115200)
