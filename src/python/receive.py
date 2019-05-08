import socket
import sys

#UDP_IP = "192.168.1.107"
#UDP_IP = "10.145.200.172"
UDP_IP = "10.145.69.25"

UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

missing_header, missing_closer = 0, 0

try:
	while True:
		data, addr = sock.recvfrom(1024)
		if(data[0] == '{'):
			if(data[len(data) == '}']):
				message_buffer = data
				print "received message: ", message_buffer
			else:
				missing_closer += 1
				print "ERROR: Missing '} closer", "Counter: ", missing_closer

				# TO-DO Reqest new data immediately
		else:
			missing_header += 1
			print "ERROR: Missing '{' header", "Counter: ", missing_header
			#  TO-DO Request new data immediately
except KeyboardInterrupt:
	print "Closing"
finally:
	sock.shutdown(socket.SHUT_RDWR)
	sock.close()