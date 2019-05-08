import socket
import sys
 
# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Bind the socket to the port
server_address = ("10.145.200.172", 5005)
sock.bind(server_address)
# Listen for incoming connections
sock.listen(1)
 
try: 
    while True:
        # Wait for a connection
        print('waiting for a connection...')
        connection, client_address = sock.accept()
        print('connection from %s:%d' % client_address)
        try:
            while True:
                # Receive the data one byte at a time
                data, addr = connection.recvfrom(2048)
                sys.stdout.write(data)
        finally:
            # Clean up the connection
            connection.close()
except KeyboardInterrupt:
    print('exiting.')
finally:
    sock.shutdown(socket.SHUT_RDWR)
    sock.close()