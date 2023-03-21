import serial
import colorama
from colorama import Fore, Back, Style
colorama.init(autoreset=True)
import os

SERIAL_PORT = 'COM3';
FILE_PATH = os.path.join(os.getcwd(),'raw_values.txt');

ser = serial.Serial(SERIAL_PORT)
ser.flushInput()

# read serial data
def readData()-> str:
    ser.flushInput()
    ser_bytes = ser.readline()
    return str(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))

# convert serial data
def setData()-> tuple:
    roll = pitch = yaw = 0.0
    ax = ay = az = 0.0


    data = readData().split(',') #delimeter
    #euler angles
    roll_now = float(data[3])
    pitch_now = float(data[4])
    yaw_now = float(data[5])
    #raw numbers
    ax_now = float(data[6])
    ay_now = float(data[7])
    az_now = float(data[8])


    # add the data values to the respected variable
    roll += roll_now
    pitch += pitch_now
    yaw += yaw_now
    return (pitch , roll, yaw) # average out data

