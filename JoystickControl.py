import pygame
import requests


pygame.init()
pygame.joystick.init()


logiStick = pygame.joystick.Joystick(0)
logiStick.init()
print ("Index {0}:  {1} connected.".format (0, logiStick.get_name()))

# print(logiStick.get_numaxes())

# leftWheelSpeed = 0
# rightWheelSpeed = 0

joystickDeadband = 0.2
maxPower = 0.5

def deadband(inputSignal, deadband):
    return 0 if (abs(inputSignal) < deadband) else inputSignal

def clamp(num, min, max):
    return min if num < min else max if num > max else num

def CurvatureDrive(drive, turn, allowTurnInPlace):
    xSpeed = drive
    zRotation = turn

    if allowTurnInPlace:
        leftWheelSpeed = xSpeed - zRotation
        rightWheelSpeed = xSpeed + zRotation
    else:
        leftWheelSpeed = xSpeed - abs(xSpeed) * zRotation
        rightWheelSpeed = xSpeed + abs(xSpeed) * zRotation
    
    maxMagnitude = max(abs(leftWheelSpeed), abs(rightWheelSpeed))
    if (maxMagnitude > 1.0):
        leftWheelSpeed /= maxMagnitude
        rightWheelSpeed /= maxMagnitude
    
    return [leftWheelSpeed, rightWheelSpeed]




# while True:
#     pygame.event.pump()
#     drive = clamp(deadband(-logiStick.get_axis(1), joystickDeadband), -1.0, 1.0)  #forward is positive
#     turn = clamp(deadband(-logiStick.get_axis(0), joystickDeadband), -1.0, 1.0)   #right (CCW) is positive
#     zTwist = clamp(deadband(-logiStick.get_axis(2), joystickDeadband), -1.0, 1.0)  #CCW is positive


#     WheelSpeeds = CurvatureDrive(drive, turn, False)
#     # print("turn{0}, drive{1}, L{2}, R{3}".format(turn, drive, WheelSpeeds[0], WheelSpeeds[1]))
#     print("L  {0}         R  {1}".format(WheelSpeeds[0], WheelSpeeds[1]))


URL = 'http://192.168.4.1'
r = requests.get(url = URL, params = 'H')

