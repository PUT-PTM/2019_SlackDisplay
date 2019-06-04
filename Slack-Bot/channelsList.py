from channel import Channel

class ChannelsList:
    def __init__(self):
        self.channels = []

    def add(self, name, chan_id):
        """Adds channel to list"""
        self.channels.append(Channel(name, chan_id))

    def print(self):
        """Prints list of channels"""
        for e in self.channels:
            print(e)

    def print_name(self, name):
        """Prints channel with given name and it's messages"""
        for e in self.channels:
            if e.name == name:
                e.print()

    def print_all(self):
        """Prints channels and messages"""
        for e in self.channels:
            e.print()

    def get(self, name):
        for e in self.channels:
            if e.name == name:
                return e

        return None

    def get_id(self, id):
        return self.channels[id]



    def check(self, chan_id):
        """Checks if channel already exists"""
        other = False
        size = len(self.channels)
        for data in self.channels:

            if data.chan_id != chan_id:
                other = True
            else:
                other = False
                break
        return other

    def check_new(self, NEW_DATA_FLAG, SENT):
        iter = 0
        for e in self.channels:
            if e.new > 0 and SENT == 0:
                NEW_DATA_FLAG = 1
                return NEW_DATA_FLAG, SENT
            if e.new > 0 and SENT == 1:
                return NEW_DATA_FLAG, SENT
            iter += 1
        if iter == len(self.channels):
            if NEW_DATA_FLAG == 1:
                NEW_DATA_FLAG = 0
                SENT = 0

        return NEW_DATA_FLAG, SENT

