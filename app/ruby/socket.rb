#!/usr/bin/env ruby

require 'socket'

client = TCPSocket.open('10.0.128.32', 'finger')
client.send("mysql\n", 0)
puts client.readlines
client.close
