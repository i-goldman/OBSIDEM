#code for laptop side of serial system
import subprocess
import serial
from operator import xor

s = serial.Serial('/dev/tty.usbserial',9600)
len_data = 15
data_in = [False for i in range (len_data)]

while True:
    for i in range (0, len_data):
         data_in[i] = xor(s.readline() , data_in[i] )
    if data_in (0):
        subprocess.Popen('vlc s0.mp3')
        
