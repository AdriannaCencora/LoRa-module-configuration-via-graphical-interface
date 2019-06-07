import serial

port = '/dev/ttyUSB0'

ser = serial.Serial(port)

print("Waiting for data......")
while True
	reading = ser.readline().decode('utf-8')
	print(readline)