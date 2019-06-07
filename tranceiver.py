import serial
import os

scale = 1024
size = 0
kb_size = 0
amount = 0
port = '/dev/ttyUSB0'

ser = serial.Serial(port)
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
			os.system('./flog -t "log" -o'+filename+' -w -b ' + str(byte_size))
			f = open(filename,"r")
			indexed_log= str(i+1) + " " + f.read() 
			print(indexed_log)
			ser.write(indexed_log)
			ser.write("\n<<EOF>>\n")
	elif(decision=='0'):
		break
	else:
		print('Unrecognised command')						

ser.close()



