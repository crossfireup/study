#!/usr/bin/env ruby

require 'socket'
include Socket::Constants

socket = Socket::new( AF_INET, SOCK_STREAM, 0)
sockaddr = Socket.pack_sockaddr_in( 80, 'www.bing.com')
socket.connect(sockaddr)
socket.write("HEAD / HTTP/1.1\r\n\r\n")
puts socket.read
