#!/usr/bin/env python
# -*- coding:utf-8 -*-

import SocketServer

class MyTcpHandle(SocketServer.BaseRequestHandler):

    def handle(self):
        self.data = self.request.recv(1024).strip()
        print "{} wrote:".format(self.client_address)
        print self.data
        self.request.sendall(self.data.upper())

if __name__ == '__main__':
    host, port = "localhost", 9999
    server = SocketServer.TCPServer((host, port), MyTcpHandle)
    server.serve_forever()
