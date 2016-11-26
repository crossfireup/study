#!/usr/bin/env ruby

require 'monitor'

class Counter < Monitor
	attr_reader :count
	def initialize
		@count = 0
		super
	end
	def tick 
        @count += 1
		# synchronize do
        # end
    end
end

c = Counter.new
t1 = Thread.new { 10000.times { c.tick}}
t2 = Thread.new { 10000.times { c.tick}}

t1.join; t2.join
puts c.count
