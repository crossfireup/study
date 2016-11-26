#!/usr/bin/env ruby

require 'socket'
include Socket::Constants
socket =Socket.new( AF_INET, SOCK_STREAM, 0)
socketaddr = Socket.sockaddr_in(80, 'www.baidu.com')
begin
    lambda {socket.shutdown; socket.close} if !socket.closed?
    socket.connect_nonblock(socketaddr)
rescue IO::WaitWritable
    IO::select(nil, [socket])
    begin
        socket.connect_nonblock(socketaddr)
        socket.write(<<EOF.gsub(/$\n/,'\r\n'))
HEAD / HTTP/1.1
User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:49.0) Gecko/20100101 Firefox/49.0
EOF
    rescue Errno::EISCONN => e
        print "error connect #{e.message}"
    end
end
puts socket.read
socket.close
