from threading import Thread

from channelsList import ChannelsList
from slacker import Slacker


class ThreadTimer(Thread):
    def __init__(self, event, ch_list):
        Thread.__init__(self)
        self.stopped = event
        self.channels_list = ChannelsList()
        self.channels_list = ch_list
        # self.NEW_DATA_FLAG = NEW_DATA_FLAG
        # self.SENT = SENT
        self.slack = Slacker('')

    def run(self):
        while not self.stopped.wait(15):

            # self.channels_list.check_new(self.NEW_DATA_FLAG, self.SENT)
            self.slack.update_channels(self.channels_list)
            print("updated")



            # call a function