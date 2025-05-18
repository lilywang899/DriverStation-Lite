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
port = 1180

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

def create_packet(voltage):
    """
    Create a packet to send a specific voltage.
    :param voltage: The voltage value to encode (e.g., 5.0).
    :return: A list representing the packet.
    """
    # Integer part (upper byte) of the voltage
    upper = int(voltage)  # 5 for 5.0

    # Fractional part (lower byte), scaled to 0-255
    lower = int((voltage - upper) * 0xFF)  # 0 for 5.0

    # Construct the packet
    packet = [0x00] * 10  # Initialize a 10-byte packet with 0s
    packet[3] = 0x01  # Example control byte
    packet[4] = 0x02  # Example robot status byte
    packet[5] = upper  # Upper byte for the voltage
    packet[6] = lower  # Lower byte for the voltage
    packet[7] = 0x01  # Example request flag

    # Return only the relevant part of the packet
    return packet[:8]

def main():
    logging.basicConfig(filename='/home/lily/DriverStation-Lite/log/ds_data1.log',
                        level=logging.INFO,
                        format='%(asctime)s - %(levelname)s [%(lineno)d] %(message)s',
                        datefmt='%d/%m/%Y %I:%M:%S%p')
    # create dgram udp socket
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.bind(('', 1130))
        #logger.info('Waiting for data')
    except socket.error:
        print('Failed to create socket')
        sys.exit()

    msg = "I" 
    
    #packet = create_packet(5)

    try:
        start_new_thread(recv_data, (s,))
        timer = Timer(2, send_data, args=(s, msg))
        timer.start()
        time.sleep(10)
        timer.cancel()

    #except (socket.error, msg):
    except socket.error:
        print('Error Code : ' + str(msg[0]) + ' Message ' + msg[1])
        sys.exit()

    while(1):
        time. sleep(10)


if __name__== '__main__':
    main()
