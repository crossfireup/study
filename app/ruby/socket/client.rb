#!/usr/bin/env ruby

require 'socket'

client = TCPSocket.new 'localhost', 2000

while line = client.gets
    puts line
end

client.close
