from slackclient import SlackClient
import pytz
#import datetime
import time
import re
import sys, json
import serial
from channelsList import ChannelsList
from slacker import Slacker

MSG_NUM = 16


slack = Slacker('xoxb-536663832229-571336411969-SVeVMb8w95UgYercyeRS0cDO')


channels_list = ChannelsList()
slack.get_channels(channels_list)
slack.get_messeges(channels_list)

channels_list.print_all()

channels_list.print_name('general')


# TODO: spradzanie czy dana wiadomość już jest
# TODO: protokół
# ser = serial.Serial(
#     port='COM7',
#     baudrate=9600,
#     parity=serial.PARITY_ODD,
#     stopbits=serial.STOPBITS_ONE,
#     bytesize=serial.EIGHTBITS
# )


################################################################################
print("\n\nSerial\n\n")
ser = serial.Serial('COM7')

ser.isOpen()

for e in channels_list.get('general').msgs.messages:
    #print(e.text)
    #time = datetime.datetime.fromtimestamp(float(e["ts"]))
    data = e.text
    #print(f"{data}, {time}")
    print(f"{data}")
    ser.write(data.encode('ascii'))


    #time.sleep(1)
    out = ''
    # let's wait one second before reading output (let's give device time to answer)
    time.sleep(3)
    while ser.inWaiting() > 0:
        out += str(ser.read(1).decode('ascii'))

    if out != '':
        print(">>" + out)


ser.close()
exit()




