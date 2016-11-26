#!/usr/bin/env ruby

class Array
	def find
		for i in 0...size
			value = self[i]
			return value if yield(value)
		end
		nil
	end
end

puts [1, 3, 5, 7, 9].find { |x| x * x > 30}
