#code for laptop side of serial system
import subprocess
import serial
from operator import xor

s = serial.Serial("/dev/ttyACM0")
len_data = 15

data_in = [False for i in range (len_data)]

while True:
    event = -1;
    old_data = data_in
    if s.readline() == 'S':
        for j in range (len_data):
            data_in[j] = s.readline()
            if XOR(data_in[j] == old_data[j]):
                    event = j

        if event == 0: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])
        if event == 1: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])
        if event == 2: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])
        if event == 3: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])
        if event == 4: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])
        if event == 5: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])   
        if event == 6: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])
        if event == 7: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])
        if event == 8: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])
        if event == 9: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])
        if event == 10: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])
        if event == 11: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])
        if event == 12: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])
        if event == 13: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])
        if event == 14: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])
        if event == 15: p=subprocess.Popen(["vlc","/home/obsidem/Desktop/SoundFX/0"])



