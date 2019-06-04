from slackclient import SlackClient
import pytz
#import datetime
import time
import re
import sys, json
import serial
from channelsList import ChannelsList
from slacker import Slacker
import unicodedata
import threading

from threadTimer import ThreadTimer


def hello(s):
    print(s)


MSG_NUM = 16
NEW_DATA_FLAG = -1
SENT = 0

# s = "o shit, it works"
# t = threading.Timer(4.0, hello, [s])



slack = Slacker('')


channels_list = ChannelsList()
slack.get_channels(channels_list)
slack.get_messeges(channels_list)
users_map = slack.get_users()
print(users_map)

slack.send_message('CGTPA9HCK', "lorem ipsum")
slack.send_message('CGTPA9HCK', "dolor")
slack.send_message('CGTPA9HCK', "sit amet")


stopFlag = threading.Event()
thread = ThreadTimer(stopFlag, channels_list)
thread.start()






################################################################################
print("\n\nSerial\n\n")
ser = serial.Serial('COM7')

ser.isOpen()
out = ''

max_msg_index = len(channels_list.get('general').msgs.messages)-1
msg_index = max_msg_index

max_ch_index = len(channels_list.channels)-1
ch_index = 0


time.sleep(0.01)

while ser.inWaiting() > 0:
    out += str(ser.read(1).decode('ascii'))

if out != '':
    print("sinit>>" + out)
out = ''

while True:
    while ser.inWaiting() > 0:
        out += str(ser.read(1).decode('ascii'))
    if out != '':
        print(f"Recieved: {out}")
        time.sleep(0.02)

    if out.startswith('cms_up'):
        out = ''
        if msg_index > 0:
            msg_index = msg_index - 1

        text = channels_list.get_id(ch_index).msgs.messages[msg_index].text

        data = f"sms_up~{users_map[channels_list.get_id(ch_index).msgs.messages[msg_index].user]}~" \
               f"{text.replace('~', '``')}"
        data = unicodedata.normalize('NFKD', data).encode('ASCII', 'ignore')


        print(f"Sent data: {data}")
        ser.write(data)

        time.sleep(0.02)
    elif out.startswith('cms_dn'):
        out = ''
        if msg_index<max_msg_index:
            msg_index = msg_index + 1

        text = channels_list.get_id(ch_index).msgs.messages[msg_index].text

        data = f"sms_dn~{users_map[channels_list.get_id(ch_index).msgs.messages[msg_index].user]}~" \
               f"{text.replace('~', '``')}"
        data = unicodedata.normalize('NFKD', data).encode('ASCII', 'ignore')
        print(f"Sent data: {data}")

        if msg_index > max_msg_index-channels_list.get_id(ch_index).new:
            channels_list.get_id(ch_index).new = 0
        ser.write(data)

        time.sleep(0.02)
    elif out.startswith('cch_up'):
        out = ''
        if ch_index>0:
            ch_index = ch_index - 1
        else:
            ch_index = max_ch_index

        max_msg_index = len(channels_list.get_id(ch_index).msgs.messages) - 1
        msg_index = max_msg_index


        print(f"Changed channel to: {channels_list.get_id(ch_index).name}")

        data = f"sch_get~{channels_list.get_id(ch_index).name}~{channels_list.get_id(ch_index).new}"
        data = unicodedata.normalize('NFKD', data).encode('ASCII', 'ignore')
        print(f"Sent data: {data}")
        ser.write(data)

        time.sleep(0.02)

    elif out.startswith('cch_dn'):
        out = ''
        if ch_index < max_ch_index:
            ch_index = ch_index + 1
        else:
            ch_index = 0

        max_msg_index = len(channels_list.get_id(ch_index).msgs.messages) - 1
        msg_index = max_msg_index

        print(f"Changed channel to: {channels_list.get_id(ch_index).name}")

        data = f"sch_get~{channels_list.get_id(ch_index).name}~{channels_list.get_id(ch_index).new}"
        data = unicodedata.normalize('NFKD', data).encode('ASCII', 'ignore')
        print(f"Sent data: {data}")
        ser.write(data)

        time.sleep(0.02)

    elif out.startswith('cch_get'):
        out = ''
        slack.update_channels(channels_list)
        max_ch_index = len(channels_list.channels) - 1

        print(f"Changed channel to: {channels_list.get_id(ch_index).name}")
        data = f"sch_get~{channels_list.get_id(ch_index).name}~{channels_list.get_id(ch_index).new}"
        data = unicodedata.normalize('NFKD', data).encode('ASCII', 'ignore')
        print(f"Sent data: {data}")
        ser.write(data)

        time.sleep(0.02)
    else:
        out = ''


        time.sleep(0.02)

    max_ch_index = len(channels_list.channels) - 1



ser.close()
exit()




