'''
	udp socket client
'''

import socket  # for sockets
import sys  # for exit
from _thread import start_new_thread
host = '127.0.0.1'
port = 1150

def main():
    # create dgram udp socket
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.bind(('', 1110))
    except socket.error:
        print('Failed to create socket')
        sys.exit()

    while True:
        msg = "H"

        try:
            for x in range(10):
                # Set the whole string
                s.sendto(msg.encode('utf-8'), (host, port))

            # receive data from client (data, addr)
            d = s.recvfrom(1024)
            reply = d[0]
            addr = d[1]

            print('Server reply : ' + str(reply))

        except (socket.error, msg):
            print('Error Code : ' + str(msg[0]) + ' Message ' + msg[1])
            sys.exit()