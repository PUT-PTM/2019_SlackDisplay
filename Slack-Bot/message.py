class Message:
    def __init__(self, text, user, ts):
        self.text = text
        self.user = user
        self.ts = ts

    def __str__(self):
        return f"\tUser: {self.user}\tText: {self.text}"

