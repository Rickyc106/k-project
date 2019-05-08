import socket
import time

UDP_IP = "192.168.1.107"
UDP_PORT = 5005
MESSAGE = "Hello, World!"
#MESSAGE = str(42)

print "UDP target IP:", UDP_IP
print "UDP target port:", UDP_PORT
print "message:", MESSAGE

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
#sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))

n = 0

while(n < 3):
	sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
	time.sleep(0.5)
	n += 1