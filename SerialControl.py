import serial
import time
import keyboard

arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)

def write(m):
    arduino.write(bytes(m, 'utf-8'))
    time.sleep(0.05)

def read():
    data = arduino.readline()
    return data


while True:
    wasd_state = [0, 0, 0, 0]

    try:  
        if keyboard.is_pressed('w'):
            wasd_state[0] = 1
        if keyboard.is_pressed('a'):
            wasd_state[1] = 1
        if keyboard.is_pressed('s'):
            wasd_state[2] = 1
        if keyboard.is_pressed('d'):
            wasd_state[3] = 1
    except:
        pass 

    key = tuple(wasd_state)

    dict = {(0,0,0,0):0, (1,0,0,0):1, (0,1,0,0):2, (0,0,1,0):3, (0,0,0,1):4, (1,1,0,0):5, (1,0,1,0):6, (1,0,0,1):7, (0,1,1,0):8, (0,1,0,1):9, (0,0,1,1):10, (1,1,1,0):11, (1,1,0,1):12, (1,0,1,1):13, (0,1,1,1):14, (1,1,1,1):15}

    # print(dict[key])

    write(str(dict[key]))
    print(arduino.readline())