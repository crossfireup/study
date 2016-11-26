#!/usr/bin/env ruby

Thread.abort_on_exception = true
threads = []
count = 0
10.times do |i|
	threads << Thread.new(i) do |id|
		raise "Boom" if id == 2
		print "#{id}\n"
		# sleep(0.1)
	end
end

threads.each {|t| t.join}
# threads.each do  |t| 
# 	begin
# 		t.join
# 	rescue RuntimeError => e
# 		puts "Failed: #{e.message}"
# 	end
# end
# 
