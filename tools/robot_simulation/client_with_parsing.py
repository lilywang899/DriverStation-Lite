'''
	udp socket client
'''

import socket  # for sockets
import sys  # for exit
from _thread import start_new_thread
import time
import logging
from threading import Timer

#protocol bytes
cEmergencyStop = 0x80 << 24
cFMSConnected = 0x08 << 24
cTeleoperated = 0x00 << 24
cTest = 0x01 << 24
cAutonomous = 0x02 << 24
cEnabled = 0x04 << 16

cRequestRestartCode = 0x04
cRequestReboot = 0x08

cRed1 = 0x00
cRed2 = 0x01
cRed3 = 0x02
cBlue1 = 0x03
cBlue2 = 0x04
cBlue3 = 0x05

cRTagCANInfo = 0x0e
cRTagCPUInfo = 0x05
cRTagRAMInfo = 0x06
cRTagDiskInfo = 0x04
cTagDate = 0x0f
cTagJoystick = 0x0c
cTagTimezone = 0x10


host = '127.0.0.1'
port = 1150

logger = logging.getLogger(__name__)

class RepeatTimer(Timer):
    def run(self):
        while not self.finished.wait(self.interval):
            self.function(*self.args,**self.kwargs)

def send_data(server_socket, msg):
    logger.info('Client sent: ' + str(msg))
    server_socket.sendto(msg.encode('utf-8'), (host, port))

def recv_data(server_socket):
    while True:
        # receive data from client (data, addr)
        d = server_socket.recvfrom(1024)
        reply = d[0]
        addr = d[1]
        logger.info('Server sent: ' + str(reply))
        if int.from_bytes(reply,byteorder='big') & cEnabled:
            logger.info('Robot is enabled')

def main():
    logging.basicConfig(filename='/home/lily/share/LiteDS_docs/robot_sim/ds_data.log',
                        level=logging.INFO,
                        format='%(asctime)s - %(levelname)s [%(lineno)d] %(message)s',
                        datefmt='%d/%m/%Y %I:%M:%S%p')
    # create dgram udp socket
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.bind(('', 1180))
        #logger.info('Waiting for data')
    except socket.error:
        print('Failed to create socket')
        sys.exit()

    msg = "H"

    try:
        start_new_thread(recv_data, (s,))
        timer = Timer(2, send_data, args=(s, msg))
        timer.start()
        time.sleep(10)
        timer.cancel()

    except (socket.error, msg):
        print('Error Code : ' + str(msg[0]) + ' Message ' + msg[1])
        sys.exit()

if __name__== '__main__':
    main()