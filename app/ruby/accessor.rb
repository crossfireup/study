#!/usr/bin/env ruby

class Test
	def initialize
		@var = 20
	end

	def var
		return @var
	end
	
	def var=(var)
		@var = var
	end
end

t = Test.new
puts t.var
t.var = 30
puts t.var


class Test1
	def initialize
		@var = 21
	end

	attr_accessor :var
end

t1 = Test1.new
puts t1.var
t1.var = 210
puts t1.var
