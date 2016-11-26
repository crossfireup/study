#!/usr/bin/env ruby

list = [] 
1.upto(10) { |x| list << x}

puts list

def ascii_hex(str)
	puts str
	res = []
	whitespace = ""
	str.each_byte do |b|
		res << whitespace << "%02x" % b
	end
	return res
end

puts ascii_hex("hello c program")
