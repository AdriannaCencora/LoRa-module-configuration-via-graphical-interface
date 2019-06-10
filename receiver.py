import serial
from configuration import *

ser = serial.Serial(receiver_port,baudrate,timeout = 1)

print("Waiting for data......")
while True:
	reading = ser.readline().decode('utf-8')
	print(reading)