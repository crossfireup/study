#!/usr/bin/env ruby

a = gets.chomp.to_i
case a
	when 0..4 then puts "#{a} < 5"
	when 5 then puts "#{a} == 5"
	when 5..10 then puts "#{a} > 5"
	else puts "uknown values #{a}"
end
