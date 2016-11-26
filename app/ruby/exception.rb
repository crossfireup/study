#!/usr/bin/env ruby

f = File.open("rb.txt","w")
a = 0
begin
	a = a + 1
	while data = socket.read(512)
		f.write(data)
	end
rescue SystemCallError
	$stderr.print "IO failed: " + $! + "\n"
	f.close
	File.delete(f)
rescue StandardError
	$stderr.print "name error: " + $!.to_s + "\n"
	retry if a < 3
end
