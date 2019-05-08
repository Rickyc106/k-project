import socket
import sys

UDP_IP = "192.168.1.107"
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

try:
	while True:
		data, addr = sock.recvfrom(1024)
		print "received message: ", data
except KeyboardInterrupt:
	print "Closing"
finally:
	sock.shutdown(socket.SHUT_RDWR)
	sock.close()