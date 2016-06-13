#!/usr/bin/python
# -*- coding: utf-8 -*-
import socketIO_client

class WikiNamespace(socketIO_client.BaseNamespace):
    def on_change(self, change):
        print('%(user)s edited %(title)s' % change)

    def on_connect(self):
        self.emit('subscribe', '*.wikipedia.org')


socketIO = socketIO_client.SocketIO('stream.wikimedia.org', 80)
socketIO.define(WikiNamespace, '/rc')

socketIO.wait()
