#!/usr/bin/env ruby

f = File.open("exception.rb", "r")
f.each do |line|
	puts line
end
f.close
