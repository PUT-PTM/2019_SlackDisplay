from slackclient import SlackClient

class Slacker:
    def __init__(self, token):
        self.token = token
        self.sc = SlackClient(self.token)

    def __get_channel_list(self):
        """Gets JSON with channels"""
        channels_json = self.sc.api_call(
            "channels.list"
        )
        return channels_json

    def get_channels(self, ch):
        """Gets JSON with channels and adds channels to list"""
        channels_json = self.__get_channel_list()
        for e in channels_json["channels"]:
            ch.add(e["name"], e["id"])

    def __get_channel_history(self, chan_id):
        """Gets JSON with channel's id history"""
        response = self.sc.api_call(
            "channels.history",
            channel = chan_id
        )
        return response

    def get_messeges(self, channels_list):
        """Gets JSON with channel's id history and adds them to the list"""
        for e in channels_list.channels:
            history = self.__get_channel_history(e.chan_id)

            for data in history["messages"]:
                e.msgs.add(data["text"], data["user"], data["ts"])

            e.msgs.messages.reverse()

            # tmp = MessegesList()
            #
            # for data in history["messages"]:
            #     tmp.add(data["text"], data["user"], data["ts"])
            #
            # tmp.messages.reverse()
            # tmp.print()
            #
            # e.msgs = tmp