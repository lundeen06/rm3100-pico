import serial
import time

with serial.Serial('/dev/tty.usbmodem2101', 115200) as ser:
    with open('./output/magnetometer_data.csv', 'w') as f:
        while True:
            try:
                line = ser.readline().decode('utf-8')
                f.write(line)
                f.flush()  # Make sure data is written immediately
                print(line, end='')  # Show data as it's being recorded
            except KeyboardInterrupt:
                print("\nStopping data collection...")
                break