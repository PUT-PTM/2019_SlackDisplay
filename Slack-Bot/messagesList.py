from message import Message


class MessegesList:
    def __init__(self):
        self.messages = []

    def add(self, text, user, ts):
        self.messages.append(Message(text, user, ts))

    def print(self):
        for e in self.messages:
            print(e)

    def check(self):
        """Checks if message already exists"""
        pass