#!/usr/bin/env ruby

module M
       def print_a(str)
		puts str
       end
	m_a = 4
end


class A
	include M
	def a
		print_a("a in A class")
	end
end

instance_a = A.new
instance_a.a
