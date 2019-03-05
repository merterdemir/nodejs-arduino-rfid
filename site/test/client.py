#! /usr/bin/env python
from socketIO_client import SocketIO, LoggingNamespace
import numpy as np

def on_connect():
    print('connect')

def on_disconnect():
    print('disconnect')

def on_reconnect():
    print('reconnect')

def on_data_response(*args):
    print('on_data_response', args)

socketIO = SocketIO('localhost', 3030, LoggingNamespace)
socketIO.on('connect', on_connect)
socketIO.on('disconnect', on_disconnect)
socketIO.on('reconnect', on_reconnect)

# Listen
socketIO.on('data_response', on_data_response)
while True:
    try:
        socketIO.emit('data', {'label': 'rfid', 'rfid': '0123456789'})
        socketIO.wait(seconds=np.random.randint(1,3))
    except KeyboardInterrupt:
        break