import json

from slackclient import SlackClient
from messagesList import MessegesList

class Slacker:
    def __init__(self, token):
        self.token = token
        self.sc = SlackClient(self.token)

    def __get_channel_list(self):
        """Gets JSON with channels"""
        # channels_json = self.sc.api_call(
        #     "channels.list"
        # )

        channels_json = self.sc.api_call(
            "conversations.list",
            types='public_channel,private_channel'
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
            "conversations.history",
            channel = chan_id
        )
        return response



    def get_messeges(self, channels_list):
        """Gets JSON with channel's id history and adds them to the list"""
        for e in channels_list.channels:
            history = self.__get_channel_history(e.chan_id)
            # print(json.dumps(history, sort_keys=True, indent=4))
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

    def __get_users_list(self):
        users = self.sc.api_call(
            'users.list'
        )
        return users

    def get_users(self):
        users = self.__get_users_list()
        users_map = {}
        for data in users["members"]:
            users_map[data["id"]] = data["name"]
        return users_map

    def send_message(self, ch, txt):
        self.sc.api_call(
            'chat.postMessage',
            channel=ch,
            text=txt,
            as_user=True
        )

    def update_channels_list(self, ch):
        """Gets JSON with channels and adds channels to list"""
        channels_json = self.__get_channel_list()
        for e in channels_json["channels"]:
            if ch.check(e["id"]):
                ch.add(e["name"], e["id"])

    def update_channels(self, channels_list):

        self.update_channels_list(channels_list)

        for e in channels_list.channels:
            if len(e.msgs.messages) > 0:
                history = self.__get_channel_history(e.chan_id)

                tmp = MessegesList()

                for data in history["messages"]:


                    if e.msgs.messages[-1].ts < data["ts"]:
                        tmp.add(data["text"], data["user"], data["ts"])


                tmp.messages.reverse()
                count = len(tmp.messages)
                e.msgs.messages.extend(tmp.messages)
                e.new += count
            elif len(e.msgs.messages) == 0:
                history = self.__get_channel_history(e.chan_id)
                # print(json.dumps(history, sort_keys=True, indent=4))
                for data in history["messages"]:
                    e.msgs.add(data["text"], data["user"], data["ts"])

                e.msgs.messages.reverse()
                e.new = len(e.msgs.messages)
