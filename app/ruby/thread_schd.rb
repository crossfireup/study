#!/usr/bin/env ruby

class Chase
	attr_reader :count
	def initialize(name)
		@name = name
		@count = 0
	end

	def chase(other)
		puts "start chase #{@name}"
		while @count < 5
			while @count - other.count > 1
				print "#{@name}: #{@count} thread.pass\n"
				Thread.pass
				# sleep(0.2)
			end
			@count += 1
			puts "#{@name}: #{@count}\n"
		end
	end
end

c1 = Chase.new("c1")
c2 = Chase.new("c2")
threads = [
	Thread.new{ Thread.stop; c1.chase(c2)},
	Thread.new{ Thread.stop; c2.chase(c1)}
]
start_index = rand(2)
# start_index = 1
threads[start_index].run
threads[1 - start_index].run
threads.each {|t| t.join}
