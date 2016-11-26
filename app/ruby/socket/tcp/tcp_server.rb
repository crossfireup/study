#!/usr/bin/env ruby

require 'socket'

server = TCPServer.new 4567
begin
    sock = server.accept_nonblock
    sock.puts "helloc"
    # sock.close
rescue IO::WaitReadable, Errno::EINTR
    IO.select([server])
    retry
ensure
    server.close
end

