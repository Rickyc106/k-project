import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

def main():
	data, addr = sock.recvfrom(2048)
	print "received message:", data

if __name__ == "__main__":
	try:
		main()
	except KeyboardInterrupt:
		pass