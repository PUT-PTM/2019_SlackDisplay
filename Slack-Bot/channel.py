from messagesList import MessegesList


class Channel:
    def __init__(self, name, chan_id):
        self.name = name
        self.chan_id = chan_id
        self.msgs = MessegesList()

    def __str__(self):
        return f"Channel name: {self.name}\t Channel id: {self.chan_id}"

    def print(self):
        #return f"Channel name: {self.name}\t Channel id: {self.id}\n{self.msgs}"

        print(f"Channel name: {self.name}\t Channel id: {self.chan_id}")
        self.msgs.print()


