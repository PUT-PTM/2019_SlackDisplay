from messagesList import MessegesList


class Channel:
    def __init__(self, name, chan_id):
        self.name = name
        self.chan_id = chan_id
        self.msgs = MessegesList()
        self.new = 0

    def __str__(self):
        return f"Channel name: {self.name}\t Channel id: {self.chan_id}"

    def print(self):

        print(f"Channel name: {self.name}\tChannel id: {self.chan_id}\tNew messages: {self.new}")
        self.msgs.print()


