from slackclient import SlackClient
import pytz
#import datetime
import time
import re
import sys, json
import serial

slack_token = 'xoxb-536663832229-571336411969-GejYp2GT38SV4REtQb8gk1HM'
sc = SlackClient(slack_token)

# send message on slack
# sc.api_call(
#   "chat.postMessage",
#   channel="#general",
#   text="Test Message"
# )

MSG_NUM = 3

# get message history from slack
response = sc.api_call(
    "channels.history",
    channel="CFRR7FSTB",
    count=MSG_NUM
)

# file = open("response.txt", "w")
# file.write(str(response))
# file.close

#print(json.dumps(response, indent=4))

ser = serial.Serial(
    port='com7',
    baudrate=9600,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)

ser.isOpen()

for e in response["messages"]:
    #time = datetime.datetime.fromtimestamp(float(e["ts"]))
    data = e["text"]
    #print(f"{data}, {time}")
    print(f"{data}")
    ser.write(data.encode('ascii'))


    time.sleep(1)
    out = ''
    # let's wait one second before reading output (let's give device time to answer)
    time.sleep(1)
    while ser.inWaiting() > 0:
        out += str(ser.read(1).decode('ascii'))

    if out != '':
        print(">>" + out)


ser.close()
exit()




