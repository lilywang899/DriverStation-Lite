'''
	udp socket server
'''

import socket  # for sockets
import sys  # for exit
from _thread import start_new_thread
import time
import logging
from threading import Timer

# host = '127.0.0.1'
# port = 1150

def recv_data(server_socket):
    while True:
        # receive data from client (data, addr)
        d = server_socket.recvfrom(1180)
        reply = d[0]
        addr = d[1]
        print('Server sent: ' + str(reply))
        # if int.from_bytes(reply,byteorder='big') & cEnabled:
        #     print('Robot is enabled')

def main():
    
    # create dgram udp socket
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.bind(('', 1180))
        #logger.info('Waiting for data')
    except socket.error:
        print('Failed to create socket')
        sys.exit()

    #msg = "H" lily
    
    try:
        start_new_thread(recv_data, (s,))
        time.sleep(20)

    except (socket.error):
        print('Error Code : ')
        sys.exit()

if __name__== '__main__':
    main()