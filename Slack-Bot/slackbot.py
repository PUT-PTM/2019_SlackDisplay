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


slack = Slacker('xoxb-536663832229-571336411969-JwKvJ76easEvRAoWVPM7IyGc')


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
out = ''
# for e in channels_list.get('general').msgs.messages:
#     #print(e.text)
#     #time = datetime.datetime.fromtimestamp(float(e["ts"]))
#     data = e.text
#     #print(f"{data}, {time}")
#     print(f"{data}")
#     ser.write(data.encode('ascii'))
#
#
#     #time.sleep(1)
#     out = ''
#     # let's wait one second before reading output (let's give device time to answer)
#     time.sleep(0.003)
#     while ser.inWaiting() > 0:
#         out += str(ser.read(1).decode('ascii'))
#
#     if out != '':
#         print(">>" + out)
max_msg_index = len(channels_list.get('general').msgs.messages)-1
msg_index = max_msg_index

max_ch_index = len(channels_list.channels)-1
ch_index = 1

#some nice function for that
data = f"sinit?{channels_list.get_id(ch_index).msgs.messages[msg_index].user}?" \
       f"{channels_list.get_id(ch_index).msgs.messages[msg_index].text}"

print(f"Sent data: {data}")
ser.write(data.encode('ascii'))

time.sleep(0.01)

while ser.inWaiting() > 0:
    out += str(ser.read(1).decode('ascii'))

if out != '':
    print("sinit>>" + out)
out = ''

# also some nice function
while True:
    while ser.inWaiting() > 0:
        out += str(ser.read(1).decode('ascii'))
    if out != '':
        print(f"Recieved: {out}")
        time.sleep(0.01)

    if out.startswith('cms_up'):
        out = ''
        if msg_index > 0:
            msg_index = msg_index - 1
        data = f"sms_up?{channels_list.get_id(ch_index).msgs.messages[msg_index].user}?" \
               f"{channels_list.get_id(ch_index).msgs.messages[msg_index].text}"
        print(f"Sent data: {data}")
        ser.write(data.encode('ascii'))

        time.sleep(0.01)
    elif out.startswith('cms_dn'):
        out = ''
        if msg_index<max_msg_index:
            msg_index = msg_index + 1
        data = f"sms_dn?{channels_list.get_id(ch_index).msgs.messages[msg_index].user}?" \
               f"{channels_list.get_id(ch_index).msgs.messages[msg_index].text}"
        print(f"Sent data: {data}")
        ser.write(data.encode('ascii'))

        time.sleep(0.01)
    elif out.startswith('cch_up'):
        out = ''
        if ch_index>0:
            ch_index = ch_index - 1
        else:
            ch_index = max_ch_index

        max_msg_index = len(channels_list.get_id(ch_index).msgs.messages) - 1
        msg_index = max_msg_index

        print(f"Changed channel to: {channels_list.get_id(ch_index).name}")

        # some nice function for that
        data = f"sinit?{channels_list.get_id(ch_index).msgs.messages[msg_index].user}?" \
               f"{channels_list.get_id(ch_index).msgs.messages[msg_index].text}"

        print(f"Sent data: {data}")
        ser.write(data.encode('ascii'))

        time.sleep(0.01)

    elif out.startswith('cch_dn'):
        out = ''
        if ch_index < max_ch_index:
            ch_index = ch_index + 1
        else:
            ch_index = 0

        max_msg_index = len(channels_list.get_id(ch_index).msgs.messages) - 1
        msg_index = max_msg_index

        print(f"Changed channel to: {channels_list.get_id(ch_index).name}")
        # some nice function for that
        data = f"sinit?{channels_list.get_id(ch_index).msgs.messages[msg_index].user}?" \
               f"{channels_list.get_id(ch_index).msgs.messages[msg_index].text}"

        print(f"Sent data: {data}")
        ser.write(data.encode('ascii'))

        time.sleep(0.01)
    else:
        out = ''



ser.close()
exit()




