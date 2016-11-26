#!/usr/bin/env ruby

require 'socket'

Addrinfo.udp('192.168.43.128', 4567).bind { |s|
    puts 'helloc '
    s.local_address.connect { |s| s.send "hello c world", 0}
    puts s.recv(100)
}


Addrinfo.tcp("www.ruby-lang.org", 80).connect {|s|
      s.print "GET / HTTP/1.0\r\nHost: www.ruby-lang.org\r\n\r\n"
        puts s.read
}

Addrinfo.unix("socket").bind { |s| 
    s.local_addres.connect { |s| s.send "hello unix", 0}
    puts s.recv(100)
}
