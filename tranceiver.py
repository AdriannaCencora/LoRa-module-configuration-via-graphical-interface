import serial
import os
from configuration import *


def print_menu(size,amount):
	
	print ('1. Set size of package [KB] (current value = '+str(size) + ')')
	print ('2. Set amount of packages (current value = '+str(amount) + ')')
	print ('3. Send data')
	print ('0. Exit')

scale = 1024
size = 3
byte_size = 0
amount = 1

ser = serial.Serial(tranceiver_port,baudrate,timeout = 1)

while True:
	print_menu(size, amount)	
	decision = input("Your choice: ")
	if(decision=='1'):
		size = input("Set size[KB]: ")
		byte_size = int(size)*scale
	elif(decision=='2'):
		amount = input("Set amount: ")
	elif(decision=='3'):
		for i in range(int(amount)):
			filename = "sended_logs/log"+str(i+1)
			os.system('mkdir -p sended_logs')
			os.system('./flog -t "log" -o'+filename+' -w -b ' + str(byte_size))
			f = open(filename,"r")
			indexed_log= (str(i+1) + " " + f.read()).encode() 
			#print('indexed_log')
			ser.write(indexed_log)
			ser.write(b"\n<<EOF>>\n")

	elif(decision=='0'):
		break
	else:
		print('Unrecognised command')						

ser.close()



