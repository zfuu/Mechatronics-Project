import serial
import time

arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)


# def write_read(x):
#     arduino.write(bytes(x, 'utf-8'))
#     time.sleep(0.05)
#     data = arduino.readline()
#     return data

def write(m):
    arduino.write(bytes(m, 'utf-8'))
    time.sleep(0.05)

def read():
    data = arduino.readline()
    return data

while True:
    message = input("Enter a number: ") # Taking input from user
    # message = 'a'
    write(message)
    # value = write_read(num)
    # print(value) # printing the value
    print(arduino.readline())