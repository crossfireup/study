#!/usr/bin/env ruby

print "(t)imes or (p)lus: "
oper = gets
print "number: "
number = Integer(gets)
if oper =~ /^t/
	calc = lambda { |n| n * number}
else
	calc = lambda { |n| n + number}
end
puts((1..10).collect(&calc).join(", "))
