import serial
import time
import csv
import matplotlib
import colorama
from colorama import Fore, Back, Style
colorama.init(autoreset=True)
import pandas
import os
matplotlib.use("tkAgg")
import matplotlib.pyplot as plt
import numpy as np

SERIAL_PORT = 'COM3';
FILE_PATH = os.path.join(os.getcwd(),'raw_values.txt');
DATA_AMOUNT = 20; # taking 20 datapoints in

ser = serial.Serial(SERIAL_PORT)
ser.flushInput()

# read serial data
def readData()-> str:
    ser.flushInput()
    ser_bytes = ser.readline()
    return str(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))

# convert serial data
def setData()-> tuple:
    ax = ay = az = 0.0
    for _ in range(DATA_AMOUNT):
        #format the data into a list
        data = readData().split(',')
        ax_now = float(data[3])
        ay_now = float(data[4])
        az_now = float(data[5])
    # add the data values to the respected variable
    ax += ax_now
    ay += ay_now
    az += az_now
    return (ax / DATA_AMOUNT, ay / DATA_AMOUNT, az / DATA_AMOUNT) # average out data

# print data to file
def writeFile(dataList: list, fileName: str, delim: str = ',', fileMode = 'a'):
    df = pandas.DataFrame(dataList)
    df.to_csv(
        fileName,
        sep=delim,
        mode = fileMode, # file is open for writing
        header= False,
        index = False
    )

def main():

    input("Select any button when ready..   ")

    holdData = []
    for i in range(200):
        usrInput = input(Fore.GREEN+ "Select 'r' when ready for measurement. Select 'q' when ready to end the program  ").lower()
        
        if(usrInput == 'r'):
            ax, ay, az = setData();
            print(Fore.YELLOW + "Average readings: {:.4f}, {:.4f}, {:.4f}".format(ax, ay, az))
            holdData.append([ax, ay, az])
        elif(usrInput == 'q'):
            print(Fore.MAGENTA + "Saving and quitting")
            writeFile(holdData, FILE_PATH, delim ='\t')
            ser.close
            print("Done!")
            return
        else:
            print(Fore.RED + "reached max")
            writeFile(holdData, FILE_PATH, delimeter='\t')
            ser.close


if __name__ == '__main__':
    main()