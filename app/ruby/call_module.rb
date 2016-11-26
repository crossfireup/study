#!/usr/bin/env ruby


# require 'module.rb'
load 'module.rb'

class C
	include M
	def a
		print_a("a in C class")
	end
end

instance_c = C.new
instance_c.a
