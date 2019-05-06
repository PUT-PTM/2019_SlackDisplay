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
        pass
